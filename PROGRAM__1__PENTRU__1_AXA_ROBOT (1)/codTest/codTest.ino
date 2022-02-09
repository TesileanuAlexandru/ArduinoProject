#include <AccelStepper.h>



AccelStepper stepperX(1, 4, 5);

#define home_switch 9 

long TravelX;
int move_finished=1;
long initial_homing=-1;


void setup() {

Serial.begin(9600);
pinMode (home_switch, INPUT_PULLUP);
delay(5);

stepperX.setMaxSpeed(100.0);
stepperX.setAcceleration(100.0);

Serial.print("Stepper is Homing...........");
while(digitalRead(home_switch))  {

  stepperX.moveTo(initial_homing);
  initial_homing--;
  stepperX.run ();
  delay(5);
  
}



stepperX.setCurrentPosition(0);
stepperX.setMaxSpeed (100.0);
stepperX.setAcceleration (100.0);
initial_homing=1;

while (!digitalRead(home_switch))  {
    stepperX.moveTo(initial_homing);
    stepperX.run();
    initial_homing++;
    delay(5);

}


stepperX.setCurrentPosition(0);
Serial.println ("Homing Completed");
Serial.println ("");
stepperX.setMaxSpeed(1000.0);
stepperX.setAcceleration(1000.0);



Serial.println ("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home): ");

}




void loop() {


while (Serial.available ()>0) {
 move_finished=0;

TravelX=Serial.parseInt();
if (TravelX <0 || TravelX > 1350)  {
Serial.println ("");
Serial.println ("Please enter a value greater than zero and smaller or equal to 1350.....");
Serial.println("");

}

else  {

Serial.println ("Moving stepper into position: ");
Serial.println (TravelX);

stepperX.moveTo(TravelX);
delay(5);

}

     }

if (TravelX > 0  && TravelX <=1350) {


if ((stepperX.distanceToGo () !=0))  {
  stepperX.run ();

}

  if ((move_finished ==0) && (stepperX.distanceToGo() ==0))  {

    Serial.println ("COMPLETED");
    Serial.println ("");
    Serial.println ("Enter Travel distance (Positive for CW / Negative for CCW and Zero for back to Home) : ");

move_finished=1;

}
   }
     }







  





























 
