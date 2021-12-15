#include <Stepper.h>
const float STEPS_PER_REV = 42;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;
int StepsRequired;
int dir = 12;
Stepper steppermotor1(STEPS_PER_REV,3,4);
Stepper steppermotor2(STEPS_PER_REV,5,4);
Stepper steppermotor3(STEPS_PER_REV,7,4);
Stepper steppermotor4(STEPS_PER_REV,9,4);
Stepper steppermotor5(STEPS_PER_REV,6,4);
Stepper steppermotor6(STEPS_PER_REV,8,4);
Stepper steppermotor7(STEPS_PER_REV,10,4);












void setup() {
  // put your setup code here, to run once:

pinMode(2,INPUT);
pinMode(12,OUTPUT);

}
int x=0;
void loop() {

  if (digitalRead(2) == HIGH) {
  digitalWrite(12,LOW);
  }
  
  
else {
  digitalWrite(12,LOW);
}

  
 
 StepsRequired = 1900;
 steppermotor1.setSpeed(3000);
  steppermotor1.step(-1900); 

 x = x + 1;
 delay(500) ;
 digitalWrite(12,HIGH);
 steppermotor1.step(1900); 

 

digitalWrite(12,HIGH);
 delay (100);
digitalWrite(12,LOW);

 

}
