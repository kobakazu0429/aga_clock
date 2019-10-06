#ifndef MotorController_h
#define MotorController_h

class MotorController {
public:
  MotorController();
  void move();

private:
  void open();
  void close();
  void brake();

  static const int SPEED_PWM = 3;
  static const int IN1 = 12;
  static const int IN2 = 13;

  static const int SPEED_MIN = 0;
  static const int SPEED_MAX = 255;
  static const int SPEED = SPEED_MAX;

  static const int DURATION = 7800;

  static const int STOP = {LOW, LOW};
  static const int POSITIVE_ROTATION = {HIGH, LOW};
  static const int REVERSE_ROTATION = {LOW, HIGH};
  static const int BRAKE = {HIGH, HIGH};
};

#endif
