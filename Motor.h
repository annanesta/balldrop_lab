//Motor.h
#ifndef Motor_h
#define Motor_h

#include <Arduino.h>

class Motor{
  private:
    int angle;
  public:
    Motor();
    float rotate();
};

#endif