#include "SevenSegmentController.h"
#include "Arduino.h"

SevenSegmentController::SevenSegmentController() {
  pinMode(SRCLK, OUTPUT);
  pinMode(RCLK, OUTPUT);
  pinMode(SER, OUTPUT);

  for (int i = 0; i < ANODE_PINS_LENGTH; i++) {
    pinMode(ANODE_PINS[i], OUTPUT);
  }
}

void SevenSegmentController::sendSerialData(uint8_t patterns) {
  shiftOut(SER, SRCLK, LSBFIRST, patterns);
  digitalWrite(RCLK, LOW);
  digitalWrite(RCLK, HIGH);
}

void SevenSegmentController::clear() {
  sendSerialData(0b00000000);

  for (int i = 0; i < ANODE_PINS_LENGTH; i++) {
    digitalWrite(ANODE_PINS[i], LOW);
  }
}

void SevenSegmentController::displayNumbers(String currentClock) {
  for (int i = 0; i < ANODE_PINS_LENGTH; i++) {
    clear();
    digitalWrite(ANODE_PINS[i], HIGH);
    sendSerialData(PATTERNS[String(currentClock[i]).toInt()]);
    delay(1);
  }
}
