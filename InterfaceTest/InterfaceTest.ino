volatile int opresteTot = 1;
void ISR_opresteTot(){
  opresteTot  =0;
 // Serial.println("STOPPED");
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
  bool areMentenanta;
public:
  StepperMotor(int pinDir, int pinStep, int pinHome, int vMin, int vMax){
    this->pinDir = pinDir;
    this->pinStep = pinStep;
    this->pinHome = pinHome;
    this->vMin = vMin;
    this->vMax = vMax;
    digitalWrite(this-> pinDir, HIGH);
    areMentenanta = false;
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
    areMentenanta = true;
  }
  void trimiteLaAcasa(){
      step(-1*poz);
  }
  bool getAreMentenanta(){
    return areMentenanta;
  }
  
};

// #########################################################################################

#include <LinkedList.h>
#include <StateMachine.h>
#include <String.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define DOWN_PIN  8
#define UP_PIN    9
#define OK_PIN    10

#define DIR_PIN        5
#define STEP_PIN       4
#define HOME_PIN       3
#define KILL_PIN       2

StepperMotor motor1(DIR_PIN, STEP_PIN, HOME_PIN, 1400, 300);

const int STATE_DELAY = 300;
int randomState = 0;
StateMachine machine = StateMachine();
State* S_SetPozAcasa       = machine.addState(&D_SetPozAcasa);
State* S_TrimitAcasa       = machine.addState(&D_TrimitAcasa);
State* S_MiscaAxe          = machine.addState(&D_MiscaAxe);
State* S_TrimiteMentenanta = machine.addState(&D_TrimiteMentenanta);
State* S_StartSudare       = machine.addState(&D_StartSudare);
State* S_ProcedeuSudare    = machine.addState(&D_ProcedeuSudare);
State* S_Resetare          = machine.addState(&D_Resetare);
State* S_ResetKill         = machine.addState(&D_ResetKill);

String selecteazaText(String txt){
  return ">" + txt;
};
void afisInfo(String txt1, bool sel, String txt2){
  lcd.clear();
  if(sel){
    lcd.setCursor(0,0);
    lcd.print(selecteazaText(txt1));
    lcd.setCursor(0,1);
    lcd.print(txt2);
  } else {
    lcd.setCursor(0,0);
    lcd.print(txt1);
    lcd.setCursor(0,1);
    lcd.print(selecteazaText(txt2));
  } 
}

String I_SetPozAcasa = "Set poz acasa";
String I_MiscaAxe    = "Misca axe";
String I_TrimiteMentenanta = "Trim mentenanta";
String I_StartSudare = "Start sudare";
String I_Resetare    = "Resetare oprire";




//#####################################################################################################################################
void setup() {
  Serial.begin(9600);
  randomSeed(A0);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(OK_PIN, INPUT_PULLUP);

  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(HOME_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(KILL_PIN), ISR_opresteTot, CHANGE);

  lcd.init();
  lcd.backlight();

  S_SetPozAcasa->addTransition(&T_BDown, S_MiscaAxe);
  S_SetPozAcasa->addTransition(&T_BOk, S_TrimitAcasa);

  S_TrimitAcasa->addTransition(&T_BOk, S_SetPozAcasa);

  S_MiscaAxe->addTransition(&T_BUp, S_SetPozAcasa);
  S_MiscaAxe->addTransition(&T_BDown, S_TrimiteMentenanta);

  S_TrimiteMentenanta->addTransition(&T_BUp, S_MiscaAxe);
  S_TrimiteMentenanta->addTransition(&T_BDown, S_StartSudare);

  S_StartSudare->addTransition(&T_BUp, S_TrimiteMentenanta);
  S_StartSudare->addTransition(&T_BOk, S_ProcedeuSudare);
   S_ProcedeuSudare->addTransition(&T_BOk, S_StartSudare);
  S_StartSudare->addTransition(&T_BDown, S_Resetare);

  S_Resetare->addTransition(&T_BUp, S_StartSudare);
  S_Resetare->addTransition(&T_BOk, S_ResetKill);

  S_ResetKill->addTransition(&T_BOk, S_Resetare);

  
}

void loop() {
  // put your main code here, to run repeatedly:
  machine.run();
  delay(STATE_DELAY);
}

void D_SetPozAcasa(){
  if(machine.executeOnce){
    afisInfo(I_SetPozAcasa, true, I_MiscaAxe);
    Serial.println("Setpozacasa");
  }
}
void D_MiscaAxe(){
  if(machine.executeOnce){
    afisInfo(I_SetPozAcasa, false, I_MiscaAxe);
    Serial.println("Miscaaxe");
  }
}
void D_TrimiteMentenanta(){
  if(machine.executeOnce){
    afisInfo(I_MiscaAxe, false, I_TrimiteMentenanta);
  }
}
void D_TrimitAcasa(){
  if(machine.executeOnce){
    afisInfo("Se trimit acasa", false, "Inapoi");
    motor1.seteazaHome(false,20);
  }
}
void D_StartSudare(){
  if(machine.executeOnce){
    afisInfo(I_TrimiteMentenanta, false, I_StartSudare);
  }
}
void D_Resetare(){
  if(machine.executeOnce){
    afisInfo(I_StartSudare, false, I_Resetare);
  }
}
void D_ResetKill(){
  if(machine.executeOnce){
    afisInfo("Rest oprire", false, "Inapoi");
    opresteTot = 1;
  }
}

//#########################################################################################

void D_ProcedeuSudare(){
  if(machine.executeOnce){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Trimite motoare ");
    lcd.setCursor(0,1);
    lcd.print("acasa");
    motor1.seteazaHome(false,20);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Start sudare");
    while(opresteTot == 1){
      motor1.step(10000);
      delay(100);
      //Serial.println(opresteTot);
      motor1.step(-3000);
      delay(1000);
    }
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Oprire urgenta");
    lcd.setCursor(0,1);
    lcd.print(">Inapoi");
    //opresteTot = 1;
  }
}

bool T_BDown(){
  if(digitalRead(DOWN_PIN) == LOW){
    return true;
  }
  return false;
}
bool T_BUp(){
  if(digitalRead(UP_PIN) == LOW){
    return true;
  }
  return false;
}
bool T_BOk(){
  if(digitalRead(OK_PIN) == LOW){
    return true;
  }
  return false;
}
