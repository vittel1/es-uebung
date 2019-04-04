int pin_state = LOW;

void setup() {
  pinMode(7, OUTPUT);
}

void loop() {
  digitalWrite(7, pin_state);
  delay(2000);
  pin_state = !pin_state;
  digitalWrite(7, pin_state);
  delay(500);
  pin_state = !pin_state;
}
