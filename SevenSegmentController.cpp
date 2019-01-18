#include "Arduino.h"
#include "SevenSegmentController.h"

SevenSegmentController::SevenSegmentController() {
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
