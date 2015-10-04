#include <Servo.h>

#define STEERING_CTRL_PIN 2
#define THROTTLE_CTRL_PIN 3
#define LEFT_MOTOR_PIN 4
#define RIGHT_MOTOR_PIN 5

volatile int steeringStartTime;
volatile int steeringTime;
volatile int throttleStartTime;
volatile int throttleTime;
volatile int throttleTimeOld;
volatile int leftMotorValue;
volatile int rightMotorValue;
Servo leftMotor;
Servo rightMotor;

void getSteeringTime () {
  unsigned int currentTime = micros ();

  if (currentTime - steeringStartTime > 2000)
    steeringStartTime = currentTime;
  else {
    steeringTime = currentTime - steeringStartTime;
    steeringTime -= 1000;
  }
}

void getThrottleTime () {
  unsigned int currentTime = micros ();

  if (currentTime - throttleStartTime > 2000)
    throttleStartTime = currentTime;
  else {
    throttleTime = currentTime - throttleStartTime;
    throttleTime -= 1000;
    leftMotorValue = throttleTime;
    rightMotorValue = throttleTime;
    leftMotorValue += steeringTime - 500;
    rightMotorValue -= steeringTime - 500;
    if (leftMotorValue > 1000)
      leftMotorValue = 1000;
    if (leftMotorValue < 0)
      leftMotorValue = 0;
    if (leftMotorValue < 550 && leftMotorValue > 450)
      leftMotorValue = 500;
    if (rightMotorValue > 1000)
      rightMotorValue = 1000;
    if (rightMotorValue < 0)
      rightMotorValue = 0;
    if (rightMotorValue < 550 && rightMotorValue > 450)
      rightMotorValue = 500;
    //Throttle control goes here
  }
}

void setup() {
  pinMode (THROTTLE_CTRL_PIN, INPUT);
  pinMode (STEERING_CTRL_PIN, INPUT);
  attachInterrupt (digitalPinToInterrupt(STEERING_CTRL_PIN), getSteeringTime, CHANGE);
  attachInterrupt (digitalPinToInterrupt(THROTTLE_CTRL_PIN), getThrottleTime, CHANGE);
  leftMotor.attach (LEFT_MOTOR_PIN);
  rightMotor.attach (RIGHT_MOTOR_PIN);
  leftMotorValue = 500;
  rightMotorValue = 500;
}

void loop() {
  leftMotor.write (leftMotorValue*180/1000);
  rightMotor.write (rightMotorValue*180/1000);
}
