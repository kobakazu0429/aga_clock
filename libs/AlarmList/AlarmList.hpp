#ifndef AlarmList_h
#define AlarmList_h

class AlarmList
{
public:
  AlarmList(int model);
  int getMusicNumber();
  int getNextAlarmHour();
  int getNextAlarmMinutes();

private:
  int _model = 0;
  int _next = 0;

  struct Alarm {
    int index;
    int nextIndex;
    int alarmHour;
    int alarmMinutes;
    int musicNumber;
  };

  Alarm AlarmRecords[4][4];
};

#endif
