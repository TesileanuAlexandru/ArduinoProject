#include "ParallelStepperMotor.h"
Gear::Gear(){
    this->teethNo = 1;
}
Gear::Gear(int teethNo){
    this->teethNo = teethNo;
}
void Gear::setTeethNo(int x){
    this->teethNo = x;
}
int Gear::getTeethNo(){
    return this->teethNo;
}

void StepperMotorAssambley::setMainGear(Gear g){
    this->mainGear = g;
}

void StepperMotorAssambley::addGear(Gear g){
    gears.push_back(g);
}

float StepperMotorAssambley::computeFinalRatio(){
    finalRatio = mainGear.getTeethNo();
    bool hasGears = false;
    list<Gear>::iterator it;
    for(it = gears.begin(); it!= gears.end(); ++it){
        finalRatio = finalRatio / it->getTeethNo();
        hasGears = true;
    }
    if (hasGears == false){
        finalRatio = 1;
    }
    return finalRatio;
}

