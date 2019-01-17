#include "SevenSegmentController.h"

SevenSegmentController SevenSegmentController;

void setup() {
}

void loop() {
  String currentClock = "0429";
  SevenSegmentController.displayNumbers(currentClock);
}
