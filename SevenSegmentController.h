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

  int ANODE_PINS[4] = {8, 9, 10, 11};
  static const int ANODE_PINS_LENGTH = 4;

  uint8_t PATTERNS[10] = {0b00000011, 0b10011111, 0b00100101, 0b00001101,
                          0b10011001, 0b01001001, 0b01000001, 0b00011011,
                          0b00000001, 0b00001001};
};

#endif
