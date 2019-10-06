#!/bin/sh

DIR=$(cd $(dirname $0) && pwd)

echo "Create Libs Symbolic Links"
echo "==========================================="

# aga_clock-big-sound
ln -s $DIR/libs/RTC8564/RTC8564.h                                          $DIR/src/aga_clock-big-sound/RTC8564.h
ln -s $DIR/libs/RTC8564/RTC8564.cpp                                        $DIR/src/aga_clock-big-sound/RTC8564.cpp
ln -s $DIR/libs/DFPlayer-Mini-mp3/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.h    $DIR/src/aga_clock-big-sound/DFPlayer_Mini_Mp3.h
ln -s $DIR/libs/DFPlayer-Mini-mp3/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp  $DIR/src/aga_clock-big-sound/DFPlayer_Mini_Mp3.cpp
ln -s $DIR/libs/SevenSegmentController/SevenSegmentController.h            $DIR/src/aga_clock-big-sound/SevenSegmentController.h
ln -s $DIR/libs/SevenSegmentController/SevenSegmentController.cpp          $DIR/src/aga_clock-big-sound/SevenSegmentController.cpp
ln -s $DIR/libs/AlarmList/AlarmList.cpp                                    $DIR/src/aga_clock-big-sound/AlarmList.cpp
ln -s $DIR/libs/AlarmList/AlarmList.hpp                                    $DIR/src/aga_clock-big-sound/AlarmList.hpp
ln -s $DIR/libs/MotorController/MotorController.cpp                        $DIR/src/aga_clock-big-sound/MotorController.cpp
ln -s $DIR/libs/MotorController/MotorController.h                          $DIR/src/aga_clock-big-sound/MotorController.h
echo "src/aga_clock-big-sound : done"

# aga_clock-small-sound
ln -s $DIR/libs/RTC8564/RTC8564.h                                          $DIR/src/aga_clock-small-sound/RTC8564.h
ln -s $DIR/libs/RTC8564/RTC8564.cpp                                        $DIR/src/aga_clock-small-sound/RTC8564.cpp
ln -s $DIR/libs/DFPlayer-Mini-mp3/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.h    $DIR/src/aga_clock-small-sound/DFPlayer_Mini_Mp3.h
ln -s $DIR/libs/DFPlayer-Mini-mp3/DFPlayer_Mini_Mp3/DFPlayer_Mini_Mp3.cpp  $DIR/src/aga_clock-small-sound/DFPlayer_Mini_Mp3.cpp
ln -s $DIR/libs/SevenSegmentController/SevenSegmentController.h            $DIR/src/aga_clock-small-sound/SevenSegmentController.h
ln -s $DIR/libs/SevenSegmentController/SevenSegmentController.cpp          $DIR/src/aga_clock-small-sound/SevenSegmentController.cpp
ln -s $DIR/libs/AlarmList/AlarmList.cpp                                    $DIR/src/aga_clock-small-sound/AlarmList.cpp
ln -s $DIR/libs/AlarmList/AlarmList.hpp                                    $DIR/src/aga_clock-small-sound/AlarmList.hpp
echo "src/aga_clock-small-sound : done"

# aga_clock-small
ln -s $DIR/libs/RTC8564/RTC8564.h                                          $DIR/src/aga_clock-small/RTC8564.h
ln -s $DIR/libs/RTC8564/RTC8564.cpp                                        $DIR/src/aga_clock-small/RTC8564.cpp
ln -s $DIR/libs/SevenSegmentController/SevenSegmentController.h            $DIR/src/aga_clock-small/SevenSegmentController.h
ln -s $DIR/libs/SevenSegmentController/SevenSegmentController.cpp          $DIR/src/aga_clock-small/SevenSegmentController.cpp
echo "src/aga_clock-small : done"

echo "Create Libs Symbolic Links : done"
echo "==========================================="
