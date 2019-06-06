#include <SPI.h>
#include <SD.h>

 
//pin declarations
#define TFT_CS     10   //display: CS-pin
#define TFT_RST     9   //display: reset
#define TFT_DC      8   //display: Data/Command (D/C)
#define SD_CS     4             //SD-CSpin


#define TFT_DC_HIGH()           digitalWrite(TFT_DC, HIGH)
#define TFT_DC_LOW()            digitalWrite(TFT_DC, LOW)


//SPI-Settings
#define SPI_DEFAULT_FREQ        8000000      ///< Default SPI data clock frequency
SPISettings settingsTFT(SPI_DEFAULT_FREQ, MSBFIRST, SPI_MODE0);


//TFT-area of 128 x 160 (1.8") TFT
const uint8_t FIRST_COL = 2;
const uint8_t FIRST_ROW = 1;
const uint8_t LAST_COL = 129;
const uint8_t LAST_ROW = 160;

//TFT's commands
const uint8_t SWRESET = 0x01;           // Software reset                                                                                                                  
const uint8_t SLPOUT = 0x11;            //Sleep out & booster on                                                                                                           
const uint8_t DISPOFF = 0x28;       //Display off                                                                                                                          
const uint8_t DISPON = 0x29;            //Display on                                                                                                                       
const uint8_t CASET = 0x2A;                     //Column adress set                                                                                                        
const uint8_t RASET = 0x2B;                     //Row adress set                                                                                                           
const uint8_t RAMWR = 0x2C;                     //Memory write                                                                                                             
const uint8_t MADCTL = 0x36;            //Memory Data Access Control                                                                                                       
const uint8_t COLMOD = 0x3A;            //RGB-format, 12/16/18bit                                                                                                          
const uint8_t INVOFF = 0x20;            // Display inversion off                                                                                                           
const uint8_t INVON = 0x21;                     // Display inversion on                                                                                                    
const uint8_t INVCTR = 0xB4;            //Display Inversion mode control                                                                                                   
const uint8_t NORON = 0x13;                     //Partial off (Normal)                                                                                                     
                                                                                                                                                                           
const uint8_t PWCTR1 = 0xC0;            //Power Control 1                                                                                                                  
const uint8_t PWCTR2 = 0xC1;            //Power Control 2                                                                                                                  
const uint8_t PWCTR3 = 0xC2;            //Power Control 3                                                                                                                  
const uint8_t PWCTR4 = 0xC3;            //Power Control 4                                                                                                                  
const uint8_t PWCTR5 = 0xC4;            //Power Control 5
const uint8_t VMCTR1 = 0xC5;            //VCOM Voltage setting


