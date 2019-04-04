int pin_state = LOW;
int button_state = HIGH;

void setup() {
  pinMode(7, OUTPUT);
  pinMode(5, INPUT);
}

void loop() {
  int val = digitalRead(5);
  if(val != button_state) {
    pin_state = !pin_state;
    digitalWrite(7, pin_state);
  }
}
