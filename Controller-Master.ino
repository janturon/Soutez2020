
#include "button.cpp"

#define TASKS 2
namespace Tasks {
  byte index = 0;
  byte current = 0;
  byte control[TASKS];
  bool add(byte pin) {
    if(index>=TASKS) return false;
    control[index++] = pin;
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    return true;
  }
  void next() {
    if(index==0) return;
    digitalWrite(control[current], HIGH);
    current = ++current % index;
    digitalWrite(control[current], LOW);
  }
};

Button button;

void setup() {
  button = 6;
  // ground for button
  pinMode(8, OUTPUT); digitalWrite(8, LOW);
  Tasks::add(3);
  Tasks::add(4);
}

void loop() {
  if(button) Tasks::next();
}
