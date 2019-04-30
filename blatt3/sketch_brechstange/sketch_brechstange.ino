double red = 0.0;
double green = 0.0;
double blue = 0.0;

int redPin = 7;
int greenPin = 5;
int bluePin = 3;
int an = 0; //0 wenn aus


void setup() {  
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    String input = Serial.readString();
    checkInput(input);
  }
}

boolean checkInput(String input) {
  if(input.length() > 20){
    Serial.println("Kein gültiger Befehl (Leerzeichen?)");
  }
  else if(input.substring(0, 7) == "setRGB(" ) {
    //keine Kommas anstatt Punkten
    if(input.substring(8,9) == "," || input.substring(12,13) == "," || input.substring(16,17) == ","){
      Serial.println("Zahlenformat nicht richtig");
    }
    else if(input.length() < 20){
      Serial.println("Zu wenige Parameter (3 gefordert)");
    }
    else{
      setColor(input);
    }
  }
  else if(input.substring(0,7) == "RGBon()"){
    Serial.println();
    turnOn();
  }
  else if(input.substring(0,8) == "RGBoff()"){
    turnOff();
  }
  else{
    Serial.print("Eingabe: ");
    Serial.println(input);
    Serial.println("Kein gültiger Befehl");
  }
  
}

void setColor(String input) {
  //setRGB(0.1,0.2,0.3)
  double tempRed = input.substring(7,10).toDouble();
  double tempGreen = input.substring(11,14).toDouble();
  double tempBlue = input.substring(15,18).toDouble();
  double colors[] = {tempRed, tempGreen, tempBlue};
  int check = 1;
  for (int i = 0; i < 3; i++)
  {
    if(colors[i] < 0.0 || colors[i] > 1.0)
    {
      Serial.println("Nicht in gültiger Range");
      check = 0;
      
    }
  }
  if(check == 1)
  {
    red = tempRed;
    green = tempGreen;
    blue = tempBlue;
    Serial.print("Red: ");
    Serial.println(red);
    Serial.print("Green: ");
    Serial.println(green);
    Serial.print("Blue: ");
    Serial.println(blue);
    if(an == 1){
      analogWrite(redPin, red*255);
      analogWrite(greenPin, green*255);
      analogWrite(bluePin, blue*255);      
    }
  }
  
}

void turnOn() {
  analogWrite(redPin, red*255);
  analogWrite(greenPin, green*255);
  analogWrite(bluePin, blue*255);
  Serial.println("LED an");
  an = 1;
}

void turnOff() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  Serial.println("LED aus");
  an = 0;
}
