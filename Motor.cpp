//Motor.cpp
#include "Motor.h"

Motor::Motor(){
  angle= 35;
};
float Motor::rotate(){
  if (angle == 50) {
    angle = 35;  
  } else {
    angle = 50;  
  }
  return (angle);
};