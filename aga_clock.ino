#include "SevenSegmentController.h"
#include "RTC8564.h"
#include "DFPlayer_Mini_Mp3.h"
#include <SoftwareSerial.h>

SevenSegmentController SevenSegmentController;

boolean flag = false;

void setup() {
  struct dateTime dt = {0, 30, 12, 1, 1, 19, 2};
  struct alarmTime at = {31, 12, 1, 2};

  RTC8564.begin(&dt);
  RTC8564.setAlarm(RTC8564_AE_MINUTE, &at, 0);

  String currentClock = "0000";

  Serial.begin(9600);
  mp3_set_serial(Serial);
  mp3_set_volume(10);
}

void loop() {
  struct dateTime dt;
  char RTCTime[20];

  if (RTC8564.getDateTime(&dt) == 0) {
    sprintf(RTCTime, "%2d%2d", dt.hour, dt.minute);
  } else {
    RTC8564.begin();
  }

  if (RTC8564.getAlarmFlag()) {
    if(!flag){
      mp3_play(3);
      flag = true;
    }
    RTC8564.clearAlarmFlag();
  }

  String currentClock = RTCTime;
  SevenSegmentController.displayNumbers(currentClock);
}
