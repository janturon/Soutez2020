#define PIN_ENABLED 10
#define PIN_LEDENABLED 9
#define PIN_RED 3
#define PIN_GREEN 5
#define PIN_BLUE 6
#define PIN_POT A1

#include "module.cpp"

class RGBLed {
protected:
  byte r,g,b;
public:
  RGBLed(byte r, byte g, byte b) : r(r), g(g), b(b) {
    pinMode(r, OUTPUT); digitalWrite(r, LOW);
    pinMode(g, OUTPUT); digitalWrite(g, LOW);
    pinMode(b, OUTPUT); digitalWrite(b, LOW);
  }
  void setHue(byte h) {
    byte R = map(constrain(h, 0, 85), 0, 85, 255, 0);
    byte G = h<128 ? map(h, 0, 127, 0, 255) : map(h, 127, 255, 255, 0);
    byte B = map(constrain(h, 170, 255)-170, 0, 85, 0, 255);
    analogWrite(r, R);
    analogWrite(g, G);
    analogWrite(b, B);
  }
  void reset() {
    digitalWrite(r, LOW);
    digitalWrite(g, LOW);
    digitalWrite(b, LOW);
  }
};

RGBLed led(PIN_RED, PIN_GREEN, PIN_BLUE);
Module module(PIN_ENABLED, PIN_LEDENABLED);

void setup() {
  Serial.begin(115200);
}

void loop() {
  if(module.isEnabled()) {
    unsigned int value = map(analogRead(PIN_POT), 0, 1024, 0, 255);
    led.setHue(value);
  }
  else {
    led.reset();
    while(!module.isEnabled()) delay(100);
  }
}
