/*
 * JOINTIQ — Intelligent Robot Health Monitor
 * robot_failure_detector_v4.ino
 * Honda/OVIN Hackathon 2026
 *
 * Hardware:
 *   4x DHT11 temperature sensors  → Pins 7, 9, 11, 12 (Joints 1–3, Motor housing)
 *   3x Piezo vibration sensors    → A1, A2, A3      (Joints 1, 2, 3)
 *   1x Potentiometer              → A0              (Motor load)
 *   1x IR rotation sensor         → Pin 3           (Stall detection)
 *   3x LEDs (Green/Amber/Red)     → Pins 4, 6, 5
 *   1x Active Buzzer              → Pin 8
 *   1x LCD 1602 I2C               → Pins 20/21 (SDA/SCL)
 *
 * ⚠ Piezo sensors → analog pins A1–A3 (read amplitude, no resistor needed)
 * ⚠ DHT11 → 5V power, 10kΩ pull-up resistor between signal and 5V
 */

#include <DHT.h>
#include <LiquidCrystal_I2C.h>

// ── PIN DEFINITIONS ────────────────────────────────────────
#define POT_PIN     A0
#define PIEZO_1     A1    // Joint 1 — Base
#define PIEZO_2     A2    // Joint 2 — Shoulder
#define PIEZO_3     A3    // Joint 3 — Elbow

#define DHT_PIN_1   7     // Joint 1 temperature
#define DHT_PIN_2   9     // Joint 2 temperature
#define DHT_PIN_3   11    // Joint 3 temperature
#define DHT_PIN_4   12    // Joint 4 — Motor housing
#define DHT_TYPE    DHT11

#define IR_PIN      3     // Stall detection
#define LED_GREEN   4
#define LED_AMBER   6
#define LED_RED     5
#define BUZZER_PIN  8

// ── THRESHOLDS ─────────────────────────────────────────────
#define LOAD_AMBER        65.0   // % — start warning
#define LOAD_RED          80.0   // % — fault
#define TEMP_AMBER        35.0   // °C — warning
#define TEMP_RED          40.0   // °C — fault
#define PIEZO_AMBER       300    // analog units — moderate vibration
#define PIEZO_RED         600    // analog units — severe vibration
#define STALL_MS          1500   // ms without IR pulse = stall

// ── OBJECTS ────────────────────────────────────────────────
DHT dht1(DHT_PIN_1, DHT_TYPE);
DHT dht2(DHT_PIN_2, DHT_TYPE);
DHT dht3(DHT_PIN_3, DHT_TYPE);
DHT dht4(DHT_PIN_4, DHT_TYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2);  // try 0x3F if blank

// ── STATE ──────────────────────────────────────────────────
float   baseline       = -1;
bool    blLocked       = false;
int     blSamples      = 0;
float   blSum          = 0;
unsigned long blStart  = 0;
#define BL_LEARN_MS    10000   // 10 second baseline learn window

// Per-joint state
struct Joint {
  const char* name;
  float  temp;
  int    piezo;
  int    piezoMax;      // rolling max over 500ms window
  bool   tempFault;
  bool   piezoFault;
  bool   tempAmber;
  bool   piezoAmber;
};

Joint joints[4] = {
  {"J1-BASE",     0, 0, 0, false, false, false, false},
  {"J2-SHLDR",    0, 0, 0, false, false, false, false},
  {"J3-ELBOW",    0, 0, 0, false, false, false, false},
  {"J4-MOTOR",    0, 0, 0, false, false, false, false}
};

// Global fault state
String faultType   = "";
String faultZone   = "GREEN";
bool   faulted     = false;

// IR stall tracking
volatile unsigned long lastIR = 0;
void irPulse() { lastIR = millis(); }

// Timing
unsigned long lastDHT      = 0;
unsigned long lastSerial   = 0;
unsigned long lastLCD      = 0;
unsigned long lastPiezo    = 0;
unsigned long piezoWindow  = 0;
int           piezoMax1=0, piezoMax2=0, piezoMax3=0;

// Smoothed load
float smoothLoad = 50.0;

// ── SETUP ──────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  dht1.begin();
  dht2.begin();
  dht3.begin();
  dht4.begin();

  pinMode(IR_PIN,    INPUT_PULLUP);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_AMBER, OUTPUT);
  pinMode(LED_RED,   OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(IR_PIN), irPulse, FALLING);

  // LCD init
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0); lcd.print("JOINTIQ  v3.0");
  lcd.setCursor(0,1); lcd.print("Learning...");

  // Green LED on — healthy start
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_AMBER, LOW);
  digitalWrite(LED_RED,   LOW);

  blStart = millis();
  lastIR  = millis();

  Serial.println("# JOINTIQ v4.0 — 4x DHT11 + 3x Piezo");
  Serial.println("# FORMAT: DATA|ZONE|LOAD|T1|T2|T3|T4|P1|P2|P3|FAULT");
}

