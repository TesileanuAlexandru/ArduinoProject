#include <Stepper.h>
const float STEPS_PER_REV = 42;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
int StepsRequired;
int dir = 12;
Stepper steppermotor1(STEPS_PER_REV,3,4);

unsigned long previousMotor1Time = millis();
long Motor1Interval = 1;

unsigned long previousMotor2Time = millis();
long Motor2Interval = 10;

void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(12,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(2) == HIGH) {
  digitalWrite(12,LOW);
  } 
  else {
    digitalWrite(12,LOW);
  }
  steppermotor1.setSpeed(4000);
  unsigned long currentMotor1Time = millis();
  unsigned long currentMotor2Time = millis();
  if(currentMotor2Time - previousMotor2Time > Motor2Interval){
    // Spin Motor2
    previousMotor2Time = currentMotor2Time;
  }
  
  if(currentMotor1Time - previousMotor1Time > Motor1Interval){
    steppermotor1.step(1);
    previousMotor1Time = currentMotor1Time;
  }
  
}
