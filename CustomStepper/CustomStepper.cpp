#include "CustomStepper.h"

/*
void ExtendedStepper::setStepper(Stepper *stepper){
    &this->stepper = stepper;
}
*/
void ExtendedStepper::step(int steps){
    this->stepper.step(steps);
}



ExtendedStepper::ExtendedStepper(){
    this->position = 0;
}

ExtendedStepper::ExtendedStepper(float stepsPerRev, int pin, int pin2):stepper(stepsPerRev, pin, pin2){
    position = 0;
}
