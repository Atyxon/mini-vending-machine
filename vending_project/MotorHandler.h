#ifndef MOTOR_HANDLER_CLASS_H
#define MOTOR_HANDLER_CLASS_H

#include <Arduino.h>
#include <PCF8574.h>


class MotorHandler {
private:
  PCF8574 &pcf;
  int step_number = 0;
  int step_revolution = 2048;

public:
  int pin1, pin2, pin3, pin4;
  bool dir;
  MotorHandler(PCF8574 &pcfRef, int pinArg1, int pinArg2, int pinArg3, int pinArg4, bool dirArg) : pcf(pcfRef) 
  {
    pin1 = pinArg1;
    pin2 = pinArg2;
    pin3 = pinArg3;
    pin4 = pinArg4;
    dir = dirArg;
  }
  void rotate()
  {
    for (int i = 0; i < step_revolution; i++)
    {
      OneStep(dir);
      delay(2);
    }
    disable();
  }
  void WritePins(int valPin1, int valPin2, int valPin3, int valPin4)
  {
    pcf.write(pin1, valPin1);
    pcf.write(pin2, valPin2);
    pcf.write(pin3, valPin3);
    pcf.write(pin4, valPin4);
  }

  void OneStep(bool dir)
  {
    if(dir)
    {
      switch(step_number)
      {
        case 0:
          WritePins(1,0,0,0);
        break;
        case 1:
          WritePins(0,1,0,0);
        break;
        case 2: 
          WritePins(0,0,1,0);
        break;
        case 3:
          WritePins(0,0,0,1);
        break;
        } 
      }else{
        switch(step_number){
      case 0:
        WritePins(0,0,0,1);
      break;
      case 1:
        WritePins(0,0,1,0);
      break;
      case 2:
        WritePins(0,1,0,0);
      break;
      case 3:
        WritePins(1,0,0,0);
      } 
    }
    step_number = (step_number + 1) % 4;
  }
  void disable() {
    delay(50);
    pcf.write(pin1, 0);
    pcf.write(pin2, 0);
    pcf.write(pin3, 0);
    pcf.write(pin4, 0);
  }
};

#endif