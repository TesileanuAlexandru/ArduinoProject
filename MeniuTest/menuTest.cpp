#include <CMBMenu.hpp>



// define function IDs
enum MenuFID {
  MeniuDefault,
  MeniuAxe,
  MeniuAxa1,
  MeniuMiscaAxa1_5Pasi,
  MeniuMiscaAxa1_10Pasi,
  MeniuMiscaAxa2_5Pasi,
  MeniuMiscaAxa2_10Pasi,
  MeniuPozAxa1,
  MeniuAxa2,
  MeniuPozAxa2,
  MeniuPozAcasa,
  MeniuPozMentenanta,
};

// define key types
enum KeyType {
  KeyNone, // no key is pressed
  KeyLeft,
  KeyRight,
  KeyEnter,
  KeyExit
};


CMBMenu<100> g_Menu;

const char meniuStareDefault[] PROGMEM = {"Afisare detalii aparat"};
const char meniuMiscareAxe[] PROGMEM = {"Mutare axe"};
const char meniuMiscaAxa1[] PROGMEM = {"Muta axa 1"};
const char meniuMiscaAxa1_5pasi[] PROGMEM = {"Muta axa1 5 pasi"};
const char meniuMiscaAxa1_10pasi[] PROGMEM = {"Muta axa1 10 pasi"};
const char meniuPozitieAxa1[] PROGMEM = {"Poxitia axei 1:"};
const char meniuMiscaAxa2[] PROGMEM = {"-Muta axa 2"};
const char meniuMiscaAxa2_5pasi[] PROGMEM = {"Muta axa2 5 pasi"};
const char meniuMiscaAxa2_10pasi[] PROGMEM = {"Muta axa2 10 pasi"};
const char meniuPozitieAxa2[] PROGMEM = {"Poxitia axei 2:"};
const char meniuPozitieAcasa[] PROGMEM = {"Seteaza/Trimite la pozitia acasa"};
const char meniuPozitieMentenanta[] PROGMEM = {"Trimite la pozitia mentenanta"};
const char meniuStartProcedeuSudare[] PROGMEM = {"Pornire procedeu sudare"};

void setup() {
  Serial.begin(9600);
  Serial.println("===========================");
  Serial.println("mblib - example for CMBMenu");
  Serial.println("===========================");
  Serial.println("");
  Serial.println("l: left, r: right, e: enter, x: exit, m: print menu");
  Serial.println("");
  // add nodes to menu (layer, string, function ID)
  g_Menu.addNode(0, meniuStareDefault, MeniuDefault);
  g_Menu.addNode(1, meniuMiscareAxe, MeniuAxe);
  g_Menu.addNode(2, meniuMiscaAxa1, MeniuAxa1);
  g_Menu.addNode(3, meniuMiscaAxa1_5pasi, MeniuMiscaAxa1_5Pasi);
  g_Menu.addNode(4, meniuPozitieAxa1, MeniuPozAxa1);
  g_Menu.addNode(3, meniuMiscaAxa1_10pasi, MeniuMiscaAxa1_10Pasi);
  g_Menu.addNode(4, meniuPozitieAxa1, MeniuPozAxa1);

  g_Menu.addNode(2, meniuMiscaAxa2, MeniuAxa2);
  g_Menu.addNode(3, meniuMiscaAxa2_5pasi, MeniuMiscaAxa2_5Pasi);
  g_Menu.addNode(4, meniuPozitieAxa2, MeniuPozAxa2);
  g_Menu.addNode(3, meniuMiscaAxa1_10pasi, MeniuMiscaAxa2_10Pasi);
  g_Menu.addNode(4, meniuPozitieAxa1, MeniuPozAxa2);

  g_Menu.addNode(1, meniuPozitieAcasa, MeniuPozAcasa);
  g_Menu.addNode(1, meniuPozitieMentenanta, MeniuPozMentenanta);

  const char* info;
  g_Menu.buildMenu(info);
  g_Menu.printMenu();

  // ** menu **
  // print current menu entry
   printMenuEntry(info);

  
}
KeyType getKey()
{
  KeyType key = KeyNone;

  // here for demonstration: get "pressed" key from terminal
  // replace code when using push buttons
  while(Serial.available() > 0) {
    String Key_s = Serial.readString();
    Key_s.trim();
    Serial.println("");
    if(Key_s.equals("l")) { // left
      key = KeyLeft;
      Serial.println("<left>");
    } else if (Key_s.equals("r")) { // right
      key = KeyRight;
      Serial.println("<right>");
    } else if (Key_s.equals("e")) { // enter
      key = KeyEnter;
      Serial.println("<enter>");
    } else if (Key_s.equals("x")) { // exit
      key = KeyExit;
      Serial.println("<exit>");
    } else if (Key_s.equals("m")) { // print menu
      g_Menu.printMenu();
    }
  }

 return key;
}

void printMenuEntry(const char* f_Info)
{
  String info_s;
  MBHelper::stringFromPgm(f_Info, info_s);

  // when using LCD: add/replace here code to
  // display info on LCD
  Serial.println("----------------");
  Serial.println(info_s);
  Serial.println("----------------");
}

void loop() {
  // put your main code here, to run repeatedly:

  // function ID
  int fid = 0;

  // info text from menu
  const char* info;

  // go to deeper or upper layer?
  bool layerChanged=false;

  // determine pressed key
  KeyType key = getKey();

  // ** menu **
  // call menu methods regarding pressed key
  switch(key) {
    case KeyExit:
      g_Menu.exit();
      break;
    case KeyEnter:
      g_Menu.enter(layerChanged);
      break;
    case KeyRight:
      g_Menu.right();
      break;
    case KeyLeft:
      g_Menu.left();
      break;
    default:
      break;
  }

  if (KeyNone != key) {
    fid = g_Menu.getInfo(info);
    printMenuEntry(info);
  }
  if ((0 != fid) && (KeyEnter == key) && (!layerChanged)) {
    switch (fid) {
      case MeniuMiscaAxa1_5Pasi:
        MutaAxa1_5Pasi();
        break;
      default:
        break;
    }
  }
}


void MutaAxa1_5Pasi(){

}