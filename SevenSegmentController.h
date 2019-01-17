#ifndef SevenSegmentController_h
#define SevenSegmentController_h

class SevenSegmentController {
public:
  SevenSegmentController();
  void displayNumbers(String);

private:
  void clear();
  void sendSerialData(uint8_t);

  static const int SRCLK = 5;
  static const int RCLK = 6;
  static const int SER = 7;

  int CATHODE_PINS[4];
  static const int CATHODE_PINS_LENGTH = 4;

  uint8_t PATTERNS[10];
};

#endif
