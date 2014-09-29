#include <Wire.h>

#include "Adafruit_LEDBackpack.h"
#include "Adafruit_GFX.h"

Adafruit_7segment disp1 = Adafruit_7segment();
Adafruit_7segment disp2 = Adafruit_7segment();
Adafruit_7segment disp3 = Adafruit_7segment();
Adafruit_7segment disp4 = Adafruit_7segment();

const String PING = String('p'); //implemented
const String RSET = String('r');
const String INIT = String('i'); //implemented
const String DSBL = String('d'); //implemented
const String BRT = String('b'); //implemented
const String WRTE_SEQ = String("ws"); //implemented
const String WRTE_ALL = String("wa"); //implemented
const String WRTE_ONE = String("wo"); //implemented
const String COLN_SEQ = String("cs"); //implemented
const String COLN_ALL = String("ca"); //implemented
const String COLN_ONE = String("co"); //implemented

const String DBG = String("e"); //implemnted

const String ACK = String("r");

String disp[4];

boolean colon[4] = {false, false, false, false};

int brightness;

String currCmd = String("");

void setup() {
  // initialize serial:
  Serial.begin(9600);
  
  
  disp1.begin(0x70);
  disp2.begin(0x71);
  disp3.begin(0x72);
  disp4.begin(0x73);

}

void loop() {
  // if there's any serial available, read it:
  while (Serial.available() > 0) {

    // look for the next valid integer in the incoming serial stream:
    char cmd = Serial.read();
    if(cmd == ';'){
      currCmd += cmd;
      currCmd.trim();
      if(currCmd.startsWith(PING)){
        Serial.println("ardFCSv1");
      }
      else if(currCmd.startsWith(BRT)){
        brightness = currCmd.substring(BRT.length()).toInt();
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(COLN_ALL)){
        colon[0] = currCmd.substring(COLN_ALL.length()).toInt();
        colon[1] = currCmd.substring(COLN_ALL.length()).toInt();
        colon[2] = currCmd.substring(COLN_ALL.length()).toInt();
        colon[3] = currCmd.substring(COLN_ALL.length()).toInt();
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(COLN_ONE)){
        int id = currCmd.substring(WRTE_ALL.length()).toInt();
        colon[id-1] = currCmd.substring(currCmd.lastIndexOf(',')+1).toInt();    
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(COLN_SEQ)){
        int pos1 = COLN_SEQ.length();
        int pos2 = currCmd.indexOf(',');
        for(int i = 0; i < 4; i++){
          colon[i] = currCmd.substring(pos1,pos2).toInt(); 
          pos1 = pos2+1;
            pos2 = currCmd.substring(pos1).indexOf(',')+pos1;
            if(pos2<pos1){
              pos2 = currCmd.lastIndexOf(';');
            }
        }
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(WRTE_ALL)){
        disp[0] = currCmd.substring(WRTE_ALL.length(),currCmd.lastIndexOf(';'));
        disp[1] = currCmd.substring(WRTE_ALL.length(),currCmd.lastIndexOf(';'));
        disp[2] = currCmd.substring(WRTE_ALL.length(),currCmd.lastIndexOf(';'));
        disp[3] = currCmd.substring(WRTE_ALL.length(),currCmd.lastIndexOf(';'));        
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(WRTE_ONE)){
        int id = currCmd.substring(WRTE_ALL.length()).toInt();
        disp[id-1] = currCmd.substring(currCmd.lastIndexOf(',')+1,currCmd.lastIndexOf(';'));    
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(WRTE_SEQ)){
        int pos1 = WRTE_SEQ.length();
        int pos2 = currCmd.indexOf(',');
        for(int i = 0; i < 4; i++){
          disp[i] = currCmd.substring(pos1,pos2); 
          pos1 = pos2+1;
            pos2 = currCmd.substring(pos1).indexOf(',')+pos1;
            if(pos2<pos1){
              pos2 = currCmd.lastIndexOf(';');
            }
        }
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(DSBL)){
        disp[0] = "    ";
        disp[1] = "    ";
        disp[2] = "    ";
        disp[3] = "    ";
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(INIT)){
        disp[0] = " d1 ";
        disp[1] = " d2 ";
        disp[2] = " d3 ";
        disp[3] = " d4 ";
        Serial.println(ACK);
      }
      else if(currCmd.startsWith(DBG)){
        Serial.print(disp[0]);
        Serial.print('|');
        Serial.print(disp[1]);
        Serial.print('|');
        Serial.print(disp[2]);
        Serial.print('|');
        Serial.println(disp[3]);
        Serial.print(colon[0]?"t":"f");
        Serial.print('|');
        Serial.print(colon[1]?"t":"f");
        Serial.print('|');
        Serial.print(colon[2]?"t":"f");
        Serial.print('|');
        Serial.println(colon[3]?"t":"f");
        Serial.println(brightness);
      }
      currCmd = String();
    } 
    else {

      currCmd += cmd;
    }


  }
}
