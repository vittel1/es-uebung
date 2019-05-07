#include <DueTimer.h>

int redPin = 11;
int greenPin = 7;
int bluePin = 6;
int buttonLeft = 31;
int buttonRight = 43;
int bridgePWM = 5;
int bridgeIn2 = 47;
int bridgeIn1 = 49;
DueTimer timerLinks;
DueTimer timerRechts;


int buttonStateLeft = HIGH;
int buttonStateRight = HIGH;

int previousStateLeft = LOW;
int previousStateRight = LOW;

int countLeft = 0;
int countRight = 0;

int StandBy = HIGH;
int currentMode = 0; //0 für Geschwindigkeit, 1 für Richtung

int currentSpeed = 100;

void speedDown(void)
{
  int val = digitalRead(buttonRight);
  
  if(val != buttonStateRight)
  {
    if(previousStateRight == val) 
    {
      countRight++;
    }


    if(countRight == 100)
    {
      if(countLeft > 25)
      {
        timerLinks.stop();
        timerRechts.stop();
        countLeft = 0;
        countRight = 0;
        currentMode = !currentMode;
        Serial.println("currentMode geändert");
        Serial.println(currentMode);
        return;
      }
      if(currentMode == 0)
      {
        
        if(currentSpeed - 25 < 0)
        {
          currentSpeed = 0;
        }
        else
        {
          currentSpeed = currentSpeed - 25;
        }
        Serial.println("currentSpeed verändert");
        Serial.println(currentSpeed);
        analogWrite(bridgePWM, currentSpeed);
      }
      else
      {
        int stateIn1 = digitalRead(bridgeIn1);
        int stateIn2 = digitalRead(bridgeIn2);
        if(stateIn1 == LOW && stateIn2 == HIGH)
        {
          digitalWrite(bridgeIn1, HIGH);
          digitalWrite(bridgeIn2, LOW);
          analogWrite(bridgePWM, 0);
          Serial.println("drehrichtung anders");
        }
        else
        {
          if(analogRead(bridgePWM) == 0)
          {
            analogWrite(bridgePWM, currentSpeed); 
            Serial.println("jetzt drehen"); 
          }
          else
          {
            analogWrite(bridgePWM, 0);
            Serial.println("jetzt nicht");
          }
          
        }
      }
      countRight = 0; 
      timerRechts.stop();
    }

    if(previousStateRight != val)
    {
      countRight = 0;
    }
    previousStateRight = val;
  }
}

void speedUp(void)
{
  int val = digitalRead(buttonLeft);
  
  if(val != buttonStateLeft)
  {
    if(previousStateLeft == val) 
    {
      countLeft++;
    }


    if(countLeft == 100)
    {
      if(countRight > 25)
      {
        timerLinks.stop();
        timerRechts.stop();
        countLeft = 0;
        countRight = 0;
        currentMode = !currentMode;
        Serial.println("currentMode geändert");
        Serial.println(currentMode);
        return;
      }
      if(currentMode == 0)
      {
        if(currentSpeed + 25 > 255)
        {
          currentSpeed = 255;
        }
        else
        {
          currentSpeed = currentSpeed + 25;
        }
        Serial.println("currentSpeed verändert");
        Serial.println(currentSpeed);
        analogWrite(bridgePWM, currentSpeed);
      }
      else
      {
        int stateIn1 = digitalRead(bridgeIn1);
        int stateIn2 = digitalRead(bridgeIn2);
        if(stateIn1 == HIGH && stateIn2 == LOW)
        {
          digitalWrite(bridgeIn1, LOW);
          digitalWrite(bridgeIn2, HIGH);
          analogWrite(bridgePWM, 0);
          Serial.println("drehrichtung anders");
        }
        else
        {
          if(analogRead(bridgePWM) == 0)
          {
            analogWrite(bridgePWM, currentSpeed);
            Serial.println(analogRead(bridgePWM));
            Serial.println("jetzt drehen");  
          }
          else
          {
            analogWrite(bridgePWM, 0);
            Serial.println(analogRead(bridgePWM));
            Serial.println("jetzt nicht");
          }
        }
      }
      countLeft = 0; 
      timerLinks.stop();
    }

    if(previousStateLeft != val)
    {
      countLeft = 0;
    }
    previousStateLeft = val;
  }
}

void leftButtonPressed()
{
  timerLinks.start();
  timerLinks.configure(1000, speedUp);
}

void rightButtonPressed()
{
  timerRechts.start();
  timerRechts.configure(1000, speedDown);
}



void setup() {
  Serial.begin(9600);
  pinMode(redPin,OUTPUT);
  pinMode(greenPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  pinMode(buttonLeft, INPUT);
  pinMode(buttonRight, INPUT);
  pinMode(bridgePWM, OUTPUT);
  pinMode(bridgeIn1, OUTPUT);
  pinMode(bridgeIn2, OUTPUT);
  //if(timerLinks.configure(1000, speedUp))
  //{
  //  timerLinks.start();
  //}
  attachInterrupt(digitalPinToInterrupt(buttonLeft), leftButtonPressed, RISING);
  attachInterrupt(digitalPinToInterrupt(buttonRight), rightButtonPressed, RISING);
  digitalWrite(bridgeIn1, LOW);
  digitalWrite(bridgeIn2, HIGH);
  analogWrite(bridgePWM, currentSpeed);
  Serial.println("setup");
}



void loop() {
}
