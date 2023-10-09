//Timer.h
#ifndef Timer_h
#define Timer_h

#include <Arduino.h>

class Timer{
  private:
    float _timeCircle;
    float _timeDif;
    float _avarageTime;
    float _avarageTimeDif;
  public:
    Timer();

    //summerize time segments in a circle
    void timeCircle(float t);
    float timeCircleGet();

    //summerize time changes in a circle
    void timeDif(float t, float pt);
    float timeDifGet();

    //count avarage time for time
    void avarageTime(float t, int d);
    float avarageTimeGet();

    //count avarage time for time changes
    void avarageTimeDif(float t, int d);
    float avarageTimeDifGet();
};

#endif