unsigned char font[95][6] =
{
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 }, // space
{ 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00 }, // !
{ 0x00, 0x07, 0x00, 0x07, 0x00, 0x00 }, // "
{ 0x14, 0x7F, 0x14, 0x7F, 0x14, 0x00 }, // #
{ 0x24, 0x2A, 0x7F, 0x2A, 0x12, 0x00 }, // $
{ 0x23, 0x13, 0x08, 0x64, 0x62, 0x00 }, // %
{ 0x36, 0x49, 0x55, 0x22, 0x50, 0x00 }, // &
{ 0x00, 0x00, 0x07, 0x00, 0x00, 0x00 }, // '
{ 0x00, 0x1C, 0x22, 0x41, 0x00, 0x00 }, // (
{ 0x00, 0x41, 0x22, 0x1C, 0x00, 0x00 }, // )
{ 0x0A, 0x04, 0x1F, 0x04, 0x0A, 0x00 }, // *
{ 0x08, 0x08, 0x3E, 0x08, 0x08, 0x00 }, // +
{ 0x00, 0x50, 0x30, 0x00, 0x00, 0x00 }, // ,
{ 0x08, 0x08, 0x08, 0x08, 0x08, 0x00 }, // -
{ 0x00, 0x60, 0x60, 0x00, 0x00, 0x00 }, // .
{ 0x20, 0x10, 0x08, 0x04, 0x02, 0x00 }, // slash
{ 0x3E, 0x51, 0x49, 0x45, 0x3E, 0x00 }, // 0
{ 0x00, 0x42, 0x7F, 0x40, 0x00, 0x00 }, // 1
{ 0x42, 0x61, 0x51, 0x49, 0x46, 0x00 }, // 2
{ 0x21, 0x41, 0x45, 0x4B, 0x31, 0x00 }, // 3
{ 0x18, 0x14, 0x12, 0x7F, 0x10, 0x00 }, // 4
{ 0x27, 0x45, 0x45, 0x45, 0x39, 0x00 }, // 5
{ 0x3C, 0x4A, 0x49, 0x49, 0x30, 0x00 }, // 6
{ 0x03, 0x71, 0x09, 0x05, 0x03, 0x00 }, // 7
{ 0x36, 0x49, 0x49, 0x49, 0x36, 0x00 }, // 8
{ 0x06, 0x49, 0x49, 0x29, 0x1E, 0x00 }, // 9
{ 0x00, 0x36, 0x36, 0x00, 0x00, 0x00 }, // :
{ 0x00, 0x56, 0x36, 0x00, 0x00, 0x00 }, // ;
{ 0x08, 0x14, 0x22, 0x41, 0x00, 0x00 }, // <
{ 0x14, 0x14, 0x14, 0x14, 0x14, 0x00 }, // =
{ 0x00, 0x41, 0x22, 0x14, 0x08, 0x00 }, // >
{ 0x02, 0x01, 0x51, 0x09, 0x06, 0x00 }, // ?
{ 0x32, 0x49, 0x79, 0x41, 0x3E, 0x00 }, // @
{ 0x7E, 0x11, 0x11, 0x11, 0x7E, 0x00 }, // A
{ 0x7F, 0x49, 0x49, 0x49, 0x36, 0x00 }, // B
{ 0x3E, 0x41, 0x41, 0x41, 0x22, 0x00 }, // C
{ 0x7F, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // D
{ 0x7F, 0x49, 0x49, 0x49, 0x41, 0x00 }, // E
{ 0x7F, 0x09, 0x09, 0x09, 0x01, 0x00 }, // F
{ 0x3E, 0x41, 0x41, 0x49, 0x7A, 0x00 }, // G
{ 0x7F, 0x08, 0x08, 0x08, 0x7F, 0x00 }, // H
{ 0x00, 0x41, 0x7F, 0x41, 0x00, 0x00 }, // I
{ 0x20, 0x40, 0x41, 0x3F, 0x01, 0x00 }, // J
{ 0x7F, 0x08, 0x14, 0x22, 0x41, 0x00 }, // K
{ 0x7F, 0x40, 0x40, 0x40, 0x40, 0x00 }, // L
{ 0x7F, 0x02, 0x0C, 0x02, 0x7F, 0x00 }, // M
{ 0x7F, 0x04, 0x08, 0x10, 0x7F, 0x00 }, // N
{ 0x3E, 0x41, 0x41, 0x41, 0x3E, 0x00 }, // O
{ 0x7F, 0x09, 0x09, 0x09, 0x06, 0x00 }, // P
{ 0x3E, 0x41, 0x51, 0x21, 0x5E, 0x00 }, // Q
{ 0x7F, 0x09, 0x19, 0x29, 0x46, 0x00 }, // R
{ 0x26, 0x49, 0x49, 0x49, 0x32, 0x00 }, // SsetContrast(0.2)
{ 0x01, 0x01, 0x7F, 0x01, 0x01, 0x00 }, // T
{ 0x3F, 0x40, 0x40, 0x40, 0x3F, 0x00 }, // U
{ 0x1F, 0x20, 0x40, 0x20, 0x1F, 0x00 }, // V
{ 0x3F, 0x40, 0x38, 0x40, 0x3F, 0x00 }, // W
{ 0x63, 0x14, 0x08, 0x14, 0x63, 0x00 }, // X
{ 0x07, 0x08, 0x70, 0x08, 0x07, 0x00 }, // Y
{ 0x61, 0x51, 0x49, 0x45, 0x43, 0x00 }, // Z
{ 0x00, 0x7F, 0x41, 0x41, 0x00, 0x00 }, // [
{ 0x02, 0x04, 0x08, 0x10, 0x20, 0x00 }, // backslash
{ 0x00, 0x41, 0x41, 0x7F, 0x00, 0x00 }, // ]
{ 0x04, 0x02, 0x01, 0x02, 0x04, 0x00 }, // ^
{ 0x40, 0x40, 0x40, 0x40, 0x40, 0x00 }, // _
{ 0x00, 0x01, 0x02, 0x04, 0x00, 0x00 }, // `
{ 0x20, 0x54, 0x54, 0x54, 0x78, 0x00 }, // a
{ 0x7F, 0x48, 0x44, 0x44, 0x38, 0x00 }, // b
{ 0x38, 0x44, 0x44, 0x44, 0x20, 0x00 }, // c
{ 0x38, 0x44, 0x44, 0x48, 0x7F, 0x00 }, // d
{ 0x38, 0x54, 0x54, 0x54, 0x18, 0x00 }, // e
{ 0x08, 0x7E, 0x09, 0x01, 0x02, 0x00 }, // f
{ 0x08, 0x54, 0x54, 0x54, 0x3C, 0x00 }, // g
{ 0x7F, 0x08, 0x04, 0x04, 0x78, 0x00 }, // h
{ 0x00, 0x48, 0x7D, 0x40, 0x00, 0x00 }, // i
{ 0x20, 0x40, 0x44, 0x3D, 0x00, 0x00 }, // j
{ 0x7F, 0x10, 0x28, 0x44, 0x00, 0x00 }, // k
{ 0x00, 0x41, 0x7F, 0x40, 0x00, 0x00 }, // l
{ 0x7C, 0x04, 0x78, 0x04, 0x78, 0x00 }, // m
{ 0x7C, 0x08, 0x04, 0x04, 0x78, 0x00 }, // n
{ 0x38, 0x44, 0x44, 0x44, 0x38, 0x00 }, // o
{ 0x7C, 0x14, 0x14, 0x14, 0x08, 0x00 }, // p
{ 0x08, 0x14, 0x14, 0x18, 0x7C, 0x00 }, // q
{ 0x7C, 0x08, 0x04, 0x04, 0x08, 0x00 }, // r
{ 0x48, 0x54, 0x54, 0x54, 0x20, 0x00 }, // s
{ 0x04, 0x3F, 0x44, 0x40, 0x20, 0x00 }, // t
{ 0x3C, 0x40, 0x40, 0x20, 0x7C, 0x00 }, // u
{ 0x1C, 0x20, 0x40, 0x20, 0x1C, 0x00 }, // v
{ 0x3C, 0x40, 0x30, 0x40, 0x3C, 0x00 }, // w
{ 0x44, 0x28, 0x10, 0x28, 0x44, 0x00 }, // x
{ 0x0C, 0x50, 0x50, 0x50, 0x3C, 0x00 }, // y
{ 0x44, 0x64, 0x54, 0x4C, 0x44, 0x00 }, // z
{ 0x00, 0x08, 0x36, 0x41, 0x00, 0x00 }, // {
{ 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00 }, // |
{ 0x00, 0x41, 0x36, 0x08, 0x00, 0x00 }, // }
{ 0x10, 0x08, 0x08, 0x10, 0x08, 0x00 } // ~
};


