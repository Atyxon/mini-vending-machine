#ifndef BUTTON_HANDLER_CLASS_H
#define BUTTON_HANDLER_CLASS_H

#include <Arduino.h>
#include <PCF8574.h>

#define BUTTON_NOT_PRESSED 0
#define BUTTON_PRESSED 1

class ButtonHandler {
private:
  PCF8574 &pcf;
  int buttonState = 0;

public:
  ButtonHandler(PCF8574 &pcfRef) : pcf(pcfRef) {}
  int ButtonListen()
  {
    int button1 = pcf.read(2);
    int button2 = pcf.read(1);
    int button3 = pcf.read(0);

    if(buttonState == BUTTON_NOT_PRESSED)
    {
      if(button1 == BUTTON_PRESSED)
      {
        Serial.println(F("Pressed button 1"));
        buttonState = 1;
      }
      else if(button2 == BUTTON_PRESSED)
      {
        Serial.println(F("Pressed button 2"));
        buttonState = 2;
      }
      else if(button3 == BUTTON_PRESSED)
      {
        Serial.println(F("Pressed button 3"));
        buttonState = 3;
      }
    }
    else
    {
      if(buttonState == 1 && button1 == BUTTON_NOT_PRESSED)
      {
        buttonState = 0;
      }
      else if(buttonState == 2 && button2 == BUTTON_NOT_PRESSED)
      {
        buttonState = 0;
      }
      else if(buttonState == 3 && button3 == BUTTON_NOT_PRESSED)
      {
        buttonState = 0;
      }
    }
    return buttonState;
  }
};

#endif