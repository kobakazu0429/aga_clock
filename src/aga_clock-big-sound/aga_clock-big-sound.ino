#include "DFPlayer_Mini_Mp3.h"
#include "RTC8564.h"
#include "SevenSegmentController.h"
#include <SoftwareSerial.h>

int model = 3;
boolean isPlaying = false;
int next = 1;

SevenSegmentController SevenSegmentController;

void setup() {
  pinMode(13, INPUT);

  struct dateTime dt = {0, 0, 13, 1, 1, 19, 2};
  struct alarmTime at = {5, 13, 1, 2};

  RTC8564.begin(&dt);
  RTC8564.setAlarm((RTC8564_AE_MINUTE | RTC8564_AE_HOUR), &at, 0);

  Serial.begin(9600);
  mp3_set_serial(Serial);
  mp3_set_volume(5);
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

void playMusic() {
  // mp3_play(4);

  if (next == 1) {
    mp3_play(3);
    struct alarmTime at = {10, 13, 1, 2};
    RTC8564.setAlarm((RTC8564_AE_MINUTE | RTC8564_AE_HOUR), &at, 0);
    next = 2;
  } else if (next == 2) {
    mp3_play(4);
    struct alarmTime at = {15, 13, 1, 2};
    RTC8564.setAlarm((RTC8564_AE_MINUTE | RTC8564_AE_HOUR), &at, 0);
    next = 1;
  }
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

  if (RTC8564.getAlarmFlag()) {
    RTC8564.clearAlarmFlag();
    playMusic();
  }

  String currentClock = RTCTime;
  SevenSegmentController.displayNumbers(currentClock);
}
