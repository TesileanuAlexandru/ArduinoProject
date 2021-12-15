
#include <Stepper.h>
#include <Keyboard.h>

class ExtendedStepper{
  private:
    int position;
    Stepper stepper;
    int dirPin;
  public:
    void setSpeed(int speed){
      stepper.setSpeed(speed);
    }

    void setPosition(int pos){
      position = pos;
    }
    
    ExtendedStepper(int speed, float stepsPerRev, int pin, int pin2, int dirPin):stepper(stepsPerRev, pin, pin2){
      stepper.setSpeed(speed);
      dirPin = dirPin;
      digitalWrite(dirPin, HIGH);
    };  
    
    void setHome(int increments){
      bool sensor = false;
      int x = 100; // 
      while(sensor == false){
        stepper.step(increments);
        //Citeste din nou valoarea senzorului (Urmatoarele linii se vor sterge)
        x--;
        if(x == 0){
          sensor = true;
        }
      }
      position = 0;
    }
    
   void step(int steps){
    /*
      if (position + steps < 0){
          steps = position;
          position = 0;
      }
      */
      stepper.step(steps);
   }
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



ExtendedStepper motor(4000,STEPS_PER_REV,3,4, 12);
//motor.setStepper(steppermotor1);


void setup() {
  // put your setup code here, to run once:
  pinMode(2,INPUT);
  pinMode(12,OUTPUT);

  
  motor.step(4000);
  delay(500);

  digitalWrite(12,LOW);
  motor.step(5000);
 delay(500);
}

void loop() {
  
    // put your main code here, to run repeatedly:

  /*
  unsigned long currentMotor1Time = millis();

  digitalWrite(12,HIGH);
  digitalWrite(2, HIGH);
  if( (currentMotor1Time - previousMotor1Time > Motor1Interval) && stepsToDo > 0){
    motor.setSpeed(4000);
    motor.step(-50);
    previousMotor1Time = currentMotor1Time;
    stepsToDo -= 5;
  }
  */
}
