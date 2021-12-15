#include <Stepper.h>

// Prin coventie, pin12 & High = inainte

class ExtendedStepper{
  
  private:
    Stepper stepper;
    int position;
    int dirPin;
    bool sens; // True inainte, False inapoi
    int mentenancePoint;
    
  public:
    ExtendedStepper(float stepsPerRev, int pin1, int pin2, int dirPin, int speed):stepper(stepsPerRev, pin1, pin2){
      stepper.setSpeed(speed);
      this->dirPin = dirPin;
      digitalWrite(dirPin,HIGH); 
      this->sens = true;
    }

    void step(int steps){
      if(steps > 0){
        if(sens == false){
          sens = true;
          digitalWrite(dirPin,HIGH);
        }
      }else{
        if(sens == true){
          sens = false;
          digitalWrite(dirPin,LOW);
        }
      }
      if(position + steps < 0){
          steps = -1 * position;
          position = 0;
      }
      stepper.step(steps);
      position += steps;
    }
    

    void setSpeed(int speed){
      stepper.setSpeed(speed);
    }
    
    void setHome(int steps){
      bool sensor = false;
      int x = 100; // 
      while(sensor == false){
        step(steps);
        //Citeste din nou valoarea senzorului (Urmatoarele linii se vor sterge)
        x--;
        if(x == 0){
          sensor = true;
        }
      }
      position = 0;
    }

    void goHome(){
      step(-1 * position);
    }

    void setMentenancePoint(int mentenancePoint){
      this->mentenancePoint = mentenancePoint;
    }

    void goToMentenancePoint(){
      step(mentenancePoint-position);
    }

    void setPosition(int pos){
      this->position = pos;
    }

    
    
   
  
};



// ----------------------  SETUP  ------------------------------

const float STEPS_PER_REV = 42;
const float GEAR_RED = 64;
const float STEPS_PER_OUT_REV = STEPS_PER_REV * GEAR_RED;

ExtendedStepper motor(STEPS_PER_REV, 3, 4, 12, 4000);


void setup() {
  pinMode(2,INPUT);
  pinMode(12,OUTPUT);
/*
  motor.step(2000);
  delay(500);
  motor.step(-2000);
  // Verificam sa mearga directiile bine
  delay(1000);
*/
  motor.setHome(100);
  delay(1000);
  motor.setMentenancePoint(18000);
  motor.setPosition(9000);
  motor.goToMentenancePoint();

  delay(1000);
  motor.step(-9000);
  // A ajuns la Home

  
}



// ----------------- LOOP ------------------------
void loop() {
  // put your main code here, to run repeatedly:

}
