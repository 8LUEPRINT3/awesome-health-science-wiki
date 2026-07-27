/*
 * ============================================================
 *  ROBOT FAILURE DETECTOR
 *  Honda/OVIN Hackathon — Arduino MEGA
 * ============================================================
 *  Detects two failure categories:
 *    1. MOTOR  — overload, overheat, stall
 *    2. GEAR   — vibration, bearing wear, joint degradation
 *
 *  WIRING:
 *    Potentiometer (load)  → A0
 *    LM35 temp sensor      → A1
 *    Vibration sensor      → Pin 2
 *    IR rotation sensor    → Pin 3  (LOW = rotation detected)
 *    Green LED             → Pin 4
 *    Red LED               → Pin 5
 *    Amber LED             → Pin 6
 *    Buzzer                → Pin 8
 *    LCD I2C SDA           → Pin 20
 *    LCD I2C SCL           → Pin 21
 * ============================================================
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ── PINS ─────────────────────────────────────────────────────
#define LOAD_PIN       A0
#define TEMP_PIN       A1
#define VIBRATION_PIN   2
#define IR_PIN          3
#define GREEN_LED       4
#define RED_LED         5
#define AMBER_LED       6
#define BUZZER          8

// ── THRESHOLDS ───────────────────────────────────────────────
#define LOAD_AMBER     65.0   // % load — warning
#define LOAD_RED       80.0   // % load — fault
#define TEMP_AMBER     55.0   // °C — motor warm
#define TEMP_RED       70.0   // °C — motor fault
#define DRIFT_WATCH     5.0   // % drift above baseline
#define DRIFT_FAULT    20.0   // % drift — gear degraded
#define STALL_MS      1500    // ms with no rotation = stall
#define BASELINE_N     100    // samples to learn baseline

// ── LCD ──────────────────────────────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);  // try 0x3F if blank

// ── STATE ────────────────────────────────────────────────────
float   baselineLoad   = -1;
float   baselineSum    = 0;
int     baselineCount  = 0;
bool    baselineLocked = false;

float   smoothLoad     = 50.0;
float   smoothTemp     = 25.0;
float   smoothDrift    = 0.0;

unsigned long lastRotation  = 0;
bool    lastIR              = HIGH;
int     vibCount            = 0;      // vibration events per window
unsigned long vibWindow     = 0;      // start of vibration window
bool    gearFault           = false;
bool    motorFault          = false;

String  lastFault  = "";
String  zone       = "GREEN";
unsigned long lastBuzz = 0;
unsigned long lastLCD  = 0;
unsigned long lastSerial = 0;

// ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED,    OUTPUT);
  pinMode(AMBER_LED,    OUTPUT);
  pinMode(RED_LED,      OUTPUT);
  pinMode(BUZZER,       OUTPUT);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(IR_PIN,        INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("ROBOT MONITOR");
  lcd.setCursor(0, 1); lcd.print("Learning...");

  digitalWrite(GREEN_LED, HIGH);
  Serial.println("BOOT|RobotFailureDetector|v1.0");
}

// ─────────────────────────────────────────────────────────────
void loop() {

  // ── 1. READ SENSORS ──────────────────────────────────────
  float rawLoad = analogRead(LOAD_PIN) / 1023.0 * 100.0;
  float rawTemp = (analogRead(TEMP_PIN) * 5.0 / 1023.0) * 100.0; // LM35: 10mV/°C

  // Exponential smoothing — removes jitter
  smoothLoad = smoothLoad * 0.85 + rawLoad * 0.15;
  smoothTemp = smoothTemp * 0.90 + rawTemp * 0.10;

  // ── 2. LEARN BASELINE (first ~10 seconds) ────────────────
  if (!baselineLocked) {
    baselineSum += smoothLoad;
    baselineCount++;
    if (baselineCount >= BASELINE_N) {
      baselineLoad  = baselineSum / baselineCount;
      baselineLocked = true;
      Serial.print("BASELINE|");
      Serial.println(baselineLoad, 1);
      lcd.setCursor(0, 1);
      lcd.print("Ready          ");
    }
    delay(100);
    return; // keep learning until locked
  }

  // ── 3. CALCULATE DRIFT FROM BASELINE ─────────────────────
  float rawDrift = ((smoothLoad - baselineLoad) / baselineLoad) * 100.0;
  smoothDrift = smoothDrift * 0.88 + rawDrift * 0.12;

  // ── 4. DETECT MOTOR FAILURES ─────────────────────────────

  // Stall detection — IR sees no rotation despite load
  bool irNow = digitalRead(IR_PIN);
  if (irNow == LOW) lastRotation = millis();  // rotation pulse seen
  bool stalled = (smoothLoad > 30) && (millis() - lastRotation > STALL_MS);

  // Motor fault conditions
  bool motorOverload  = smoothLoad >= LOAD_RED;
  bool motorOverheat  = smoothTemp >= TEMP_RED;
  bool motorWarnLoad  = smoothLoad >= LOAD_AMBER;
  bool motorWarnTemp  = smoothTemp >= TEMP_AMBER;

  motorFault = motorOverload || motorOverheat || stalled;

  // ── 5. DETECT GEAR / JOINT FAILURES ──────────────────────

  // Vibration counting — gear wear causes repeated vibration under load
  bool vibNow = digitalRead(VIBRATION_PIN);
  if (vibNow == HIGH) {
    if (millis() - vibWindow > 2000) {
      vibWindow = millis();  // new 2-second window
      vibCount  = 0;
    }
    vibCount++;
  }

  // Gear fault: vibration bursts + elevated load (not just a bump)
  bool gearVibFault   = (vibCount >= 5) && (smoothLoad > 40);
  // Joint degradation: long-term drift above baseline
  bool gearDriftFault = (smoothDrift >= DRIFT_FAULT);
  bool gearWarnDrift  = (smoothDrift >= DRIFT_WATCH);

  gearFault = gearVibFault || gearDriftFault;

  // ── 6. DETERMINE ZONE ────────────────────────────────────
  String newZone;
  String faultDesc;

  if (motorFault || gearFault) {
    newZone = "RED";
    if      (stalled)        faultDesc = "MOTOR:STALL";
    else if (motorOverheat)  faultDesc = "MOTOR:OVERHEAT";
    else if (motorOverload)  faultDesc = "MOTOR:OVERLOAD";
    else if (gearVibFault)   faultDesc = "GEAR:VIBRATION";
    else                     faultDesc = "JOINT:DEGRADED";
  }
  else if (motorWarnLoad || motorWarnTemp || gearWarnDrift) {
    newZone = "AMBER";
    if      (motorWarnTemp)  faultDesc = "MOTOR:TEMP HIGH";
    else if (gearWarnDrift)  faultDesc = "JOINT:DRIFTING";
    else                     faultDesc = "MOTOR:LOAD HIGH";
  }
  else {
    newZone = "GREEN";
    faultDesc = "ALL NORMAL";
  }

  // ── 7. OUTPUTS ───────────────────────────────────────────

  // LEDs
  digitalWrite(GREEN_LED, newZone == "GREEN" ? HIGH : LOW);
  digitalWrite(AMBER_LED, newZone == "AMBER" ? HIGH : LOW);
  digitalWrite(RED_LED,   newZone == "RED"   ? HIGH : LOW);

  // Buzzer patterns
  unsigned long now = millis();
  if (newZone == "RED" && now - lastBuzz > 500) {
    tone(BUZZER, 1200, 400);   // urgent continuous
    lastBuzz = now;
  }
  else if (newZone == "AMBER" && now - lastBuzz > 2000) {
    tone(BUZZER, 800, 100);    // double beep every 2s
    delay(150);
    tone(BUZZER, 800, 100);
    lastBuzz = now;
  }

  // LCD — update every 600ms (no flicker)
  if (now - lastLCD > 600) {
    lastLCD = now;
    lcd.setCursor(0, 0);
    if (newZone == "GREEN") {
      lcd.print("OK  L:");
      lcd.print((int)smoothLoad);
      lcd.print("% T:");
      lcd.print((int)smoothTemp);
      lcd.print("C   ");
    } else {
      lcd.print(newZone == "RED" ? "FAULT: " : "WARN:  ");
      lcd.print(faultDesc.substring(0, 9));
      lcd.print("       ");
    }
    lcd.setCursor(0, 1);
    lcd.print("D:");
    lcd.print(smoothDrift, 1);
    lcd.print("% V:");
    lcd.print(vibCount);
    lcd.print("       ");
  }

  // Serial — send to dashboard every 200ms
  if (now - lastSerial > 200) {
    lastSerial = now;
    Serial.print("DATA|");
    Serial.print(newZone);       Serial.print("|");
    Serial.print(smoothLoad, 1); Serial.print("|");
    Serial.print(smoothTemp, 1); Serial.print("|");
    Serial.print(smoothDrift, 1);Serial.print("|");
    Serial.print(vibCount);      Serial.print("|");
    Serial.println(stalled ? "STALL" : "OK");

    // Log fault events
    if (newZone != zone && newZone == "RED") {
      Serial.print("FAULT|");
      Serial.print(faultDesc);
      Serial.print("|");
      Serial.println(now);
    }
    if (newZone != zone && newZone == "AMBER") {
      Serial.print("WARN|");
      Serial.print(faultDesc);
      Serial.print("|");
      Serial.println(now);
    }
    if (newZone != zone && newZone == "GREEN" && zone != "") {
      Serial.print("RECOVERED|");
      Serial.println(now);
    }

    zone = newZone;
  }

  delay(80); // ~12Hz sample rate — smooth and responsive
}
