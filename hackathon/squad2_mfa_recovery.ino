// ============================================================
// SQUAD 2: ZTA MFA RECOVERY + POKA-YOKE HUMAN ERROR PREVENTION
// Based on actual UR10e Manual fault recovery procedure
// Hardware: RC522 RFID + 4x4 Keypad + LCD1602 I2C
// ============================================================
// WIRING:
//   LCD I2C SDA → Pin 20  SCL → Pin 21
//   RFID SDA    → Pin 53  RST → Pin 9
//   RFID MOSI   → Pin 51  MISO→ Pin 50  SCK → Pin 52
//   RFID VCC    → 3.3V  ⚠️  NOT 5V
//   Keypad Rows → Pins 30,31,32,33
//   Keypad Cols → Pins 34,35,36,37
// ============================================================

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
MFRC522 rfid(53, 9);

const byte ROWS=4, COLS=4;
char keys[ROWS][COLS]={{'1','2','3','A'},{'4','5','6','B'},{'7','8','9','C'},{'*','0','#','D'}};
byte rowPins[ROWS]={30,31,32,33};
byte colPins[COLS]={34,35,36,37};
Keypad keypad=Keypad(makeKeymap(keys),rowPins,colPins,ROWS,COLS);

// ── USERS ────────────────────────────────────────────────────
struct RFIDUser { byte uid[4]; byte uidLen; String role; String name; String pin; };
RFIDUser users[]={
  {{0xAA,0xBB,0xCC,0xDD},4,"WORKER",  "Floor Op.", ""},
  {{0x11,0x22,0x33,0x44},4,"TECH",    "Maint.Tech","1234"},
  {{0x55,0x66,0x77,0x88},4,"ENGINEER","Eng. Singh","9999"}
};
const int NUM_USERS=3;

// ── POKA-YOKE: Recovery Steps from UR10e Manual ──────────────
// Technician must confirm EACH step before system allows reset
// Prevents "acknowledge and ignore" — #1 cause of repeat faults
struct RecoveryStep {
  String instruction; // shown on LCD line 1
  String detail;      // shown on LCD line 2
  char   confirmKey;  // key tech must press to confirm
};

RecoveryStep steps[]={
  {"1.CHECK WORKSPACE", "Clear? Press 1",    '1'},
  {"2.INSPECT JOINT",   "No damage? Prss 2", '2'},
  {"3.CHECK PAYLOAD",   "TCP correct? Prss3","3"},
  {"4.REVIEW LOG",      "Cause found? Prss4","4"},
  {"5.CLEAR HAZARD",    "Hazard gone? Prss5","5"},
};
const int NUM_STEPS=5;
int currentStep=0;

// ── STATE ─────────────────────────────────────────────────────
enum AuthState { IDLE, AWAIT_RFID, AWAIT_PIN, POKA_YOKE, COMPLETE, DENIED };
AuthState authState=IDLE;
RFIDUser* currentUser=nullptr;
String pinBuffer="";
int failedPins=0;
unsigned long lockoutUntil=0;
String faultReason="";
int humanErrors=0;  // Track skipped/wrong steps

// ── HELPERS ──────────────────────────────────────────────────
void lcdPrint(String l1, String l2=""){
  lcd.clear();
  lcd.setCursor(0,0); lcd.print(l1.substring(0,16));
  if(l2.length()>0){lcd.setCursor(0,1); lcd.print(l2.substring(0,16));}
}

void logSerial(String event){
  Serial.println("EVENT|"+event+"|"+String(millis()));
}

RFIDUser* identifyCard(){
  if(!rfid.PICC_IsNewCardPresent()) return nullptr;
  if(!rfid.PICC_ReadCardSerial()) return nullptr;
  Serial.print("RFID_SCAN:");
  for(byte i=0;i<rfid.uid.size;i++){Serial.print(" ");Serial.print(rfid.uid.uidByte[i],HEX);}
  Serial.println();
  for(int i=0;i<NUM_USERS;i++){
    if(rfid.uid.size!=users[i].uidLen) continue;
    bool m=true;
    for(byte j=0;j<users[i].uidLen;j++){if(rfid.uid.uidByte[j]!=users[i].uid[j]){m=false;break;}}
    if(m){rfid.PICC_HaltA();rfid.PCD_StopCrypto1();return &users[i];}
  }
  rfid.PICC_HaltA();rfid.PCD_StopCrypto1();
  return nullptr;
}

// ── SETUP ────────────────────────────────────────────────────
void setup(){
  Serial.begin(9600);
  lcd.init(); lcd.backlight();
  SPI.begin(); rfid.PCD_Init();
  lcdPrint("UR10e ZTA","POKA-YOKE v2.0");
  delay(2000);
  showIdle();
  logSerial("SYSTEM_BOOT");
}

void showIdle(){
  authState=IDLE; currentUser=nullptr; pinBuffer=""; currentStep=0;
  lcdPrint("JOINT: NOMINAL","SCAN=ROLE CHECK");
  logSerial("STATE_IDLE");
}

