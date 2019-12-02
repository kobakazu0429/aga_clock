#include "AlarmList.hpp"
#include "DFPlayer_Mini_Mp3.h"
#include "MotorController.h"
#include "RTC8564.h"
#include "SevenSegmentController.h"
#include <SoftwareSerial.h>

// 阿賀小学校         :  0
// 原小学校           :  1
// 市民センター       :  2
// まちづくりセンター :  3
// デバッグ用         : 99

#define MODEL 99

SevenSegmentController SevenSegmentController;
AlarmList AlarmList(MODEL);
MotorController MotorController;

void setup() {
  pinMode(13, INPUT);

  struct dateTime dt = {0, 0, 0, 1, 1, 19, 2};
  RTC8564.begin(&dt);

  setFirstAlarm();

  Serial.begin(9600);
  mp3_set_serial(Serial);
  mp3_set_volume(30);
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
  } else {
    newDatetime = {0,
                   0,
                   datetime.hour + 1,
                   datetime.day,
                   datetime.month,
                   datetime.year,
                   datetime.weekday};
  }

  if (datetime.hour == 23 && datetime.minute == 59) {
    newDatetime = {
        0, 0, 0, datetime.day, datetime.month, datetime.year, datetime.weekday};
  }

  RTC8564.setDateTime(&newDatetime);
}

void resetTimeIfInvalidTime() {
  struct dateTime datetime;
  RTC8564.getDateTime(&datetime);

  if (datetime.hour > 23 || datetime.minute > 59) {
    struct dateTime newDatetime = {0,
                                   0,
                                   0,
                                   datetime.day,
                                   datetime.month,
                                   datetime.year,
                                   datetime.weekday};
    RTC8564.setDateTime(&newDatetime);
  }
}

void setFirstAlarm() {
  int hour = AlarmList.getNextAlarmHour();
  int minutes = AlarmList.getNextAlarmMinutes();
  struct alarmTime at = {minutes, hour, 1, 2};
  RTC8564.setAlarm((RTC8564_AE_MINUTE | RTC8564_AE_HOUR), &at, 0);
}

void playMusic() {
  mp3_play(AlarmList.getMusicNumber());

  int hour = AlarmList.getNextAlarmHour();
  int minutes = AlarmList.getNextAlarmMinutes();

  struct alarmTime at = {minutes, hour, 1, 2};
  RTC8564.setAlarm((RTC8564_AE_MINUTE | RTC8564_AE_HOUR), &at, 0);
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

   resetTimeIfInvalidTime();

  if (RTC8564.getAlarmFlag()) {
    RTC8564.clearAlarmFlag();
    MotorController.move();
    playMusic();
  }

  String currentClock = RTCTime;
  SevenSegmentController.displayNumbers(currentClock);
}
