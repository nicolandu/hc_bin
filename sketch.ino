#include <string>
#include <map>

std::map<std::string, char> letters = {{".-",'A'}, {"-...",'B'}, {"-.-.",'C'}, {"-..",'D'}, {".",'E'}, {"..-.",'F'}, {"--.",'G'}, {"....",'H'}, {"..",'I'}, {".---",'J'}, {"-.-",'K'}, {".-..",'L'}, {"--",'M'}, {"-.",'N'}, {"---",'O'}, {".--.",'P'}, {"--.-",'Q'}, {".-.",'R'}, {"...",'S'}, {"-",'T'}, {"..-",'U'}, {"...-",'V'}, {".--",'W'}, {"-..-",'X'}, {"-.--",'Y'}, {"--..",'Z'}, {".----",'1'}, {"..---",'2'}};
void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  pinMode(27, INPUT_PULLUP);
}

void loop() {
  while (digitalRead(27) != LOW) {
    delay(20);
  };
  std::string seq = "";
  for (bool in_word = true; in_word;) {

    unsigned long long start = millis();
    while (digitalRead(27) != HIGH) {
      delay(20);
    };

    char c = ((millis() - start) > 200) ? '-' : '.';
    Serial.print(c);
    seq += c;

    start = millis();

    while (digitalRead(27) != LOW && (millis() - start <= 200)) {
      delay(20);
    };
    if ((millis() - start) > 200) in_word = false;
  }
  auto elem = letters.find(seq);
  if (elem != letters.end()) {
    Serial.print(' ');
    Serial.println(letters[seq]);
  } else {
    Serial.println(" unknown");
  }
}

