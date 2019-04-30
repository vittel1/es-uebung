/*TODO
 * Leerzeichen setRGB
 */
#include "regexTest.h"

double red = 0.0;
double green = 0.0;
double blue = 0.0;

int redPin = 7;
int greenPin = 5;
int bluePin = 3;


void setup() {

  //VERBINDUNG ZUR ANODE MACHEN
  
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
  Serial.begin(9600);
}

//hier konvertieren
void loop() {
  while (Serial.available() > 0) {
    std::string input = "";
    input += (char)Serial.read();
    checkInput(input);
  }
}

//hier
boolean checkInput(std::string input) {
  //Korrektheit prüfen, siehe Aufgabe verschiedenen Fälle
  /*
  switch(input) {
    case input.substring(0, 7) == "setRGB(":
      setColors(input);
      break;
    case input.substring(0, 7) == "RGBon()":
      turnOn();
      break;
    case input.substring(0, 8) == "RGBoff()":
      turnOff();
      break;
    default:
      Serial.print("Fehler bei der Eingabe!");
  }
  */
  if(testFormat(input)) {
    setColor(input);
  }
  else if(input == "RGBon()"){
    turnOn();
  }
  else if(input =="RGBoff()"){
    turnOff();
  }
  else{
    Serial.println("Kein gültiger Befehl");
  }
  
}

//hier
void setColor(std::string input) {
  //red 7-10
  //green 11-14
  //blue 15-18
  //setRGB(0.1,0.2,0.3)
  //double tempRed = input.substr(7,10).toDouble();
  //double tempGreen = input.substr(11,14).toDouble();
  //double tempBlue = input.substr(15,18).toDouble();
  //std::stod
  double tempRed = atof(input.substr(7, 3).c_str());
  double tempGreen = atof(input.substr(11, 3).c_str());
  double tempBlue = atof(input.substr(15, 3).c_str());
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
    Serial.println("Red: ");
    Serial.print(red);
    Serial.println("Green: ");
    Serial.print(green);
    Serial.println("Blue: ");
    Serial.print(blue);  
  }
  
}

void turnOn() {
  analogWrite(redPin, red*255);
  analogWrite(greenPin, green*255);
  analogWrite(bluePin, blue*255);
}

void turnOff() {
  analogWrite(redPin, 255);
  analogWrite(greenPin, 255);
  analogWrite(bluePin, 255);
}
