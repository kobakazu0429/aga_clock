#include "Arduino.h"
#include "AlarmList.hpp"

AlarmList::AlarmList(int model)
{
  _model = model == 99 ? 4 : model;

  // struct Alarm {
  //   int index;
  //   int nextIndex;
  //   int alarmHour;
  //   int alarmMinutes;
  //   int musicNumber;
  // };

  // 阿賀小学校
  // _model : 0
  AlarmRecords[0][0] = {0, 1, 10, 40, 1};
  AlarmRecords[0][1] = {1, 0, 13, 25, 2};

  // 原小学校
  // _model : 1
  AlarmRecords[1][0] = {0, 0,  8,  0, 1};

  // 市民センター
  // _model : 2
  AlarmRecords[2][0] = {0, 1,  8, 29, 1};
  AlarmRecords[2][1] = {1, 2, 12,  0, 2};
  AlarmRecords[2][2] = {3, 4, 13,  0, 1};
  AlarmRecords[2][3] = {4, 0, 17, 15, 2};

  // まちづくりセンター
  // _model : 3
  AlarmRecords[3][0] = {0, 1, 12,  0, 1};
  AlarmRecords[3][1] = {1, 0, 17,  0, 2};

  // デバッグ
  // _model : 99
  AlarmRecords[4][0] = {0, 1,  0,  5, 1};
  AlarmRecords[4][1] = {1, 2,  0, 10, 1};
  AlarmRecords[4][2] = {2, 0,  0, 15, 1};
}

int AlarmList::getMusicNumber() {
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
