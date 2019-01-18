#include "DFPlayer_Mini_Mp3.h"
#include "RTC8564.h"
#include "SevenSegmentController.h"
#include <SoftwareSerial.h>

int model = 3;
boolean isPlaying = false;

SevenSegmentController SevenSegmentController;

Serial DFSerial(0, 1);

void setup() {
  pinMode(2, INPUT);
  pinMode(13, INPUT);

  struct dateTime dt = {30, 59, 12, 1, 1, 19, 2};
  RTC8564.begin(&dt);

  String currentClock = "0000";

  DFSerial.begin(9600);
  Serial.begin(115200);

  mp3_set_serial(DFSerial);
  mp3_set_volume(10);
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

  RTC8564.setDateTime(&newDatetime);
}

void playMusic(String now) {
  Serial.println(now);
  Serial.println(model);
  if (!isPlaying) {
    switch (model) {
    case 1: //阿賀小学校
      if (now == "1040")
        mp3_play(1);
      if (now == "1325")
        mp3_play(2);
      break;
    case 2: //原小学校
      if (now == "0800")
        mp3_play(1);
      break;
    case 3: //市民センター
      if (now == "0829")
        mp3_play(1);
      if (now == "1200")
        mp3_play(2);
      if (now == "1300") {
        Serial.println("playing");
        mp3_play(3);
      }
      if (now == "1715")
        mp3_play(4);
      break;
    case 4: //まちづくりセンター
      if (now == "1200")
        mp3_play(1);
      if (now == "1700")
        mp3_play(2);
      break;
    }
    isPlaying = true;
  }
}

void loop() {
  struct dateTime dt;
  char RTCTime[4];

  if (digitalRead(13) == HIGH) {
    addMinutes();
    delay(100);
  }

  if (digitalRead(2) == HIGH) {
    isPlaying = false;
  }

  if (RTC8564.getDateTime(&dt) == 0) {
    sprintf(RTCTime, "%2d%2d", dt.hour, dt.minute);
  }

  playMusic(RTCTime);

  String currentClock = RTCTime;
  SevenSegmentController.displayNumbers(currentClock);
}
