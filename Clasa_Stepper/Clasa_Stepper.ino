

volatile int opresteTot = 1;
void ISR_opresteTot(){
  opresteTot  =0;
  Serial.println("STOPPED");
}
class StepperMotor{
private:
  int pinStep;
  int pinDir;
  int pinHome;
  int poz;
  int pozMentenanta;
  int vMin;
  int vMax;
public:
  StepperMotor(int pinDir, int pinStep, int pinHome, int vMin, int vMax){
    this->pinDir = pinDir;
    this->pinStep = pinStep;
    this->pinHome = pinHome;
    this->vMin = vMin;
    this->vMax = vMax;
    digitalWrite(this-> pinDir, HIGH);
  }
  void setVMin(int v){
    this->vMin = v;
  }
  void setVMax(int v){
    this->vMax = v;
  }
  void setPozMentenanta(int p){
    this->pozMentenanta = p;
  }
  void step(int steps){
    if(steps > 0){
      digitalWrite(pinDir, HIGH);
      poz += steps;
    }else{
      Serial.println(poz, steps);
      digitalWrite(pinDir, LOW);
      if(steps * (-1) > poz){ // Cazul in care il pun sa mearga inpoi mai mult decat poz home
        steps = poz * (-1);
      }
      steps = (-1) * steps;
      poz -= steps;
    }

    int change = 2;
    int rampUpStop = (vMin-vMax) / change;
    if (rampUpStop > steps / 2){
       rampUpStop = steps / 2;
    }
    int rampDownStart = steps - rampUpStop;
    int d = vMin;
    for (int i=0;i<steps;i++){ 
        digitalWrite(pinStep * opresteTot , HIGH);
        digitalWrite(pinStep * opresteTot , LOW);  
        delayMicroseconds(d);
        if (i < rampUpStop)
            d -= change;
         else if (i > rampDownStart )
            d += change;
      }
   }
  
  void seteazaHome(bool sens, int nrPasi){
    if (sens == false){
      digitalWrite(pinDir, LOW);
    } else{
      digitalWrite(pinDir, HIGH);
    }
    while(digitalRead(pinHome)){
      step(nrPasi);
      delay(2);
    }
    poz = 0;
  }
  void trimiteLaMentenanta(){
    step(pozMentenanta-poz);
  }
  void trimiteLaAcasa(){
    step(-1*poz);
  }
};

// Definim pinul pentru a opri tot (pentru Arduino UNO putem folosii  numai pinii 2 sau 3)
#define DIR_PIN        5
#define STEP_PIN       4
#define HOME_PIN       3
#define KILL_PIN       2


// Declaram cele 4 motare
StepperMotor motor(DIR_PIN, STEP_PIN, HOME_PIN, 1400, 300);


void setup(){
  Serial.begin(9600);
  
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(HOME_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(KILL_PIN), ISR_opresteTot, RISING);
  
  motor.seteazaHome(false, 10); // cu false merge in o directie si true in directia opusa, 10 reprezinta numarul de pasi in care merge
  delay(1000);
  motor.step(2000);
  delay(1000);
  motor.step(1000);
  delay(1000);
  motor.step(-5000);
  delay(1000);
  motor.setPozMentenanta(6000);
  motor.trimiteLaMentenanta();
  delay(1000);
  motor.trimiteLaAcasa();
  delay(1000);
  motor.step(11000);
  delay(1000);
  motor.setVMax(150);
  motor.step(11000);
  }

void loop()
{
 /*  motor.step(1000);
   delay(1000);
   motor.step(2000);
   delay(1000);
   motor.step(-8500);
   delay(3000); */
}
