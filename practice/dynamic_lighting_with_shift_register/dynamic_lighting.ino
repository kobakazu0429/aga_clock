#include <MsTimer2.h>

#define SRCLK (5)
#define RCLK (6)
#define SER (7)

const int cathode_pins[] = {9, 10, 11, 12};
const int cathode_pins_length = sizeof(cathode_pins) / sizeof(cathode_pins[0]);

const uint8_t PATTERNS[] = {0b11111100, 0b01100000, 0b11011010, 0b11110010,
                            0b01100110, 0b10110110, 0b10111110, 0b11100100,
                            0b11111110, 0b11110110};

int currentNum = 0;

void setup() {
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SER, OUTPUT);

  for (int i = 0; i < cathode_pins_length; i++) {
    pinMode(cathode_pins[i], OUTPUT);
  }

  MsTimer2::set(1000, countUp);
  MsTimer2::start();
}

void clearSegments() {
  sendSerialData(0b00000000);

  for (int i = 0; i < cathode_pins_length; i++) {
    digitalWrite(cathode_pins[i], HIGH);
  }
}

void sendSerialData(uint8_t data) {
  shiftOut(SER, SRCLK, LSBFIRST, data);
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH);
}

void displayNumbers() {
  for (int i = 0; i < cathode_pins_length; i++){
    clearSegments();
    digitalWrite(cathode_pins[i], LOW);
    int num = getNum(i);
    sendSerialData(PATTERNS[num]);
    delay(1);
  }
}

int getNum(int id) {
  char parsed[24] = "";
  sprintf(parsed, "%04d", currentNum);

  String parsed_num = String(parsed);

  return String(parsed_num[id]).toInt();
}

void countUp() {
  currentNum++;
}

void loop() {
  displayNumbers();
}
