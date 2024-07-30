void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(27, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(27) == LOW) {
    Serial.println("a");
  }
  Serial.println("b");
}
