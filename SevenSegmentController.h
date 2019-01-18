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

  int CATHODE_PINS[4] = {9, 10, 11, 12};
  static const int CATHODE_PINS_LENGTH = 4;

  uint8_t PATTERNS[10] = {
    0b11111100,
    0b01100000,
    0b11011010,
    0b11110010,
    0b01100110,
    0b10110110,
    0b10111110,
    0b11100100,
    0b11111110,
    0b11110110
  };
};

#endif