// ── MAIN LOOP ──────────────────────────────────────────────
void loop() {
  unsigned long now = millis();

  // ── Read potentiometer (motor load) ──
  int raw = analogRead(POT_PIN);
  float loadPct = (raw / 1023.0) * 100.0;
  smoothLoad = smoothLoad * 0.85 + loadPct * 0.15;

  // ── Baseline learning ──
  if (!blLocked) {
    blSum += smoothLoad;
    blSamples++;
    if (now - blStart >= BL_LEARN_MS) {
      baseline = blSum / blSamples;
      blLocked = true;
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("JOINTIQ  READY");
      lcd.setCursor(0,1); lcd.print("BL:");
      lcd.print(baseline, 1);
      lcd.print("%  4T+3P");
      Serial.print("# Baseline locked: ");
      Serial.println(baseline);
    }
    delay(50);
    return;
  }

  // ── Read piezos (every 50ms, track peak per 500ms window) ──
  int p1 = analogRead(PIEZO_1);
  int p2 = analogRead(PIEZO_2);
  int p3 = analogRead(PIEZO_3);
  if(p1 > piezoMax1) piezoMax1 = p1;
  if(p2 > piezoMax2) piezoMax2 = p2;
  if(p3 > piezoMax3) piezoMax3 = p3;

  if(now - piezoWindow >= 500) {
    joints[0].piezo = piezoMax1;
    joints[1].piezo = piezoMax2;
    joints[2].piezo = piezoMax3;
    piezoMax1 = piezoMax2 = piezoMax3 = 0;
    piezoWindow = now;
  }

  // ── Read DHT11s (every 2.5s — DHT11 limitation) ──
  if (now - lastDHT >= 2500) {
    float t1 = dht1.readTemperature();
    float t2 = dht2.readTemperature();
    float t3 = dht3.readTemperature();
    float t4 = dht4.readTemperature();
    if (!isnan(t1)) joints[0].temp = t1;
    if (!isnan(t2)) joints[1].temp = t2;
    if (!isnan(t3)) joints[2].temp = t3;
    if (!isnan(t4)) joints[3].temp = t4;
    lastDHT = now;
  }

  // ── Evaluate all joints ──
  faulted  = false;
  faultType = "";
  String worstZone = "GREEN";

  for(int i=0; i<4; i++){
    // Temperature
    joints[i].tempAmber = (joints[i].temp >= TEMP_AMBER && joints[i].temp < TEMP_RED);
    joints[i].tempFault = (joints[i].temp >= TEMP_RED);

    // Piezo vibration
    joints[i].piezoAmber = (joints[i].piezo >= PIEZO_AMBER && joints[i].piezo < PIEZO_RED);
    joints[i].piezoFault = (joints[i].piezo >= PIEZO_RED);

    if(joints[i].tempFault || joints[i].piezoFault){
      faulted = true;
      if(faultType == ""){
        faultType = String(joints[i].name) + (joints[i].tempFault ? ":OVERHEAT" : ":VIBRATION");
      }
      worstZone = "RED";
    } else if((joints[i].tempAmber || joints[i].piezoAmber) && worstZone != "RED"){
      worstZone = "AMBER";
    }
  }

  // Load faults
  if(smoothLoad >= LOAD_RED){
    faulted = true;
    if(faultType == "") faultType = "MOTOR:OVERLOAD";
    worstZone = "RED";
  } else if(smoothLoad >= LOAD_AMBER && worstZone != "RED"){
    worstZone = "AMBER";
  }

  // Stall detection
  if((now - lastIR) > STALL_MS && smoothLoad > 30){
    faulted = true;
    if(faultType == "") faultType = "MOTOR:STALL";
    worstZone = "RED";
  }

  faultZone = worstZone;

  // ── LED + Buzzer output ──
  digitalWrite(LED_GREEN, faultZone == "GREEN" ? HIGH : LOW);
  digitalWrite(LED_AMBER, faultZone == "AMBER" ? HIGH : LOW);
  digitalWrite(LED_RED,   faultZone == "RED"   ? HIGH : LOW);
  digitalWrite(BUZZER_PIN, faulted ? HIGH : LOW);

  // ── LCD update (every 800ms) ──
  if(now - lastLCD >= 800){
    lcd.clear();
    if(faulted){
      lcd.setCursor(0,0); lcd.print("!! FAULT DETECT");
      lcd.setCursor(0,1); lcd.print(faultType.substring(0,16));
    } else if(faultZone == "AMBER"){
      lcd.setCursor(0,0); lcd.print("WARNING  AMBER");
      // Show which joint is worst
      for(int i=0;i<3;i++){
        if(joints[i].tempAmber || joints[i].piezoAmber){
          lcd.setCursor(0,1); lcd.print(joints[i].name);
          lcd.print(joints[i].tempAmber?" HOT":" VIB");
          break;
        }
      }
    } else {
      lcd.setCursor(0,0); lcd.print("JOINTIQ  GREEN");
      lcd.setCursor(0,1);
      lcd.print("L:");  lcd.print((int)smoothLoad); lcd.print("% ");
      lcd.print("T:");  lcd.print((int)joints[0].temp); lcd.print("C");
    }
    lastLCD = now;
  }

  // ── Serial telemetry (every 250ms) ──
  if(now - lastSerial >= 250){
    // DATA|ZONE|LOAD|T1|T2|T3|T4|P1|P2|P3|FAULT
    Serial.print("DATA|");
    Serial.print(faultZone); Serial.print("|");
    Serial.print(smoothLoad, 1); Serial.print("|");
    Serial.print(joints[0].temp, 1); Serial.print("|");
    Serial.print(joints[1].temp, 1); Serial.print("|");
    Serial.print(joints[2].temp, 1); Serial.print("|");
    Serial.print(joints[3].temp, 1); Serial.print("|");
    Serial.print(joints[0].piezo); Serial.print("|");
    Serial.print(joints[1].piezo); Serial.print("|");
    Serial.print(joints[2].piezo); Serial.print("|");
    Serial.println(faulted ? faultType : "OK");
    lastSerial = now;
  }

  delay(50);
}
