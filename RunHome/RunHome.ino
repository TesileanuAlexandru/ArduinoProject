#include <Stepper.h>

const float STEPS_PER_REV = 42;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
int StepsRequired;
int dir = 12;
Stepper steppermotor1(STEPS_PER_REV,3,4);
int stepsToDo = 15000;

unsigned long previousMotor1Time = millis();
long Motor1Interval = 1;

unsigned long previousMotor2Time = millis();
long Motor2Interval = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(12,OUTPUT);
  //stepperHome(steppermotor1);
}

void loop() {
  // put your main code here, to run repeatedly:
   bool homeSensor = false;
  int cnt = 10000;
  while(!homeSensor){
    steppermotor1.step(10);
    cnt --;
    if(cnt == 0)
      homeSensor = true;
  }
}

void stepperHome(Stepper steppermotor){
  bool homeSensor = false;
  int cnt = 10000;
  while(!homeSensor){
    steppermotor.step(10);
    cnt --;
    if(cnt == 0)
      homeSensor = true;
  }
}
