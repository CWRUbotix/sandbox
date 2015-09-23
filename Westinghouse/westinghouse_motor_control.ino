#include <Servo.h>
int pinThrottle = 2;
int pinSteering = 3;
int pinLeftMotor = 4;
int pinRightMotor = 5;

volatile unsigned long throttleStart;
volatile unsigned long throttleOut;
volatile unsigned long steeringStart;
volatile unsigned long steeringOut;

Servo leftMotor;
Servo rightMotor;

// On change on throttle pin
void throttleChange() {
	if(digitalRead(pinThrottle) {
		throttleStart = micros();
	} else {
		throttleOut = (micros() - throttleStart - 1000) * 180 / 1000;
	}
}

// On change on throttle pin
void steeringChange() {
	if(digitalRead(pinSteering) {
		steeringStart = micros();
	} else {
		steeringOut = (micros() - steeringStart - 1000) * 180 / 1000;
	}
}

// Setup Loop
void setup ()
{
	// Define pin directions
	pinMode(pinThrottle, INPUT);
	pinMode(pinSteering, INPUT);
	pinMode(pinLeftMotor, OUTPUT);
	pinMode(pinRightMotor, OUTPUT);
	// Attach motors
	leftMotor.attach(pinLeftMotor);
	rightMotor.attach(pinRightMotor);
	// Attach interrupts (done last to make sure pin direction is defined first)
	attachInterrupt(digitalPinToInterrupt (pinThrottle), throttleChange, CHANGE);
	attachInterrupt(digitalPinToInterrupt (pinSteering), steeringChange, CHANGE);
}

// Run loop
void loop ()
{
	// Math will be along the lines of:
	// leftMotor.write(throttleOut/2 + (steeringOut - middle)/2)
	// rightMotor.write(throttleOut/2 - (steeringOut - middle)/2)
	// Where middle is the middle value of the pwm range in microseconds
	leftMotor.write(throttleOut);
	rightMotor.write(throttleOut);
}
