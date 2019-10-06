#include "MotorController.h"
#include "Arduino.h"

MotorController::MotorController() {
  pinMode(SPEED_PWM, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void MotorController::brake() {
  digitalWrite(IN1, BRAKE[0]);
  digitalWrite(IN2, BRAKE[1]);
}

void MotorController::open() {
  digitalWrite(IN1, POSITIVE_ROTATION[0]);
  digitalWrite(IN2, POSITIVE_ROTATION[1]);
  analogWrite(SPEED_PWM, SPEED);
  delay(DURATION);
  brake();
}

void MotorController::close() {
  digitalWrite(IN1, REVERSE_ROTATION[0]);
  digitalWrite(IN2, REVERSE_ROTATION[1]);
  analogWrite(SPEED_PWM, SPEED);
  delay(DURATION);
  brake();
}

void MotorController::move() {
  open();
  // TODO: discussion that how moving this
  delay(1000);
  close();
}
