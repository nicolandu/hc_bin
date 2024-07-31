#include <algorithm>
#include <string>
#include <list>

const std::array<std::string, 4> letters = {".-", "-...", "-.-.", "-.."};

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(27, INPUT_PULLUP);
  while (digitalRead(27) != LOW) {};
}

void loop() {
  std::string seq = "";
  for (bool in_word = true; in_word;) {

    unsigned long long delta = millis();
    while (digitalRead(27) != HIGH) {};
    delta = millis() - delta;

    seq += (delta > 300) ? '-' : '.';
    Serial.print(delta);

    delta = millis();
    while (digitalRead(27) != LOW) {};
    delta = millis() - delta;
    Serial.println(delta);

    if (delta > 300) in_word = false;
  }
  auto it = std::find(letters.begin(), letters.end(), seq);
  if (it != letters.end()) {
    Serial.print('A'+(it-letters.begin()));
  }
}
