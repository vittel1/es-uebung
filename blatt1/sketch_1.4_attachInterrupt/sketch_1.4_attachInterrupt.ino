int pin_state = LOW;
int button_state = HIGH;

void setup() {
  pinMode(7, OUTPUT);
  pinMode(5, INPUT);
  attachInterrupt(digitalPinToInterrupt(5), blink, RISING);
}

void loop() {
}

void blink() {
  pin_state = !pin_state;
  digitalWrite(7, pin_state);
}
