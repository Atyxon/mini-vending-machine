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
  MotorHandler(PCF8574 &pcfRef, int pinArg1, int pinArg2, int pinArg3, int pinArg4) : pcf(pcfRef) 
  {
    pin1 = pinArg1;
    pin2 = pinArg2;
    pin3 = pinArg3;
    pin4 = pinArg4;
  }

  void Init()
  {
    pcf.write(pin1, 0);
    pcf.write(pin2, 0);
    pcf.write(pin3, 0);
    pcf.write(pin4, 0);
  }
  void rotate()
  {
    for (int i = 0; i < step_revolution; i++)
    {
      OneStep(false);
      delay(2);
    }
    disable();
  }
  void OneStep(bool dir)
  {
    if(dir)
    {
      switch(step_number)
      {
        case 0:
          pcf.write(pin1, 1);
          pcf.write(pin2, 0);
          pcf.write(pin3, 0);
          pcf.write(pin4, 0);
        break;
        case 1:
          pcf.write(pin1, 0);
          pcf.write(pin2, 1);
          pcf.write(pin3, 0);
          pcf.write(pin4, 0);
        break;
        case 2:
          pcf.write(pin1, 0);
          pcf.write(pin2, 0);
          pcf.write(pin3, 1);
          pcf.write(pin4, 0);
        break;
        case 3:
          pcf.write(pin1, 0);
          pcf.write(pin2, 0);
          pcf.write(pin3, 0);
          pcf.write(pin4, 1);
        break;
        } 
      }else{
        switch(step_number){
      case 0:
        pcf.write(pin1, 0);
        pcf.write(pin2, 0);
        pcf.write(pin3, 0);
        pcf.write(pin4, 1);
      break;
      case 1:
        pcf.write(pin1, 0);
        pcf.write(pin2, 0);
        pcf.write(pin3, 1);
        pcf.write(pin4, 0);
      break;
      case 2:
        pcf.write(pin1, 0);
        pcf.write(pin2, 1);
        pcf.write(pin3, 0);
        pcf.write(pin4, 0);
      break;
      case 3:
        pcf.write(pin1, 1);
        pcf.write(pin2, 0);
        pcf.write(pin3, 0);
        pcf.write(pin4, 0);
      } 
    }
    step_number++;
    if(step_number > 3)
    {
      step_number = 0;
    }
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