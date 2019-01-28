#include "RTC8564.h"
#include "SevenSegmentController.h"

// 阿賀小学校         :  0
// 原小学校           :  1
// 市民センター       :  2
// まちづくりセンター :  3
// デバッグ用         : 99

#define MODEL 99

SevenSegmentController SevenSegmentController;

void setup() {
  pinMode(13, INPUT);

  struct dateTime dt = {0, 0, 0, 1, 1, 19, 2};
  RTC8564.begin(&dt);
}

void addMinutes() {
  struct dateTime datetime;
  RTC8564.getDateTime(&datetime);

  struct dateTime newDatetime;

  if (datetime.minute < 59) {
    newDatetime = {0,
                   datetime.minute + 1,
                   datetime.hour,
                   datetime.day,
                   datetime.month,
                   datetime.year,
                   datetime.weekday};
  }

  if (datetime.minute == 59) {
    newDatetime = {0,
                   0,
                   datetime.hour + 1,
                   datetime.day,
                   datetime.month,
                   datetime.year,
                   datetime.weekday};
  }

  if (datetime.hour == 23 && datetime.minute == 59) {
    newDatetime = {0,
                   0,
                   0,
                   datetime.day,
                   datetime.month,
                   datetime.year,
                   datetime.weekday};
  }

  RTC8564.setDateTime(&newDatetime);
}

void loop() {
  struct dateTime dt;
  char RTCTime[4];

  if (digitalRead(13) == HIGH) {
    addMinutes();
    delay(100);
  }

  if (RTC8564.getDateTime(&dt) == 0) {
    sprintf(RTCTime, "%2d%2d", dt.hour, dt.minute);
  }

  String currentClock = RTCTime;
  SevenSegmentController.displayNumbers(currentClock);
}
