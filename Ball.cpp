//Ball.cpp
#include "Ball.h"

Ball::Ball(){
  g = 9.8; // m/s^2
  h = 0.7; //m  
  v = sqrt(2*g*h);
};
float Ball::BallTime(){
  return (h/v)*pow(10, 6); //micros
}