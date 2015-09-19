#include <Servo.h>
#define THROTTLE 2
#define STEERING 3
#define LEFT 4
#define RIGHT 5

volatile unsigned long throttleStart;
volatile unsigned long throttleOut;
volatile unsigned long steeringStart;
volatile unsigned long steeringOut;

Servo leftMotor;
Servo rightMotor;

void startThrottleTime ()
{
  throttleStart = micros ();
}

void stopThrottleTime ()
{
  throttleOut = micros () - throttleStart;
  throttleOut = (throttleOut - 1000) * 180 / 1000;
}

void startSteeringTime ()
{
  steeringStart = micros ();
}

void stopSteeringTime ()
{
  steeringOut = micros () - steeringStart;
  steeringOut = (steeringOut - 1000) * 180 / 1000;
}

void setup ()
{
  attachInterrupt (digitalPinToInterrupt (THROTTLE), startThrottleTime, RISING);
  attachInterrupt (digitalPinToInterrupt (THROTTLE), stopThrottleTime, LOW);
  attachInterrupt (digitalPinToInterrupt (STEERING), startSteeringTime, RISING);
  attachInterrupt (digitalPinToInterrupt (STEERING), stopSteeringTime, LOW); 
  pinMode (THROTTLE, INPUT);
  pinMode (STEERING, INPUT);
  leftMotor.attach (LEFT);
  rightMotor.attach (RIGHT);
}

void loop ()
{
  leftMotor.write (throttleOut);
  rightMotor.write (steeringOut);
}

