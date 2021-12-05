#ifndef __CustomStepper_h
#define __CustomStepper_h

#include <Stepper.h>

using namespace std;


class ExtendedStepper{
private:
    Stepper stepper;
    int position;

public:
    void voidSetHome();
    void step(int steps);
    void setStepper(Stepper stepper);
    ExtendedStepper();
    ExtendedStepper(float stepsPerRev, int pin, int pin2);
};

#endif // __ParallelStepperMotor
