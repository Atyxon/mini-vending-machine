#ifndef BUZZER_HANDLER_CLASS_H
#define BUZZER_HANDLER_CLASS_H

#include <Arduino.h>
#include <PCF8574.h>

#define BUZZER_PIN 3
#define ON 0
#define OFF 1

class BuzzerHandler {
private:
  PCF8574 &pcf;

public:
  BuzzerHandler(PCF8574 &pcfRef) : pcf(pcfRef) {}
  void ButtonBuzz()
  {
    pcf.write(BUZZER_PIN, ON);
    delay(50);
    pcf.write(BUZZER_PIN, OFF);
  }
  void UserReadBuzz()
  {
    pcf.write(BUZZER_PIN, ON);
    delay(100);
    pcf.write(BUZZER_PIN, OFF);
    delay(50);
    pcf.write(BUZZER_PIN, ON);
    delay(100);
    pcf.write(BUZZER_PIN, OFF);
  }
  void PurchaseCompleteBuzz()
  {
    pcf.write(BUZZER_PIN, ON);
    delay(50);
    pcf.write(BUZZER_PIN, OFF);
    delay(50);
    pcf.write(BUZZER_PIN, ON);
    delay(50);
    pcf.write(BUZZER_PIN, OFF);
    delay(50);
    pcf.write(BUZZER_PIN, ON);
    delay(50);
    pcf.write(BUZZER_PIN, OFF);
    delay(50);
    pcf.write(BUZZER_PIN, ON);
    delay(50);
    pcf.write(BUZZER_PIN, OFF);
    delay(50);
    pcf.write(BUZZER_PIN, ON);
    delay(50);
    pcf.write(BUZZER_PIN, OFF);
    delay(50);
    pcf.write(BUZZER_PIN, ON);
    delay(50);
    pcf.write(BUZZER_PIN, OFF);
  }
  void PurchaseFailBuzz()
  {
    pcf.write(BUZZER_PIN, ON);
    delay(800);
    pcf.write(BUZZER_PIN, OFF);
  }
  void UnknownCardBuzz()
  {
    pcf.write(BUZZER_PIN, ON);
    delay(300);
    pcf.write(BUZZER_PIN, OFF);
    delay(100);
    pcf.write(BUZZER_PIN, ON);
    delay(300);
    pcf.write(BUZZER_PIN, OFF);
  }
};

#endif