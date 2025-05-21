/*
 * --------------------------------------
 *             MFRC522      Arduino      
 *             Reader/PCD   Uno/101      
 * Signal      Pin          Pin          
 * --------------------------------------
 * RST/Reset   RST          9            
 * SPI SS      SDA(SS)      10           
 * SPI MOSI    MOSI         11 / ICSP-4  
 * SPI MISO    MISO         12 / ICSP-1  
 * SPI SCK     SCK          13 / ICSP-3  
 */

#include <SPI.h>
#include <MFRC522.h>
#include "UserClass.h"
#include "ItemClass.h"
#include "DisplayHandler.h"
#include "ButtonHandler.h"
#include "BuzzerHandler.h"
#include "MotorHandler.h"

#define RST_PIN 9
#define SS_PIN 10
#define ITEM_NOT_SELECTED -1

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance

DisplayHandler displayHandler;
PCF8574 pcf1(0x21);
PCF8574 pcf2(0x22);

ButtonHandler buttonHandler(pcf1);
BuzzerHandler buzzer(pcf1);

MotorHandler motorHandlers[] = {
  MotorHandler(pcf2, 4, 5, 6, 7),
  MotorHandler(pcf2, 0, 1, 2, 3),
  MotorHandler(pcf1, 4, 5, 6, 7)
};
User users[] = {
  User(0, "9e 17 84 9f", "Jan", 50.0),
  User(1, "13 51 86 9f", "Dawid", 1)
};
Item items[] = {
  Item(0, "Kit Kat", 3.8),
  Item(1, "3Bit", 2.5),
  Item(2, "Lion", 2.9)
};

int lastButtonState = 0;
int selectedItem = ITEM_NOT_SELECTED;
const int numUsers = sizeof(users) / sizeof(users[0]);
const int displayUserTime = 4;
const int displaySelectedItem = 8;

void setup() {
  Wire.begin();
	Serial.begin(9600);		// Initialize serial communications with the PC
	//while (!Serial);		// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)

	Serial.println(F("Starting program..."));
  InitMotorInterface();
	SPI.begin();			// Init SPI bus
	mfrc522.PCD_Init();		// Init MFRC522
	delay(4);				// Optional delay. Some board do need more time after init to be ready, see Readme
	mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD - MFRC522 Card Reader details
  displayHandler.Init();
  for (MotorHandler &motor : motorHandlers)
  {
    motor.Init();
  }

	Serial.println(F("Program started!"));
}

void loop() {
  int buttonState = buttonHandler.ButtonListen();
  displayHandler.processTimer();

  if(buttonState != lastButtonState)
  {
    lastButtonState = buttonState;

    if(buttonState == 1)
    {
      selectedItem = 0;
      displayHandler.displaySelectMenu(items[selectedItem].name, items[selectedItem].cost);
      buzzer.ButtonBuzz();
    }
    else if(buttonState == 2)
    {
      selectedItem = 1;
      displayHandler.displaySelectMenu(items[selectedItem].name, items[selectedItem].cost);
      buzzer.ButtonBuzz();
    }
    else if(buttonState == 3)
    {
      selectedItem = 2;
      displayHandler.displaySelectMenu(items[selectedItem].name, items[selectedItem].cost);
      buzzer.ButtonBuzz();
    }
  }

	// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
	if (mfrc522.PICC_IsNewCardPresent() == false) {
		return;
	}

	// Select one of the cards
	if (mfrc522.PICC_ReadCardSerial() == false) {
		return;
	}

  // Store UID in a temporary variable (String)
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // Append a leading zero if the value is less than 0x10 for better formatting
    if (mfrc522.uid.uidByte[i] < 0x10) {
      uidString += "0";
    }
    uidString += String(mfrc522.uid.uidByte[i], HEX);
    if (i < mfrc522.uid.size - 1) {
      uidString += " ";
    }
  }

  ProcessCardAction(uidString);

  if (displayHandler.timerValue > 0) 
  {
    selectedItem = ITEM_NOT_SELECTED;
  }

  // Halt the card to prevent reading the same one multiple times
  mfrc522.PICC_HaltA();
}

void ProcessCardAction(String cardId)
{
  for (int i = 0; i < numUsers; i++)
  {
    if(cardId == users[i].cardId)
    {
      if(selectedItem == ITEM_NOT_SELECTED || displayHandler.transactionScreenActive == false)
      {
        displayHandler.displayUser(users[i]);
        buzzer.UserReadBuzz();
      }
      else
      {
        PurchaseItem(i);
      }
      return;
    }
  }
  displayHandler.displayUnknownCard();
  buzzer.UnknownCardBuzz();
  Serial.println("Error: Unknown card ID");
}

void PurchaseItem(int userIndex)
{
  if(users[userIndex].credits >= items[selectedItem].cost)
  {
    users[userIndex].credits -= items[selectedItem].cost;
    displayHandler.displayPurchaseComplete(items[selectedItem].name);
    buzzer.PurchaseCompleteBuzz();
    delay(500);
    motorHandlers[selectedItem].rotate();
    delay(500);
  }
  else
  {
    displayHandler.displayInsufficientCredits();
    buzzer.PurchaseFailBuzz() ;
  }
}

// Disable every step motor to save energy
void InitMotorInterface()
{
  pcf1.begin();
  for (int i = 4; i <= 7; i++) {
    pcf1.write(i, 0);
  }

  pcf2.begin();
  for (int i = 0; i <= 7; i++) {
    pcf2.write(i, 0);
  }
}
