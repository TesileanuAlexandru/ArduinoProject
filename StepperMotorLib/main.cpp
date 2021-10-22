#include <iostream>
#include "ParallelStepperMotor.h"
#include <list>


using namespace std;

int main()
{
    Gear g1(5);
    //Gear g2(10);
    StepperMotorAssambley motor;
    motor.setMainGear(g1);
   // motor.addGear(g2);
    cout << motor.computeFinalRatio() <<"Is the final ratio";
    return 0;
}
