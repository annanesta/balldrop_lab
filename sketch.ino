#include <math.h>
#include <Servo.h>
#include "Trigger.h"
#include "Timer.h"
#include "Ball.h"
#include "Motor.h"


Trigger trigger(4);
Servo servo;
Timer ph;
Timer hall;
Ball ball;
Motor motor;

const byte photoSensor_pin = 2;
const byte hallSensor_pin = 3;

float _timeCircle=0;

float startCircle = 0;
float pointTrigCircle = 0;

int k_ph = 0;
float ph_time_prev = 0;

int k_hall = 0;
float hall_time_prev = 0;

bool flag=false;

int buttonState = 0;
int lastButtonState = 0;

int previousPhotoSensor = 0;
int previousHallSensor = 0;

void setup() {

  Serial.begin(9600);
  servo.attach(9);
  //servo.write(35);

  // put your setup code here, to run once:
  pinMode(photoSensor_pin, INPUT);
  pinMode(hallSensor_pin, INPUT);

  Serial.println("Time micros");
  Serial.println("photo | hall");

  // attachInterrupt(digitalPinToInterrupt(photoSensor_pin), pinChangeInterrupt1, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(hallSensor_pin), pinChangeInterrupt2, CHANGE);
}

void loop() {

  int photoValue = digitalRead(photoSensor_pin);
  int hallValue = digitalRead(hallSensor_pin);

  if (photoValue != previousPhotoSensor){
    pinChangeInterrupt1();
    previousPhotoSensor = photoValue;
  }

  if (hallValue != previousHallSensor){
    pinChangeInterrupt2();
    previousHallSensor=hallValue;
  }
  


  if (trigger.triggerPress()) {
    pointTrigCircle = micros();
    Serial.println();
    Serial.println("!!!!!!!!!!!!!!");
    Serial.print("pointTrigCircle = "); Serial.println(pointTrigCircle);
    Serial.println();
    //delay(1500);
    if ((ph.timeCircleGet() - (pointTrigCircle-startCircle)) <= ball.BallTime()){
      // Serial.print("pointTrigCircle = "); Serial.print(pointTrigCircle); Serial.print(" - "); Serial.print("startCircle = "); Serial.println(startCircle);
      // Serial.print("delay (nextCircle()+ball.BallTime()) = "); Serial.println(nextCircle()+ball.BallTime());
      delay ((ph.timeCircleGet()+ball.BallTime())*pow(10,-3)); // micro -> milliseconds
      //delay ((nextCircle()+ball.BallTime())*pow(10,-3)); // micro -> milliseconds

    }
    else{
      Serial.print("(pointTrigCircle-startCircle)-ball.BallTime() = "); Serial.println((pointTrigCircle-startCircle)-ball.BallTime());
      delay(((pointTrigCircle-startCircle)-ball.BallTime())*pow(10,-3)); // micro -> milliseconds
    }

    servo.write(motor.rotate());  // transmit the angle to the servo motor
    delay(100);  // wait for 0.1 second for a smooth movement
    servo.write(motor.rotate());  // transmit the angle to the servo motor

  }else{
    servo.write(35);
  }
}

float nextCircle(){
  float d = hall_ph_time_dif(ph.avarageTimeDifGet(), hall.avarageTimeDifGet());
  float T = circlePlus(hall_ph_time(ph.avarageTimeGet(), hall.avarageTimeGet()), d);
  while (ball.BallTime()>T){
    Serial.print("T = "); Serial.println(T);
    T+=circlePlus(T, d);
  }
  return T;
}

float circlePlus(float a, float b){
  return (a+b);
  //return (hall_ph_time(ph.avarageTimeGet(), hall.avarageTimeGet()) + hall_ph_time_dif(ph.avarageTimeDifGet(), hall.avarageTimeDifGet()));
}

void pinChangeInterrupt1(){
  float currentTime = micros();
  if (k_ph==0){
    startCircle = currentTime;
    Serial.println();
    Serial.println("!!!!!!!!!!!!!!");
    Serial.print("startCircle = "); Serial.println(currentTime);
    Serial.println();
  }
  Serial.print("PH  "); Serial.println(currentTime);
  if (k_ph<12){
    ph.timeCircle(currentTime);
    ph.timeDif(currentTime, ph_time_prev);
    // Serial.print("ph.timeCircleGet() = "); Serial.println(ph.timeCircleGet());
    // Serial.print("ph.timeDifGet() = "); Serial.println(ph.timeDifGet());
    k_ph+=1;
    if (k_ph==11){
      flag=true;
    }
  }else{
    ph.avarageTime(ph.timeCircleGet(), 12);
    ph.avarageTimeDif(ph.timeDifGet(), 12);
    k_ph=0;
  }
  ph_time_prev=currentTime;
}

void pinChangeInterrupt2(){
  float currentTime = micros();
  Serial.print("HALL  "); Serial.println(currentTime);
  if (k_hall<2){
    hall.timeCircle(currentTime);
    hall.timeDif(currentTime, hall_time_prev);
    k_hall+=1;
  }
  else{
    hall.avarageTime(hall.timeCircleGet(), 2);
    hall.avarageTimeDif(hall.timeDifGet(), 2);
    k_hall=0;
  }
  hall_time_prev=currentTime;
}

//ph_time   hall_time
float hall_ph_time(float ph, float hall){
  return ((ph+hall)/2);
}
//ph_time_diff    hall_time_diff
float hall_ph_time_dif(float ph, float hall){
  return ((ph+hall)/2);
}


