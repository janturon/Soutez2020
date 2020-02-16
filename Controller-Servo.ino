#define PIN_ENABLED 10
#define PIN_LEDENABLED 9
#define PIN_PLAYER1 4
#define PIN_PLAYER2 6
#define PIN_LED1 7
#define PIN_LED2 5
#define PIN_SERVO 13
#define BUTTON_SENSITIVITY 5

#include "module.cpp"
#include "button.cpp"

class SimpleServo {
protected:
  const byte pin;
  unsigned long lastCall;
public:
  SimpleServo(byte pin) : pin(pin), lastCall(0) {
    pinMode(pin, OUTPUT);
  }

  void write(int angle) {
    if(millis()-lastCall<20) return;
    lastCall = millis();
    angle = constrain(angle,-90, 90);
    digitalWrite(pin, HIGH);
    float period = 1.5 + (1.0*angle/90);
    delayMicroseconds(period*1000);
    digitalWrite(pin, LOW);
  }
};

class ButtonGame {
protected:
  int counter, prevCounter;
  Button p1, p2;
  byte led1, led2;
  SimpleServo servo;

  int gameOver(byte led) {
    digitalWrite(led, HIGH);
    delay(2000);
    reset();
  }
public:
  ButtonGame(Button p1, Button p2, byte servoPin) : p1(p1), p2(p2), servo(servoPin) {
    led1 = led2 = 0;
  }
  void setLed(byte led1, byte led2) {
    this->led1 = led1;
    pinMode(led1, OUTPUT);
    this->led2 = led2;
    pinMode(led2, OUTPUT);
  }
  void reset() {
    counter = prevCounter = 0;
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    for(int i=0; i<10; ++i) {
      servo.write(counter);
      delay(20);
    }    
  }
  int play() {
    if(counter==-90) return gameOver(led1);
    else if(counter==90) return gameOver(led2);
    if(p1) counter+= BUTTON_SENSITIVITY;
    if(p2) counter-= BUTTON_SENSITIVITY;
    if(counter==prevCounter) return 0;
    servo.write(counter);
    prevCounter = counter;
    return 0;
  }
};

ButtonGame game(PIN_PLAYER1, PIN_PLAYER2, PIN_SERVO);
Module module(PIN_ENABLED, PIN_LEDENABLED);

void setup() {
  pinMode(8, INPUT); // grounded
  game.setLed(PIN_LED1, PIN_LED2);
  game.reset();
}

void loop() {
  if(module.isEnabled()) game.play();
  else {
    game.reset();
    while(!module.isEnabled()) delay(100);
  }
}
