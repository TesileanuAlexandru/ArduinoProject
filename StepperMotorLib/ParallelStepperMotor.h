#ifndef __ParallelStepperMotor_h
#define __ParallelStepperMotor_h
#include <list>
#include <iterator>
#include <Stepper.h>

using namespace std;


class Gear{
private:
    int teethNo;
public:
    Gear();
    Gear(int teethNo);
    void setTeethNo(int x);
    int getTeethNo();
};



class StepperMotorAssambley{
private:
    list <Gear> gears;
    Gear mainGear;
    float finalRatio;
public:
    void setMainGear(Gear g);
    void addGear(Gear g);
    float computeFinalRatio();
};

#endif // __ParallelStepperMotor
