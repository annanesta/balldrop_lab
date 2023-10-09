//Trigger.cpp

#include "Trigger.h"

Trigger::Trigger(int pin): pin(pin){
  pinMode(pin, INPUT);
}
    
bool Trigger::triggerPress(){
  int triggerState = digitalRead(pin);
  //Serial.println(this->pin);
  if (triggerState == HIGH){
    return true;
  }else{
    return false;
  }
}
