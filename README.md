# aga_clock

## Usage

```bash
ln -s path/to/aga_clock/libs/RTC8564/RTC8564.h path/to/aga_clock/RTC8564.h
ln -s path/to/aga_clock/libs/RTC8564/RTC8564.cpp path/to/aga_clock/RTC8564.cpp

ln -s path/to/aga_clock/libs/DFPlayer-Mini-mp3/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.h path/to/aga_clock/DFPlayer_Mini_Mp3.h
ln -s path/to/aga_clock/libs/DFPlayer-Mini-mp3/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp path/to/aga_clock/DFPlayer_Mini_Mp3.cpp
```

## Environment Variables

### 阿賀小学校

```c
// aga_clock.ino
int model = 1;
```

### 原小学校

```c
// aga_clock.ino
int model = 2;
```

### 市民センター

```c
// aga_clock.ino
int model = 3;
```

### まちづくりセンター

```c
// aga_clock.ino
int model = 4;
```

## Libraries

1. [garretlab/RTC8564](https://github.com/garretlab/RTC8564)
2. [DFRobot/DFPlayer-Mini-mp3](https://github.com/DFRobot/DFPlayer-Mini-mp3)

## Reference

1. [RTC](https://garretlab.web.fc2.com/arduino/lab/realtime_clock/index.html)
