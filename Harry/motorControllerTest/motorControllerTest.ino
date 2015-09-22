//motor controller code

int motorOneAddress = 128;
int motorOnePin = 1;

void setup() {
  Serial.begin(9600); //pc connection
  pinMode(motorOnePin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}

void sendSerialPacket(int address, int command, int value) {
  Serial1.write(address);
  Serial1.write(command);
  Serial1.write(value);
  Serial1.write((address + command + value) & 0B01111111); //checksum
}

//command 0, 1, 4, 5 drive motor by speed
//motor = 1 or 2. indicates which motor to drive
//speed is from 0 to 127
bool driveForwardMotor(int address, int motor, int speed) {
  if(motor<0 || motor>2) {
    return(false);
  }
  if(speed<0 || speed>127) {
    return(false);
  }
  int command;
  if(motor==1) {
    command = 0;
  }
  if(motor==2) {
    command = 4;
  }
  if(speed<0) {
    command++;//commands 0 and 4 drive forwards. 1 and 5 backwards
    speed *= -1;
  }
  sendSerialPacket(address, command, speed);
  return(true);
}

//command 2 set min voltage
//takes DESIRED voltage, not serial value
//value = (desired volts-6)*5
bool setMinVoltage(int address, int desiredMinVoltage) {
  int command = 2;
  int value = (desiredMinVoltage-6)*5;
  if(value<0 || value>120) {
    return(false);
  }
  sendSerialPacket(address, command, value);
  return(true);
}

//command 3 set max voltage
//takes DESIRED voltage, not serial value
//value = desired volts*5.12
bool setMaxVoltage(int address, int desiredMaxVoltage) {
  int command = 3;
  int value = (int) (((double) desiredMaxVoltage)*5.12);
  if(value<0) {
    return(false);
  }
  sendSerialPacket(address, command, value);
  return(true);
}

//command 15 set baud rate
bool setBaudRate(int address, int baudRate) {
  int command = 15;
  int acceptableBaudRates[] {2400, 9600, 19200, 38400, 115200};
  //test if baudRate is an acceptable one
  bool contains = false;
  for(int i=0; i<sizeof(acceptableBaudRates); i++) {
    if(baudRate==acceptableBaudRates[i]) {
      contains=true;
    }
  }
  if(!contains) {
    return(false);
  }

  sendSerialPacket(address, command, baudRate);
  return(true);
}

//command 16 set ramping (ramping time is delay between full forward and full reverse speed)
//takes SERIAL VALUE not actual time
// 1~10 fast ramp =256/(~1000*value)
// 11~80 slow/intermediate ramp =256/(15.25*(value-10))
bool setRamping(int address, int value) {
  int command = 16;
  if(value<1 || value > 80) {
    return(false);
  }
  sendSerialPacket(address, command, value);
  return(true);
}

//command 17 set deadband (Range of commands interpreted as stop)
//127-command < motors off < 128 + command
bool setDeadband(int address, int deadband) {
  int command = 17;
  if(deadband<0 || deadband > 127) {
    return(false);
  }
  sendSerialPacket(address, command, deadband);
  return(true);
}

