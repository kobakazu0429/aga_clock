#include "SevenSegmentController.h"
#include "RTC8564.h"

SevenSegmentController SevenSegmentController;

void setup() {
  struct dateTime dt = {0, 30, 12, 1, 1, 19, 2};
  char s[20];

  RTC8564.begin(&dt);
  String currentClock = "0000";
}

void loop() {
  struct dateTime dt;
  char s[20];

  if (RTC8564.getDateTime(&dt) == 0) {
    sprintf(s, "%2d%2d", dt.hour, dt.minute);
  } else {
    RTC8564.begin();
  }

  String currentClock = s;
  SevenSegmentController.displayNumbers(currentClock);
}
