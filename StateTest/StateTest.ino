#include <LinkedList.h>
#include <StateMachine.h>
#include <String.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2);

#define DOWN_PIN  8
#define UP_PIN    9
#define OK_PIN    10
#define BACK_PIN  11

String selecteazaText(String info){
  return ">" + info;
}
void afisInfo(String txt1, bool sel1, String txt2, bool sel2, String Sep){
  Serial.println(Sep);
  if(sel1){
    String text = "->" + txt1;
    Serial.println(text);
    Serial.println(txt2);
  }else{
    String text = "->" + txt2;
    Serial.println(txt1);
    Serial.println(text);
  }
  Serial.println(Sep);
}


String Sep                   = "############";
String TxtPgHome              = " Pagina Acasa";
String TxtPgSetPozAcasa       = " Seteaza Pozitia de Home";
String TxtPgMiscaAxe          = " Misca una din axe";
String TxtPgSetVMin           = " Seteaza viteza minima";
String TxtPgSetVMax           = " Seteaza viteza maxima";
String TxtPgTrimiteAcasa      = " Trimite motoarele la pozitia acasa";
String TxtPgTrimiteMentenanta = " Trimite motoarele la pozitia mentenanta";
String TxtPgStartSudare       = " Start sudare";
String TxtPgInapoiMeniu       = " Inapoi";
String TxtPgMiscaAxa          = " Misca Axa ";
String TxtPg10Pasi            = " Misca 10 pasi axa ";
String TxtPg1Pasi             = " Misca 1 pas axa ";


const int STATE_DELAY = 1000;
int randomState = 0;

StateMachine machine = StateMachine();

State* S_PaginaHome              = machine.addState(&PaginaHome); 
State* S_PaginaSetPozAcasa       = machine.addState(&PaginaSetPozAcasa); 
State* S_PaginaMiscaAxe          = machine.addState(&PaginaMiscaAxe);
  State* S_PaginaInapoiMisca     = machine.addState(&PaginaInapoiMisca);
  State* S_PaginaMiscaAxa1       = machine.addState(&PaginaMiscaAxa1);
    State* S_PaginaInapoiAxa1    = machine.addState(&PaginaInapoiAxa1);
    State* S_Pagina10PasiAxa1    = machine.addState(&Pagina10PasiAxa1); 
    State* S_Pagina1PasiAxa1    = machine.addState(&Pagina1PasiAxa1); 
  State* S_PaginaMiscaAxa2       = machine.addState(&PaginaMiscaAxa2);
  State* S_PaginaMiscaAxa3       = machine.addState(&PaginaMiscaAxa3);
  State* S_PaginaMiscaAxa4       = machine.addState(&PaginaMiscaAxa4);
State* S_PaginaSetVMin           = machine.addState(&PaginaSetVMin);
State* S_PaginaSetVMax           = machine.addState(&PaginaSetVMax);
State* S_PaginaTrimiteAcasa      = machine.addState(&PaginaTrimiteAcasa); 
State* S_PaginaTrimiteMentenanta = machine.addState(&PaginaTrimiteMentenanta);
State* S_PaginaStartSudare       = machine.addState(&PaginaStartSudare);
/*

State* S_PaginaMiscaAxa1 = machine.addState(&PaginaMiscaAxa1); 
State* S_PaginaMiscaAxa1Pasi1 = machine.addState(&PaginaMiscaAxa1Pasi1); 
State* S_PaginaMiscaAxa1Pasi10 = machine.addState(&PaginaMiscaAxa1Pasi10); 
State* S_PaginaAfixPoxAxa1 = machine.addState(&PaginaAfixPoxAxa1); 


State* S_PaginaMiscaAxa2 = machine.addState(&PaginaMiscaAxa2);
State* S_PaginaMiscaAxa2Pasi1= machine.addState(&PaginaMiscaAxa2Pasi1);
State* S_PaginaMiscaAxa2Pasi10 = machine.addState(&PaginaMiscaAxa2Pasi10);
State* S_PaginaAfixPoxAxa2 = machine.addState(&PaginaAfixPoxAxa2); 

State* S_PaginaMiscaAxa3 = machine.addState(&PaginaMiscaAxa3);
State* S_PaginaMiscaAxa3Pasi1 = machine.addState(&PaginaMiscaAxa3Pasi1);
State* S_PaginaMiscaAxa3Pasi10 = machine.addState(&PaginaMiscaAxa3Pasi10);
State* S_PaginaAfixPoxAxa3 = machine.addState(&PaginaAfixPoxAxa3); 

State* S_PaginaMiscaAxa4 = machine.addState(&PaginaMiscaAxa4);
State* S_PaginaMiscaAxa4Pasi1 = machine.addState(&PaginaMiscaAxa4Pasi1);
State* S_PaginaMiscaAxa4Pasi10 = machine.addState(&PaginaMiscaAxa4Pasi10);
State* S_PaginaAfixPoxAxa4 = machine.addState(&PaginaAfixPoxAxa4); 



//
//State* S_PaginaTrimiteMentenanta = machine.addState(&PaginaTrimiteMentenanta); 
//
*/



