/*
 * ============================================================
 *  ROBOT FAILURE DETECTOR v2
 *  Honda/OVIN Hackathon — Elegoo MEGA Kit
 * ============================================================
 *  WIRING:
 *    Potentiometer middle pin → A0
 *    DHT11 signal pin         → Pin 7
 *    Vibration sensor DO      → Pin 2
 *    IR sensor OUT            → Pin 3
 *    Green LED                → Pin 4  (+ 220Ω to GND)
 *    Red LED                  → Pin 5  (+ 220Ω to GND)
 *    Yellow LED               → Pin 6  (+ 220Ω to GND)
 *    Active Buzzer +          → Pin 8
 *    LCD I2C SDA              → Pin 20
 *    LCD I2C SCL              → Pin 21
 * ============================================================
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

// ── PINS ─────────────────────────────────────────────────────
#define LOAD_PIN        A0
#define DHT_PIN          7
#define DHT_TYPE      DHT11
#define VIBRATION_PIN    2
#define IR_PIN           3
#define GREEN_LED        4
#define RED_LED          5
#define AMBER_LED        6
#define BUZZER           8

// ── THRESHOLDS ───────────────────────────────────────────────
#define LOAD_AMBER      65.0   // % — motor working hard
#define LOAD_RED        80.0   // % — motor overloaded
#define TEMP_AMBER      35.0   // °C — getting warm (DHT11 room demo)
#define TEMP_RED        40.0   // °C — overheat (raise finger off sensor)
#define DRIFT_WATCH      5.0   // % drift above baseline = watch
#define DRIFT_FAULT     20.0   // % drift = gear degraded
#define STALL_MS       1500    // ms no rotation + load = stall
#define BASELINE_N      100    // samples to learn baseline (~10s)

// ── OBJECTS ──────────────────────────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);  // try 0x3F if blank
DHT dht(DHT_PIN, DHT_TYPE);

// ── STATE ────────────────────────────────────────────────────
float   baselineLoad   = -1;
float   baselineSum    = 0;
int     baselineCount  = 0;
bool    baselineLocked = false;

float   smoothLoad  = 50.0;
float   smoothTemp  = 25.0;
float   smoothDrift = 0.0;

unsigned long lastRotation = 0;
int     vibCount           = 0;
unsigned long vibWindow    = 0;

String  zone       = "GREEN";
unsigned long lastBuzz   = 0;
unsigned long lastLCD    = 0;
unsigned long lastSerial = 0;
unsigned long lastDHT    = 0;

// ─────────────────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  pinMode(GREEN_LED,     OUTPUT);
  pinMode(AMBER_LED,     OUTPUT);
  pinMode(RED_LED,       OUTPUT);
  pinMode(BUZZER,        OUTPUT);
  pinMode(VIBRATION_PIN, INPUT);
  pinMode(IR_PIN,        INPUT_PULLUP);

  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0); lcd.print("ROBOT MONITOR");
  lcd.setCursor(0, 1); lcd.print("Learning...    ");

  digitalWrite(GREEN_LED, HIGH);
  Serial.println("BOOT|RobotFailureDetector|v2.0|DHT11");
}

// ─────────────────────────────────────────────────────────────
void loop() {

  unsigned long now = millis();

  // ── READ LOAD SENSOR (potentiometer) ─────────────────────
  float rawLoad = analogRead(LOAD_PIN) / 1023.0 * 100.0;
  smoothLoad = smoothLoad * 0.85 + rawLoad * 0.15;

  // ── READ TEMPERATURE (DHT11 — max 1 read per 2s) ─────────
  if (now - lastDHT > 2000) {
    lastDHT = now;
    float t = dht.readTemperature();
    if (!isnan(t)) {
      smoothTemp = smoothTemp * 0.7 + t * 0.3;
    }
  }

  // ── BASELINE LEARNING (first ~10 seconds) ────────────────
  if (!baselineLocked) {
    baselineSum += smoothLoad;
    baselineCount++;

    // Show progress on LCD
    if (now - lastLCD > 500) {
      lastLCD = now;
      lcd.setCursor(0, 1);
      lcd.print("Learn:");
      lcd.print(baselineCount);
      lcd.print("/");
      lcd.print(BASELINE_N);
      lcd.print("     ");
    }

    if (baselineCount >= BASELINE_N) {
      baselineLoad   = baselineSum / baselineCount;
      baselineLocked = true;
      lcd.setCursor(0, 1);
      lcd.print("READY          ");
      Serial.print("BASELINE|");
      Serial.println(baselineLoad, 1);
    }
    delay(100);
    return;
  }

  // ── DRIFT FROM BASELINE ───────────────────────────────────
  float rawDrift = ((smoothLoad - baselineLoad) / baselineLoad) * 100.0;
  smoothDrift = smoothDrift * 0.88 + rawDrift * 0.12;

  // ── STALL DETECTION (IR sensor) ──────────────────────────
  bool irNow = digitalRead(IR_PIN);
  if (irNow == LOW) lastRotation = now;
  bool stalled = (smoothLoad > 30) && (now - lastRotation > STALL_MS);

  // ── MOTOR FAULT CONDITIONS ────────────────────────────────
  bool motorOverload = smoothLoad >= LOAD_RED;
  bool motorOverheat = smoothTemp >= TEMP_RED;
  bool motorWarnLoad = smoothLoad >= LOAD_AMBER;
  bool motorWarnTemp = smoothTemp >= TEMP_AMBER;
  bool motorFault    = motorOverload || motorOverheat || stalled;

  // ── GEAR / VIBRATION DETECTION ────────────────────────────
  bool vibNow = digitalRead(VIBRATION_PIN);
  if (vibNow == HIGH) {
    if (now - vibWindow > 2000) { vibWindow = now; vibCount = 0; }
    vibCount++;
  }
  bool gearVibFault   = (vibCount >= 5) && (smoothLoad > 40);
  bool gearDriftFault = (smoothDrift >= DRIFT_FAULT);
  bool gearWarnDrift  = (smoothDrift >= DRIFT_WATCH);
  bool gearFault      = gearVibFault || gearDriftFault;

  // ── DETERMINE ZONE ────────────────────────────────────────
  String newZone;
  String faultDesc;

  if (motorFault || gearFault) {
    newZone = "RED";
    if      (stalled)       faultDesc = "MOTOR:STALL";
    else if (motorOverheat) faultDesc = "MOTOR:OVERHEAT";
    else if (motorOverload) faultDesc = "MOTOR:OVERLOAD";
    else if (gearVibFault)  faultDesc = "GEAR:VIBRATION";
    else                    faultDesc = "JOINT:DEGRADED";
  }
  else if (motorWarnLoad || motorWarnTemp || gearWarnDrift) {
    newZone = "AMBER";
    if      (motorWarnTemp) faultDesc = "TEMP HIGH";
    else if (gearWarnDrift) faultDesc = "JOINT DRIFT";
    else                    faultDesc = "LOAD HIGH";
  }
  else {
    newZone   = "GREEN";
    faultDesc = "ALL NORMAL";
  }

  // ── LEDs ─────────────────────────────────────────────────
  digitalWrite(GREEN_LED, newZone == "GREEN" ? HIGH : LOW);
  digitalWrite(AMBER_LED, newZone == "AMBER" ? HIGH : LOW);
  digitalWrite(RED_LED,   newZone == "RED"   ? HIGH : LOW);

  // ── BUZZER ───────────────────────────────────────────────
  if (newZone == "RED" && now - lastBuzz > 500) {
    tone(BUZZER, 1200, 400);
    lastBuzz = now;
  }
  else if (newZone == "AMBER" && now - lastBuzz > 2000) {
    tone(BUZZER, 800, 100); delay(150); tone(BUZZER, 800, 100);
    lastBuzz = now;
  }

  // ── LCD ──────────────────────────────────────────────────
  if (now - lastLCD > 600) {
    lastLCD = now;
    lcd.setCursor(0, 0);
    if (newZone == "GREEN") {
      lcd.print("OK L:");
      lcd.print((int)smoothLoad);
      lcd.print("% T:");
      lcd.print((int)smoothTemp);
      lcd.print("C  ");
    } else {
      lcd.print(newZone == "RED" ? "FAULT:" : "WARN: ");
      lcd.print(faultDesc.substring(0, 10));
      lcd.print("  ");
    }
    lcd.setCursor(0, 1);
    lcd.print("D:");
    lcd.print(smoothDrift, 1);
    lcd.print("% V:");
    lcd.print(vibCount);
    lcd.print("      ");
  }

  // ── SERIAL → DASHBOARD ───────────────────────────────────
  if (now - lastSerial > 200) {
    lastSerial = now;
    Serial.print("DATA|");
    Serial.print(newZone);        Serial.print("|");
    Serial.print(smoothLoad, 1);  Serial.print("|");
    Serial.print(smoothTemp, 1);  Serial.print("|");
    Serial.print(smoothDrift, 1); Serial.print("|");
    Serial.print(vibCount);       Serial.print("|");
    Serial.println(stalled ? "STALL" : "OK");

    if (newZone != zone) {
      if (newZone == "RED")   { Serial.print("FAULT|"); Serial.print(faultDesc); Serial.print("|"); Serial.println(now); }
      if (newZone == "AMBER") { Serial.print("WARN|");  Serial.print(faultDesc); Serial.print("|"); Serial.println(now); }
      if (newZone == "GREEN" && zone != "") { Serial.print("RECOVERED|"); Serial.println(now); }
      zone = newZone;
    }
  }

  delay(80);
}
