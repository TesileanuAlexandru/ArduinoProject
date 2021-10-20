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

void loop() {

  if (digitalRead(2) == HIGH) {
  digitalWrite(12,LOW);
  }
  
  
else {
  digitalWrite(12,LOW);
}

  
 steppermotor1.setSpeed(3000);
 StepsRequired = 1900;
 steppermotor1.step(StepsRequired); 
 delay(500) ;

 

 steppermotor2.setSpeed(2600);
 StepsRequired = 2000;
 steppermotor2.step(StepsRequired); 
 delay(500) ;

   
 

 steppermotor3.setSpeed(2600);
 StepsRequired = 5000;
 steppermotor3.step(StepsRequired); 
 delay(50) ;
 
 steppermotor4.setSpeed(4000);
 StepsRequired = 2400;
 steppermotor4.step(StepsRequired); 
 delay(20) ;

 steppermotor5.setSpeed(5600);
 StepsRequired = 2000;
 steppermotor5.step(StepsRequired); 
 delay(10) ;

   
 

 steppermotor6.setSpeed(8600);
 StepsRequired = 1000;
 steppermotor6.step(StepsRequired); 
 delay(50) ;
 
 steppermotor7.setSpeed(4000);
 StepsRequired = 2400;
 steppermotor7.step(StepsRequired); 
 delay(20) ;

digitalWrite(12,HIGH);
 delay (100);
digitalWrite(12,LOW);

 

}
