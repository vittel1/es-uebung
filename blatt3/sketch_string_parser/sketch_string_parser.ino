/*TODO
 * Turn off und Turn on
 * Leerzeichen setRGB
 * Formate, reg. Ausdrücke?
 * Werte im richtigem Bereich
 */


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
  Serial.begin(9600);
}

void loop() {
  while (Serial.available() > 0) {
    //const char* test = "hallo";
    String input = Serial.readString();
    checkInput(input);
  }
}

boolean checkInput(String input) {
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
  if(input.substring(0, 7) == "setRGB(") {
    setColor(input);
  }
  
}

void setColor(String input) {
  //red 7-10
  //green 11-14
  //blue 15-18
  //setRGB(0.1,0.2,0.3)
  red = input.substring(7,10).toDouble();
  green = input.substring(11,14).toDouble();
  blue = input.substring(15,18).toDouble();
  Serial.println(red);
  Serial.println(green);
  Serial.println(blue);
  turnOn();
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