void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  randomSeed(A0);
  lcd.init();
  
  
  pinMode(DOWN_PIN, INPUT_PULLUP);
  pinMode(UP_PIN, INPUT_PULLUP);
  pinMode(OK_PIN, INPUT_PULLUP);
  pinMode(BACK_PIN, INPUT_PULLUP);
  S_PaginaHome->addTransition(&T_BDown, S_PaginaSetPozAcasa);
  
  S_PaginaSetPozAcasa->addTransition(&T_BUp, S_PaginaHome);
  S_PaginaSetPozAcasa->addTransition(&T_BDown, S_PaginaMiscaAxe);
  
  S_PaginaMiscaAxe->addTransition(&T_BUp,S_PaginaSetPozAcasa);
  S_PaginaMiscaAxe->addTransition(&T_BDown, S_PaginaSetVMin);
  S_PaginaMiscaAxe->addTransition(&T_BOk, S_PaginaInapoiMisca);
    S_PaginaInapoiMisca->addTransition(&T_BOk, S_PaginaMiscaAxe);
    S_PaginaInapoiMisca->addTransition(&T_BDown, S_PaginaMiscaAxa1);

    S_PaginaMiscaAxa1->addTransition(&T_BUp, S_PaginaInapoiMisca);
    S_PaginaMiscaAxa1->addTransition(&T_BDown, S_PaginaMiscaAxa2);
    S_PaginaMiscaAxa1->addTransition(&T_BOk, S_PaginaInapoiAxa1);
      S_PaginaInapoiAxa1->addTransition(&T_BOk, S_PaginaMiscaAxa1);
      S_PaginaInapoiAxa1->addTransition(&T_BDown, S_Pagina10PasiAxa1); 
      
      S_Pagina10PasiAxa1->addTransition(&T_BUp, S_PaginaInapoiAxa1);
      S_Pagina10PasiAxa1->addTransition(&T_BDown, S_Pagina1PasiAxa1);
      
      S_Pagina1PasiAxa1->addTransition(&T_BUp, S_Pagina10PasiAxa1);
          
    S_PaginaMiscaAxa2->addTransition(&T_BUp, S_PaginaMiscaAxa1);
    S_PaginaMiscaAxa2->addTransition(&T_BDown, S_PaginaMiscaAxa3);

    S_PaginaMiscaAxa3->addTransition(&T_BUp, S_PaginaMiscaAxa2);
    S_PaginaMiscaAxa3->addTransition(&T_BDown, S_PaginaMiscaAxa4);

    S_PaginaMiscaAxa4->addTransition(&T_BUp, S_PaginaMiscaAxa3);
    
  S_PaginaSetVMin->addTransition(&T_BUp, S_PaginaMiscaAxe);
  S_PaginaSetVMin->addTransition(&T_BDown, S_PaginaSetVMax);

  S_PaginaSetVMax->addTransition(&T_BUp, S_PaginaSetVMin);
  S_PaginaSetVMax->addTransition(&T_BDown, S_PaginaTrimiteAcasa);

  S_PaginaTrimiteAcasa->addTransition(&T_BUp,S_PaginaSetVMax);
  S_PaginaTrimiteAcasa->addTransition(&T_BDown, S_PaginaTrimiteMentenanta);

  S_PaginaTrimiteMentenanta->addTransition(&T_BUp, S_PaginaTrimiteAcasa);
  S_PaginaTrimiteMentenanta->addTransition(&T_BDown, S_PaginaStartSudare);

  S_PaginaStartSudare->addTransition(&T_BUp, S_PaginaTrimiteMentenanta);
 
}
  
