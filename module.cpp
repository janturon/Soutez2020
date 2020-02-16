#include <Arduino.h>

class Module {
  byte en, led;
public:
  Module(byte en, byte led) : en(en), led(led) {
    pinMode(en, INPUT_PULLUP);
    pinMode(led, OUTPUT);
    digitalWrite(led, LOW);
  }
  bool isEnabled() {
    bool result = !digitalRead(en);
    digitalWrite(led, result);
    return result;
  }
};
