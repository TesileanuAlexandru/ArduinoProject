
#include <Stepper.h>

class ExtendedStepper{
  private:
    int postion;
  public:
    Stepper stepper;
    ExtendedStepper(float stepsPerRev, int pin, int pin2):stepper(stepsPerRev, pin, pin2){};  
};
int stepsToDo = 15000;

unsigned long previousMotor1Time = millis();
long Motor1Interval = 1;

unsigned long previousMotor2Time = millis();
long Motor2Interval = 10;

const float STEPS_PER_REV = 42;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
int StepsRequired;
int dir = 12;



ExtendedStepper motor(STEPS_PER_REV,3,4);
//motor.setStepper(steppermotor1);


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
  motor.stepper.setSpeed(4000);
  unsigned long currentMotor1Time = millis();
  
  if( (currentMotor1Time - previousMotor1Time > Motor1Interval) && stepsToDo > 0){
    motor.stepper.step(5);
    previousMotor1Time = currentMotor1Time;
    stepsToDo -= 5;
  }
}