void loop() {
  // put your main code here, to run repeatedly:
  machine.run();
  delay(STATE_DELAY);
}


void PaginaHome(){
  if(machine.executeOnce){
    afisInfo(TxtPgHome ,true, TxtPgSetPozAcasa, false, Sep);
  }
}
void PaginaSetPozAcasa(){
  if(machine.executeOnce){
    afisInfo(TxtPgHome, false, TxtPgSetPozAcasa, true, Sep); 
  }
}

void PaginaMiscaAxe(){
  if(machine.executeOnce){
    afisInfo(TxtPgSetPozAcasa, false, TxtPgMiscaAxe, true, Sep);
  }
}
void PaginaSetVMin(){
  if(machine.executeOnce){
    afisInfo(TxtPgMiscaAxe,false, TxtPgSetVMin, true, Sep);
  }
}
void PaginaSetVMax(){
  if(machine.executeOnce){
    afisInfo(TxtPgSetVMin, false, TxtPgSetVMax, true, Sep);
  }
}
void PaginaTrimiteAcasa(){
  if(machine.executeOnce){
    afisInfo(TxtPgSetVMax, true, TxtPgTrimiteAcasa, true, Sep);
  }
}
void PaginaTrimiteMentenanta(){
  if(machine.executeOnce){
    afisInfo(TxtPgTrimiteAcasa, false, TxtPgTrimiteMentenanta, true, Sep);
  }
}
void PaginaStartSudare(){
  if(machine.executeOnce){
    afisInfo(TxtPgTrimiteMentenanta, false, TxtPgStartSudare, true, Sep);
  }
}
void PaginaInapoiMisca(){
  if(machine.executeOnce){
    afisInfo(TxtPgInapoiMeniu, true, TxtPgMiscaAxa + "1", false, Sep);
  }
}
void PaginaMiscaAxa1(){
   if(machine.executeOnce){
      afisInfo(TxtPgMiscaAxa + "1", true,  TxtPgMiscaAxa + "2", false, Sep);
   }
}
void PaginaMiscaAxa2(){
   if(machine.executeOnce){
      afisInfo(TxtPgMiscaAxa + "2", true,  TxtPgMiscaAxa + "3", false, Sep);
   }
}
void PaginaMiscaAxa3(){
   if(machine.executeOnce){
      afisInfo(TxtPgMiscaAxa + "3", true,  TxtPgMiscaAxa + "4", false, Sep);
   }
}
void PaginaMiscaAxa4(){
   if(machine.executeOnce){
      afisInfo(TxtPgMiscaAxa + "3", false,  TxtPgMiscaAxa + "4", true, Sep);
   }
}
void PaginaInapoiAxa1(){
  if(machine.executeOnce){
    afisInfo(TxtPgInapoiMeniu, true, TxtPg10Pasi + "1", false, Sep);
  }
  
}
void Pagina10PasiAxa1(){
  if(machine.executeOnce){
    afisInfo(TxtPg10Pasi + "1", true, TxtPg1Pasi, false, Sep);
  }
}
void Pagina1PasiAxa1(){
  if(machine.executeOnce){
    afisInfo(TxtPg10Pasi + "1", false, TxtPg1Pasi, true, Sep);
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
