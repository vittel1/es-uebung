#include <DueTimer.h>

auto led_pin = 7;
volatile auto led_state = LOW;
int button_state = HIGH;
DueTimer timer;

int previous_state = LOW;
int count = 0;

void changeLedState(void)
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
      led_state = !led_state;
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

void restart()
{
  timer.start();
}

void setup()
{
  // Konfiguration der Richtung des digitalen I/O Anschlusspins 13
  pinMode(led_pin, OUTPUT);
  pinMode(5, INPUT);
  // Konfiguration des Hardware-Timers (@ 1 Hz)
  // Syntax: configure(timer_frequency, callback_function)
  if(timer.configure(1000, changeLedState))
  {
    timer.start();
  }
  attachInterrupt(digitalPinToInterrupt(5), restart, RISING);
}

void loop()
{
  // Wechsel des Logikpegels am Ausgangspin 13
  digitalWrite(led_pin, led_state);
}