void TFTwriteCommand(uint8_t cmd){
    TFT_DC_LOW();
    SPI.transfer(TFT_CS, cmd);
    TFT_DC_HIGH();
}

void TFTinit(void) {
        //minimal configuration: only settings which are different from Reset Default Value
        //or not affected by HW/SW-reset
        SPI.beginTransaction(TFT_CS, settingsTFT);

        TFTwriteCommand(SWRESET);
        delay(120);                     //mandatory delay
        TFTwriteCommand(SLPOUT);        //turn off sleep mode.
        delay(120);
        TFTwriteCommand(PWCTR1);
         SPI.transfer(TFT_CS, 0xA2);
         SPI.transfer(TFT_CS, 0x02);
         SPI.transfer(TFT_CS, 0x84);
        TFTwriteCommand(PWCTR4);
         SPI.transfer(TFT_CS, 0x8A);
         SPI.transfer(TFT_CS, 0x2A);
        TFTwriteCommand(PWCTR5);
         SPI.transfer(TFT_CS, 0x8A);
         SPI.transfer(TFT_CS, 0xEE);
        TFTwriteCommand(VMCTR1);
         SPI.transfer(TFT_CS, 0x0E);                    //VCOM = -0.775V

        //Memory Data Access Control D7/D6/D5/D4/D3/D2/D1/D0
        //                                                       MY/MX/MV/ML/RGB/MH/-/-
        // MY- Row Address Order; ‘0’ =Increment, (Top to Bottom)
        // MX- Column Address Order; ‘0’ =Increment, (Left to Right)
        // MV- Row/Column Exchange; '0’ = Normal,
        // ML- Scan Address Order; ‘0’ =Decrement,(LCD refresh Top to Bottom)
        //RGB - '0'= RGB color fill order
        // MH - '0'= LCD horizontal refresh left to right
        TFTwriteCommand(MADCTL);
         SPI.transfer(TFT_CS, 0x08);

        TFTwriteCommand(COLMOD);        //RGB-format, color mode
         SPI.transfer(TFT_CS, 0x55); //16-bit/pixel; high nibble don't care

        TFTwriteCommand(CASET);    //set column adress range: full range
         SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, FIRST_COL);
         SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, LAST_COL);
        TFTwriteCommand(RASET);   //set row adress range: full range
         SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, FIRST_ROW);
         SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, LAST_ROW);

        TFTwriteCommand(NORON);
        TFTwriteCommand(DISPON);

        SPI.endTransaction();
}

