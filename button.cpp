#include <Arduino.h>

class Button {
protected:
  static const unsigned int debounce = 100;
  byte pin;
  bool hold;
  unsigned long holdTime;
  bool assigned;
public:
  Button() {
    assigned = false;
  }
  Button(byte pin) : pin(pin), hold(false), holdTime(0) {
    assigned = true;
    pinMode(pin, INPUT_PULLUP);
  }
  bool pushed() {
    if(!assigned) return false;
    bool result = false;
    bool value = digitalRead(pin);
    unsigned long now = millis();
    // just pushed and not debouncing
    if(value==LOW && hold==false && now-holdTime>debounce) {
      holdTime = now;
      hold = true;
      result = true;
    }
    // sometimes debounce also occurs on release
    else if(value==HIGH && hold==true && now-holdTime>debounce) {
      holdTime = now;
      hold = false;
    }
    return result;
  }
  operator bool() {
    return pushed();
  }
  void operator=(int value) {
    pin = value;
    hold = false;
    holdTime = 0;
    pinMode(pin, INPUT_PULLUP);
    assigned = true;
  }
};
