#include <DueTimer.h>

auto led_pin = 7;
//volatile auto led_state = LOW;
int button_state = HIGH;
DueTimer timer;

int previous_state = LOW;
int count = 0;
int brightness = 125;

void brightnessUp(void)
{
  int val = digitalRead(5);
  if(val != button_state)
  {
    if(previous_state == val) 
    {
      count++;
    }
    if(count == 30)
    {
      brightness += 50;
      if(brightness > 255) 
      {
        brightness = 255;
      }
      count = 0; 
      timer.stop();
    }
    if(previous_state != val)
    {
      count = 0;
    }
    previous_state = val;
  }
}


void brightnessDown(void)
{
  int val = digitalRead(3);
  if(val != button_state)
  {
    if(previous_state == val) 
    {
      count++;
    }
    if(count == 30)
    {
      brightness -= 50;
      if(brightness < 0) 
      {
        brightness = 0;
      }
      count = 0; 
      timer.stop();
    }
    if(previous_state != val)
    {
      count = 0;
    }
    previous_state = val;
  }
}

void restartLeftPin()
{
  timer.start();
  timer.configure(1000, brightnessUp);
}

void restartRightPin()
{
  timer.start();
  timer.configure(1000, brightnessDown);
}

void setup()
{
  pinMode(led_pin, OUTPUT);
  pinMode(5, INPUT);
  pinMode(3, INPUT);
  // Konfiguration des Hardware-Timers (@ 1 Hz)
  // Syntax: configure(timer_frequency, callback_function)
  if(timer.configure(1000, brightnessUp))
  {
    timer.start();
  }
  attachInterrupt(digitalPinToInterrupt(5), restartLeftPin, RISING);
  attachInterrupt(digitalPinToInterrupt(3), restartRightPin, RISING);
}

void loop()
{
  analogWrite(led_pin, brightness);
}