void setPixel(int x, int y, uint16_t value)
{
  SPI.beginTransaction(TFT_CS, settingsTFT);
  
  TFTwriteCommand(CASET);
  SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, x);
  SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, x);
  
  TFTwriteCommand(RASET);
  SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, y);
  SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, y);
  
  TFTwriteCommand(RAMWR);
  SPI.transfer(TFT_CS, value>>8);
  SPI.transfer(TFT_CS, value);
  
  SPI.endTransaction();
}


void printChar()
{
  uint16_t mask = 0x01;
  int xPos = 30;
  int yPos = 30;
  for(int j = 0; j < 6; j++)
  {
    for(int i = 0; i < 8; i++)
    {
      if((font[11][j] & mask) != 0)
      {
        setPixel(xPos, yPos, 0x0000);
      }
      yPos++;
      mask = mask << 1;
    }
    xPos++;
    yPos = 30;
    mask = 0x01;
  }
  
}


int printChar(int x, int y, char value, uint16_t fgColor, uint16_t bgColor)
{
  if(x + 8 > LAST_COL || y + 6 > LAST_ROW)
  {
    return -1; 
  }
  
  
  uint16_t mask = 0x01;
  int xPos = x;
  int yPos = y;
  
  for(int j = 0; j < 6; j++)
  {
    for (int i = 0; i < 8; i++)
    {
      if((font[value - 32][j] & mask) != 0)
      {
        setPixel(xPos, yPos, fgColor);
        //addToBuffer(xPos, yPos, fgColor);
      }
      else
      {
        setPixel(xPos, yPos, bgColor);
        //addToBuffer(xPos, yPos, bgColor);
      }
      yPos++;
      mask = mask << 1;
    }

    xPos++;
    yPos = y;
    mask = 0x01;  
  }
  return 1;
}

int printString(int x, int y, char* c_str, uint16_t fgColor, uint16_t bgColor)
{
  int lengthStr = strlen(c_str);
  
  for(int i = 0; i < lengthStr; i++)
  {
    int val = printChar(x + i*6, y, c_str[i], fgColor, bgColor);
    if(val == -1)
    {
      return -1;
    }
  }
  return 1;
}

