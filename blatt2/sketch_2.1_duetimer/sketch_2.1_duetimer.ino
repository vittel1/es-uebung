#include <DueTimer.h>

auto led_pin = 7;
volatile auto led_state = LOW;

//Standardsignal des Buttons
int button_state = HIGH;
DueTimer timer;

int previous_state = LOW;
int count = 0;

void changeLedState(void)
{
  int val = digitalRead(5);
  
  //wenn der Taster betätigt wurde, wird if-Statement betreten
  if(val != button_state)
  {
    //wenn der momentane Zustand und der vorherige übereinstimmen, zähle den counter hoch
    if(previous_state == val) 
    {
      count++;
    }
    //falls der momentane Zustand und der vorherige nicht übereinstimmen, prellt der Taster noch
    else
    {
      count = 0;
    }

    //wenn state über 30 ms gleichgeblieben ist, wird davon ausgegangen, dass
    //das Signal nun konstant bleibt und die gewünschte Aktion wird ausgeführt und
    //der Timer wird angehalten, bis der Knopf erneut gedrückt wird (siehe interrupt)
    if(count == 30)
    {
      led_state = !led_state;
      count = 0; 
      timer.stop();
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
  digitalWrite(led_pin, led_state);
}
