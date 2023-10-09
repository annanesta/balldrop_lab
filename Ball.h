//Ball.h
#ifndef Ball_h
#define Ball_h

#include <Arduino.h>

class Ball{
  private:
    float g;
    float h;
    float v;
  public:
    Ball();
    float BallTime();
};

#endif