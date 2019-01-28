#include "Arduino.h"
#include "AlarmList.hpp"

AlarmList::AlarmList(int model)
{
  _model = model;

  // 阿賀小学校
  // _model : 0
  AlarmRecords[0][0] = {0, 1, 10, 40, 0};
  AlarmRecords[0][1] = {1, 0, 13, 25, 1};

  // 原小学校
  // _model : 1
  AlarmRecords[1][0] = {0, 0, 8, 0, 0};

  // 市民センター
  // _model : 2
  AlarmRecords[2][0] = {0, 1, 8, 29, 3};
  AlarmRecords[2][1] = {1, 2, 13, 10, 4};
  AlarmRecords[2][2] = {3, 4, 13, 15, 2};
  AlarmRecords[2][3] = {4, 0, 17, 25, 3};

  // まちづくりセンター
  // _model : 3
  AlarmRecords[3][0] = {0, 1, 12, 0, 0};
  AlarmRecords[3][1] = {1, 0, 17, 0, 1};
}

int AlarmList::getMusicNumber() {
  // struct Alarm {
  //   int index;
  //   int nextIndex;
  //   int alarmHour;
  //   int alarmMinutes;
  //   int musicNumber;
  // };
  struct Alarm _this = AlarmRecords[_model][_next];
  _next = _this.nextIndex;
  return _this.musicNumber;
}

int AlarmList::getNextAlarmHour()
{
  struct Alarm _this = AlarmRecords[_model][_next];
  return _this.alarmHour;
}

int AlarmList::getNextAlarmMinutes()
{
  struct Alarm _this = AlarmRecords[_model][_next];
  return _this.alarmMinutes;
}
