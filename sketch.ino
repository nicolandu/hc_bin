#include <string>
#include <map>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

std::string text = "";

std::map<std::string, std::string> letters =
{{".-","A"}, {"-...","B"}, {"-.-.","C"}, {"-..","D"},
{".","E"}, {"..-.","F"}, {"--.","G"}, {"....","H"},
{"..","I"}, {".---","J"}, {"-.-","K"}, {".-..","L"},
{"--","M"}, {"-.","N"}, {"---","O"}, {".--.","P"},
{"--.-","Q"}, {".-.","R"}, {"...","S"}, {"-","T"},
{"..-","U"}, {"...-","V"}, {".--","W"}, {"-..-","X"},
{"-.--","Y"}, {"--..","Z"}, {".----","1"}, {"..---","2"},
{"...--","3"}, {"....-","4"}, {".....","5"}, {"-....","6"},
{"--...","7"}, {"---..","8"}, {"----.","9"}, {"-----","0"},
{"...---...","SOS"}};
unsigned char dash[] = {
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};

unsigned char dot[] = {
  0b00000,
  0b00000,
  0b00000,
  0b01100,
  0b01100,
  0b00000,
  0b00000,
  0b00000
};

void setup() {
  Serial.begin(9600);
  pinMode(27, INPUT_PULLUP);
  lcd.begin(16, 2);
  lcd.createChar(0, dash);
  lcd.createChar(1, dot);
}

void loop() {
  while (digitalRead(27) != LOW) {
    delay(20);
  };
  std::string seq = "";

  // clear bottom row
  lcd.setCursor(0, 1);
  lcd.print("                ");
  lcd.setCursor(0, 1);
  bool in_word = true;
  for (bool in_letter = true; in_letter;) {

    unsigned long long start = millis();
    while (digitalRead(27) != HIGH) {
      delay(20);
    };

    char c = ((millis() - start) > 200) ? '-' : '.';
    Serial.print(c);
    lcd.setCursor(min(seq.length(),15), 1);
    // 0 for -, 1 for .
    lcd.write(static_cast<unsigned char>(c=='.'));
    seq += c;

    start = millis();

    while (digitalRead(27) != LOW && (millis() - start <= 800)) {
      auto elem = letters.find(seq);
      if (elem != letters.end()) {
        auto tmp = text + letters[seq];
        auto len = tmp.length();
        if (len > 16) {
          tmp = tmp.substr(len-16, len);
        }
        lcd.setCursor(0, 0);
        lcd.print(tmp.c_str());
      }
      delay(20);
    };
    if ((millis() - start) > 200) in_letter = false;
    if ((millis() - start) > 800) in_word = false;
  }
  auto elem = letters.find(seq);
  if (elem != letters.end()) {
    Serial.print(' ');
    Serial.println(letters[seq].c_str());

    text += letters[seq];
    auto len = text.length();
    if (len > 16) {
      text = text.substr(len-16, len);
    }
  } else {
    Serial.println(" unknown");

  }
  lcd.clear();
  lcd.print(text.c_str());
  if (!in_word) {
    Serial.println();
    text += " ";
  }
}

