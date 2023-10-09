//Timer.cpp

#include "Timer.h"

Timer::Timer() {
  _timeCircle = 0;
  _timeDif = 0;
  _avarageTime = 0;
  _avarageTimeDif = 0;
};

//summerize time segments in a circle
void Timer::timeCircle(float t){
  _timeCircle+=t;
}
float Timer::timeCircleGet(){
  float a = _timeCircle;
  _timeCircle = 0;
  return a;
}

//summerize time changes in a circle
void Timer::timeDif(float t, float pt){
  _timeDif+=t-pt;
}
float Timer::timeDifGet(){
  float a = _timeDif;
  _timeDif = 0;
  return a;
}

//count avarage time for time
void Timer::avarageTime(float t, int d){
  _avarageTime = t/d;
}
float Timer::avarageTimeGet(){
  float a = _avarageTime;
  _avarageTime = 0;
  return a;
}

//count avarage time for time changes
void Timer::avarageTimeDif(float t, int d){
  _avarageTimeDif = t/d;
}
float Timer::avarageTimeDifGet(){
  float a = _avarageTimeDif;
  _avarageTimeDif = 0;
  return a;
}