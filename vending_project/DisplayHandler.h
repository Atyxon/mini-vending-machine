#ifndef DISPLAY_HANDLER_CLASS_H
#define DISPLAY_HANDLER_CLASS_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "UserClass.h"

#define DISPLAY_USER_TIME 5
#define DISPLAY_SELECTED_ITEM_TIME 8
#define DISPLAY_TRANSACTION_RESULT_TIME 3
#define DISPLAY_ISSUE_TIME 1

class DisplayHandler {
private:
  LiquidCrystal_I2C lcd;
  unsigned long previousMillis = 0;
  const unsigned long interval = 1000;  // 1 second interval

public:
  float timerValue = 0;
  bool transactionScreenActive = false;
  DisplayHandler() : lcd(0x27, 20, 4) {}
  void Init()
  {
    lcd.begin();
    lcd.backlight();

    for (int i = 0; i < 3; i++)
    {
      lcd.clear();
      lcd.print("Starting.");
      delay(500);
      lcd.clear();
      lcd.print("Starting..");
      delay(500);
      lcd.clear();
      lcd.print("Starting...");
      delay(500);
    }
    displayMainView();
  }
  void processTimer()
  {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) 
    {
      previousMillis = currentMillis;

      if (timerValue > 0) {
        --timerValue;
      }

      if (timerValue == 0) {
        displayMainView();
        transactionScreenActive = false;
        timerValue = -1;
      }
    }
  }
  void displayMainView()
  {
    lcd.clear();
    lcd.print("Mini vending machine");
    lcd.setCursor(0,1);
    lcd.print("Version 1.2");
  }
  void displayUser(User user)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hello " + user.name + "!");
    lcd.setCursor(0,1);
    lcd.print("Credits: " + String(user.credits));
    timerValue = DISPLAY_USER_TIME;
  }
  void displaySelectMenu(String itemName, float price)
  {
    transactionScreenActive = true;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Selected: " + itemName);
    lcd.setCursor(0,1);
    lcd.print("Cost: " + String(price) + " credit(s)");
    timerValue = DISPLAY_SELECTED_ITEM_TIME;
  }
  void displayUnknownCard()
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Unknown card ID!");
    timerValue = DISPLAY_USER_TIME;
  }
  void displayInsufficientCredits()
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("insufficient credits");
    timerValue = DISPLAY_USER_TIME;
  }
    void displayPurchaseComplete(String itemName)
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Transaction complete");
    lcd.setCursor(0,1);
    lcd.print("Purchased: " + itemName);
    lcd.setCursor(0,3);
    lcd.print("Please wait...");
    timerValue = DISPLAY_ISSUE_TIME;
  }
};

#endif