// ── MAIN LOOP ────────────────────────────────────────────────
void loop(){

  // Lockout timer
  if(failedPins>=3 && millis()<lockoutUntil){
    long s=(lockoutUntil-millis())/1000;
    lcdPrint("LOCKED OUT","Wait: "+String(s)+"s");
    delay(500); return;
  } else if(failedPins>=3 && millis()>=lockoutUntil){
    failedPins=0; authState=AWAIT_RFID;
    lcdPrint("LOCKOUT LIFTED","SCAN BADGE");
    logSerial("LOCKOUT_LIFTED");
    delay(1500);
  }

  // Listen for fault from Squad 1
  if(Serial.available()){
    String msg=Serial.readStringUntil('\n'); msg.trim();
    if(msg.startsWith("FAULT|") && authState==IDLE){
      faultReason=msg.substring(6,msg.indexOf('|',6));
      lcdPrint("FAULT DETECTED",faultReason);
      logSerial("FAULT_RECEIVED|"+faultReason);
      delay(2500);
      authState=AWAIT_RFID;
      lcdPrint("SCAN BADGE","MFA REQUIRED");
    }
  }

  // ── RFID SCAN ─────────────────────────────────────────────
  if(authState==AWAIT_RFID || authState==IDLE){
    RFIDUser* u=identifyCard();
    if(u!=nullptr){
      currentUser=u;
      logSerial("CARD_SCAN|"+u->role+"|"+u->name);

      if(authState==IDLE){
        lcdPrint(u->name,u->role+" VERIFIED");
        logSerial("ROLE_CHECK_OK|"+u->role);
        delay(2500); showIdle(); return;
      }

      if(u->role=="WORKER"){
        lcdPrint("ERR:INSUF.PRIV",u->name+" DENIED");
        logSerial("ACCESS_DENIED|"+u->name+"|reason=insufficient_clearance");
        humanErrors++;
        Serial.println("HUMAN_ERROR|WRONG_BADGE|"+String(humanErrors));
        delay(3000);
        lcdPrint("SCAN BADGE","MFA REQUIRED");
        return;
      }

      // Tech or Engineer → PIN
      lcdPrint("BADGE:"+u->role,"ENTER PIN:");
      logSerial("FACTOR1_OK|"+u->role);
      Serial.println("FACTOR1_OK|"+u->role);
      authState=AWAIT_PIN; pinBuffer="";
    }
  }

  // ── PIN ───────────────────────────────────────────────────
  if(authState==AWAIT_PIN){
    char k=keypad.getKey();
    if(k!=NO_KEY){
      if(k=='*'){ pinBuffer=""; lcdPrint("BADGE:"+currentUser->role,"PIN:____"); }
      else if(k=='#'){
        if(pinBuffer==currentUser->pin){
          failedPins=0;
          logSerial("FACTOR2_OK|"+currentUser->role);
          Serial.println("FACTOR2_OK|"+currentUser->role);
          lcdPrint("PIN VERIFIED","STARTING CHECK..");
          delay(1500);
          authState=POKA_YOKE; currentStep=0;
          showPokaYokeStep();
        } else {
          failedPins++;
          humanErrors++;
          logSerial("FACTOR2_FAIL|attempt="+String(failedPins));
          Serial.println("HUMAN_ERROR|WRONG_PIN|"+String(humanErrors));
          lcdPrint("WRONG PIN","Tries:"+String(failedPins)+"/3");
          delay(2000);
          if(failedPins>=3){
            lockoutUntil=millis()+30000;
            lcdPrint("LOCKED:3 FAILS","30s LOCKOUT");
            logSerial("LOCKOUT_TRIGGERED|3_failed_pins");
            Serial.println("LOCKOUT|30s");
            delay(2000);
          } else {
            lcdPrint("BADGE:"+currentUser->role,"RETRY PIN:____");
            pinBuffer="";
          }
        }
      } else if(pinBuffer.length()<4){
        pinBuffer+=k;
        String mask="";
        for(int i=0;i<4;i++) mask+=(i<(int)pinBuffer.length()?"*":"_");
        lcdPrint("BADGE:"+currentUser->role,"PIN:"+mask);
      }
    }
  }

  // ── POKA-YOKE CHECKLIST ───────────────────────────────────
  // Technician MUST complete each manual inspection step
  // Cannot skip — enforces UR10e manual procedure
  if(authState==POKA_YOKE){
    char k=keypad.getKey();
    if(k!=NO_KEY){
      char expected=steps[currentStep].confirmKey;

      if(k==expected){
        // Correct step confirmed
        logSerial("STEP_CONFIRMED|step="+String(currentStep+1)+"|by="+currentUser->role);
        Serial.println("STEP_OK|"+String(currentStep+1));
        currentStep++;
        if(currentStep>=NUM_STEPS){
          // All steps complete — safe to reset
          authState=COMPLETE;
          lcdPrint("ALL CHECKS DONE","RESETTING JOINT");
          logSerial("POKA_YOKE_COMPLETE|errors="+String(humanErrors));
          Serial.println("MFA_RESET_OK");
          delay(2000);
          showIdle();
        } else {
          showPokaYokeStep();
        }
      } else if(k=='*'){
        // Tech tried to skip — LOG as human error
        humanErrors++;
        lcdPrint("CANNOT SKIP","Err:"+String(humanErrors));
        logSerial("HUMAN_ERROR|SKIPPED_STEP|step="+String(currentStep+1));
        Serial.println("HUMAN_ERROR|SKIP_STEP|"+String(humanErrors));
        delay(2000);
        showPokaYokeStep(); // Show same step again
      } else {
        // Wrong key pressed
        humanErrors++;
        lcdPrint("WRONG KEY","Expected:"+String(expected));
        logSerial("HUMAN_ERROR|WRONG_KEY|expected="+String(expected)+"|got="+String(k));
        Serial.println("HUMAN_ERROR|WRONG_KEY|"+String(humanErrors));
        delay(1500);
        showPokaYokeStep();
      }
    }
  }

  delay(50);
}

void showPokaYokeStep(){
  String progress="["+String(currentStep+1)+"/"+String(NUM_STEPS)+"]";
  lcdPrint(progress+" "+steps[currentStep].instruction, steps[currentStep].detail);
  logSerial("SHOWING_STEP|"+String(currentStep+1)+"|"+steps[currentStep].instruction);
}
