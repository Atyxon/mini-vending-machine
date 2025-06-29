#ifndef USER_CLASS_H
#define USER_CLASS_H

#include <Arduino.h>

class User {
public:
    int id;
    String cardId;
    String name;
    float credits;

    // Constructor
    User(int _id, String _cardId, String _name, float _credits) {
        id = _id;
        cardId = _cardId;
        name = _name;
        credits = _credits;
    }

    // Method to add credits
    void addCredits(float amount) {
        if (amount < 0) 
          return;
        credits += amount;
    }

    // Method to deduct credits
    bool deductCredits(float amount) {
        if (amount < 0) 
          return false;
        if (credits >= amount) {
            credits -= amount;
            return true;
        }
        return false; // Not enough credits
    }

    // Display user info
    void printUser() {
        Serial.print("ID: "); Serial.println(id);
        Serial.print("Card ID: "); Serial.println(cardId);
        Serial.print("Name: "); Serial.println(name);
        Serial.print("Credits: "); Serial.println(credits);
    }
};

#endif