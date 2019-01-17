#include "Arduino.h"
#include "SevenSegmentController.h"

SevenSegmentController::SevenSegmentController() {
  CATHODE_PINS[0] = 9;
  CATHODE_PINS[1] = 10;
  CATHODE_PINS[2] = 11;
  CATHODE_PINS[3] = 12;

  PATTERNS[0] = 0b11111100;
  PATTERNS[1] = 0b01100000;
  PATTERNS[2] = 0b11011010;
  PATTERNS[3] = 0b11110010;
  PATTERNS[4] = 0b01100110;
  PATTERNS[5] = 0b10110110;
  PATTERNS[6] = 0b10111110;
  PATTERNS[7] = 0b11100100;
  PATTERNS[8] = 0b11111110;
  PATTERNS[9] = 0b11110110;

  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SER, OUTPUT);

  for (int i = 0; i < CATHODE_PINS_LENGTH ; i++) {
    pinMode(CATHODE_PINS[i], OUTPUT);
  }
}

void SevenSegmentController::sendSerialData(uint8_t patterns) {
  shiftOut(SER, SRCLK, LSBFIRST, patterns);
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH);
}

void SevenSegmentController::clear()
{
  sendSerialData(0b00000000);

  for (int i = 0; i < CATHODE_PINS_LENGTH; i++)
  {
    digitalWrite(CATHODE_PINS[i], HIGH);
  }
}

void SevenSegmentController::displayNumbers(String currentClock) {
  for (int i = 0; i < CATHODE_PINS_LENGTH; i++) {
    clear();
    digitalWrite(CATHODE_PINS[i], LOW);
    sendSerialData(PATTERNS[String(currentClock[i]).toInt()]);
    delay(1);
  }
}