void clearDisplay() {
  for(int j = FIRST_COL; j <= LAST_COL; j++)
  {
    for(int i = FIRST_ROW; i <= LAST_ROW; i++)
    {
      setPixel(j, i, 0xFFFF);
    }
  }
  
}


void fileExists(String filename) {
  if(SD.exists(filename))
  {
    Serial.println("File exists");
  }
  else
  {
    Serial.println("File doesn't exists");
  }
}

void toSerial(String filename) {
  File file = SD.open(filename);
  if(file)
  {
    while(file.available())
    {
      Serial.print(file.read());
    }
    file.close();
  }
  else
  {
    Serial.print("error opening ");
    Serial.println(filename);
  }
}

void toLCD() {
  
}

void listDirectory(String filename) {
  File dir;
  if(!dir = SD.open(filename))
  {
    Serial.println("Directory/File couldn't be opened");
  }
  else
  {
    Serial.println("Entries:");
    while(true)
    {
      File entry = dir.openNextFile();
      if(!entry)
      {
        dir.close();
        return;
      }
      Serial.println(entry.name());
      entry.close();
    }
  
  }
}
  
  


boolean checkInput(String input) {
   if(input.substring(0,14) == "listDirectory(") {
    Serial.println("Dir: ");
    listDirectory(input.substring(14, input.length() - 1));     
   }
   else if(input.substring(0,14) == "doesFileExist(") {
    Serial.println("File Exists?");
    fileExists(input.substring(14, input.length()-1);
   }
   else if(input.substring(0,19) == "outputFileToSerial(") {
    Serial.println("To Serial: ");
    toSerial(input.substring(19, input.length() - 1));
   }
   else if(input.substring(0,16) == "outputFileToLCD(") {
    Serial.println("To LCD: ");
    toLCD();
   }
   else {
    Serial.print("Input: ");
    Serial.println(input);
    Serial.println("Not valid");
   }
}



void setup() {
    // set pin-modes
  pinMode(TFT_RST, OUTPUT);
  pinMode(TFT_DC, OUTPUT);

  // initialize serial port 0
  Serial.begin(9600);
  Serial.println("Exercise no.5 template\n");

  // initialize SPI:
  // several devices: multiple SPI.begin(nn_CS) possible
  SPI.begin(TFT_CS);
  delay(10);

  //power-on-reset of Display
  digitalWrite(TFT_RST, HIGH);
  delay(100);
  digitalWrite(TFT_RST, LOW);
  delay(100);
  digitalWrite(TFT_RST, HIGH);
  delay(100);

  TFTinit();
  Serial.println("Display Initialized");
  delay(100);

  //clear display
    uint8_t xs = FIRST_COL;
    uint8_t xe = LAST_COL;
    uint8_t ys = FIRST_ROW;
    uint8_t ye = LAST_ROW;
  uint16_t time = millis();
    SPI.beginTransaction(TFT_CS, settingsTFT);
    TFTwriteCommand(CASET); //define writewindow column-range
        SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, xs);
        SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, xe);
    TFTwriteCommand(RASET); //define writewindow row-range
        SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, ys);
        SPI.transfer(TFT_CS, 0x00); SPI.transfer(TFT_CS, ye);
    TFTwriteCommand(RAMWR);  //assigne background-color to every element of writewindow
        for (uint16_t i=0; i<(xe+1-xs)*(ye+1-ys); i++) {
            SPI.transfer(TFT_CS, 0xFF);
            SPI.transfer(TFT_CS, 0xFF);}
    SPI.endTransaction();
  time = millis() - time;
  Serial.print("time consumption of clear-display: "); Serial.print(time, DEC); Serial.println(" ms");
  
  //Init sd-card
  if(!SD.begin(SD_CS))
  {
    Serial.println("card not initialised");
  }
}

void loop() {
  while (Serial.available() > 0) {
    String input = Serial.readString();
    checkInput(input);
    }
}
