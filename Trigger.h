//Trigger.h
#ifndef Trigger_h
#define Trigger_h

#include <Arduino.h>

class Trigger{
  private:
    int pin;
  
  public:
    Trigger(int pin);
    bool triggerPress();
};

#endif