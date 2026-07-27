// ============================================================
// SQUAD 1: PREDICTIVE MAINTENANCE — ZTA JOINT MONITOR
// UR10e Elbow Joint — 3-Zone + Trend Analysis
// Hardware: Potentiometer + 5V Relay + Stepper + LEDs + Buzzer
// ============================================================
// WIRING:
//   Potentiometer middle → A0, sides → 5V & GND
//   Relay IN             → Pin 7
//   Green LED            → Pin 4 (220Ω to GND)
//   Amber/Yellow LED     → Pin 6 (220Ω to GND)
//   Red LED              → Pin 5 (220Ω to GND)
//   Buzzer               → Pin 3
//   Stepper IN1-IN4      → Pins 8,10,9,11
// ============================================================

#include <Stepper.h>

// ── PINS ────────────────────────────────────────────────────
#define POT_PIN      A0
#define RELAY_PIN     7
#define GREEN_LED     4
#define AMBER_LED     6
#define RED_LED       5
#define BUZZER_PIN    3

#define STEPS_PER_REV 2048
Stepper elbowJoint(STEPS_PER_REV, 8, 10, 9, 11);

// ── THRESHOLDS (as % of 1023) ────────────────────────────────
#define STALL_LOW       256   // 25% — stall risk
#define CAUTION_LOW     409   // 40% — caution low
#define CAUTION_HIGH    665   // 65% — caution high
#define OVERLOAD_HIGH   819   // 80% — overload

// ── TREND ────────────────────────────────────────────────────
#define HISTORY_SIZE     20
float   loadHistory[HISTORY_SIZE];
int     histIndex        = 0;
bool    historyFull      = false;
float   currentTrend     = 0.0;
int     minutesToFault   = -1;

// ── STATE ────────────────────────────────────────────────────
enum Zone { ZONE_GREEN, ZONE_AMBER_LOW, ZONE_AMBER_HIGH, ZONE_RED };
Zone    currentZone      = ZONE_GREEN;
Zone    lastZone         = ZONE_GREEN;
bool    jointShutdown    = false;
int     currentLoad      = 0;
int     currentLoadPct   = 0;
unsigned long lastPrint  = 0;
unsigned long lastBuzzer = 0;
unsigned long lastTrend  = 0;
bool    buzzerOn         = false;

// ── SETUP ───────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(AMBER_LED, OUTPUT);
  pinMode(RED_LED,   OUTPUT);
  pinMode(BUZZER_PIN,OUTPUT);

  elbowJoint.setSpeed(10);

  // Fill history with baseline
  for (int i = 0; i < HISTORY_SIZE; i++) loadHistory[i] = 512;

  // Start healthy
  setGreen();

  Serial.println("=== UR10e ELBOW — PREDICTIVE ZTA MONITOR ===");
  Serial.println("ZONE|GREEN|0|0|STABLE");
}

// ── ZONE SETTERS ─────────────────────────────────────────────
void setGreen() {
  currentZone = ZONE_GREEN;
  digitalWrite(RELAY_PIN, LOW);   // Joint powered
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(AMBER_LED, LOW);
  digitalWrite(RED_LED,   LOW);
  noTone(BUZZER_PIN);
}

void setAmber(String reason) {
  currentZone = ZONE_AMBER_HIGH;
  digitalWrite(RELAY_PIN, LOW);   // Joint STILL POWERED — just warning
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(AMBER_LED, HIGH);
  digitalWrite(RED_LED,   LOW);
  // Slow beep every 4 seconds
}

void setRed(String reason) {
  currentZone = ZONE_RED;
  jointShutdown = true;
  digitalWrite(RELAY_PIN, HIGH);  // Cut joint — micro-segmentation
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(AMBER_LED, LOW);
  digitalWrite(RED_LED,   HIGH);
  tone(BUZZER_PIN, 880);          // Continuous alarm
  Serial.println("FAULT|" + reason + "|" + String(currentLoad));
}

// ── TREND ANALYSIS ───────────────────────────────────────────
void updateHistory(float val) {
  loadHistory[histIndex] = val;
  histIndex = (histIndex + 1) % HISTORY_SIZE;
  if (histIndex == 0) historyFull = true;
}

float calcTrend() {
  if (!historyFull) return 0.0;
  // Compare newest 5 vs oldest 5
  float recent = 0, older = 0;
  for (int i = 0; i < 5; i++) {
    int ri = (histIndex - 1 - i + HISTORY_SIZE) % HISTORY_SIZE;
    int oi = (histIndex + i) % HISTORY_SIZE;
    recent += loadHistory[ri];
    older  += loadHistory[oi];
  }
  return (recent - older) / 5.0; // Positive = rising load
}

int estimateMinutesToFault(float trend, float currentPct) {
  // If trend is positive (rising), estimate how long to hit 80%
  if (trend <= 0.5) return -1; // Stable — no estimate
  float distToFault = (OVERLOAD_HIGH - (currentPct / 100.0 * 1023));
  // Each history sample = ~300ms → samples per minute = 200
  float samplesLeft = distToFault / trend;
  return max(1, (int)(samplesLeft / 200));
}

// ── BUZZER PATTERNS ──────────────────────────────────────────
void handleBuzzer() {
  if (currentZone == ZONE_RED) return; // Continuous handled in setRed

  unsigned long now = millis();
  if (currentZone == ZONE_AMBER_HIGH || currentZone == ZONE_AMBER_LOW) {
    // Slow double-beep every 4 seconds
    if (now - lastBuzzer > 4000) {
      tone(BUZZER_PIN, 660, 100);
      delay(150);
      tone(BUZZER_PIN, 660, 100);
      lastBuzzer = now;
    }
  } else {
    noTone(BUZZER_PIN);
  }
}

// ── MAIN LOOP ───────────────────────────────────────────────
void loop() {
  currentLoad    = analogRead(POT_PIN);
  currentLoadPct = map(currentLoad, 0, 1023, 0, 100);

  // Update rolling history every 300ms
  if (millis() - lastTrend > 300) {
    updateHistory((float)currentLoad);
    currentTrend   = calcTrend();
    minutesToFault = estimateMinutesToFault(currentTrend, currentLoadPct);
    lastTrend = millis();
  }

  // ── DETERMINE ZONE ───────────────────────────────────────
  if (!jointShutdown) {
    Zone newZone;

    if      (currentLoad >= OVERLOAD_HIGH)  newZone = ZONE_RED;
    else if (currentLoad <= STALL_LOW)      newZone = ZONE_RED;
    else if (currentLoad >= CAUTION_HIGH)   newZone = ZONE_AMBER_HIGH;
    else if (currentLoad <= CAUTION_LOW)    newZone = ZONE_AMBER_LOW;
    else                                    newZone = ZONE_GREEN;

    // Only change state on zone transition
    if (newZone != currentZone) {
      if      (newZone == ZONE_GREEN)       setGreen();
      else if (newZone == ZONE_AMBER_HIGH)  setAmber("OVERLOAD_TREND");
      else if (newZone == ZONE_AMBER_LOW)   setAmber("STALL_TREND");
      else if (newZone == ZONE_RED) {
        if (currentLoad >= OVERLOAD_HIGH)   setRed("OVERLOAD");
        else                                setRed("STALL");
      }
    }

    // Spin stepper if not red
    if (currentZone != ZONE_RED) {
      int rpm = map(currentLoad, CAUTION_LOW, CAUTION_HIGH, 5, 14);
      rpm = constrain(rpm, 5, 14);
      // Slow down in amber as warning
      if (currentZone == ZONE_AMBER_HIGH || currentZone == ZONE_AMBER_LOW)
        rpm = max(4, rpm - 4);
      elbowJoint.setSpeed(rpm);
      elbowJoint.step(32);
    }
  }

  // ── BUZZER ────────────────────────────────────────────────
  handleBuzzer();

  // ── SERIAL TELEMETRY (for dashboard) ─────────────────────
  if (millis() - lastPrint > 300) {
    String zoneStr = "GREEN";
    if (currentZone == ZONE_AMBER_HIGH || currentZone == ZONE_AMBER_LOW) zoneStr = "AMBER";
    if (currentZone == ZONE_RED)  zoneStr = "RED";

    String trendStr = "STABLE";
    if      (currentTrend >  8.0) trendStr = "RISING_FAST";
    else if (currentTrend >  3.0) trendStr = "RISING";
    else if (currentTrend < -8.0) trendStr = "FALLING_FAST";
    else if (currentTrend < -3.0) trendStr = "FALLING";

    // Format: ZONE|color|load%|trend|trendStr|minsToFault
    Serial.println("ZONE|" + zoneStr + "|" + String(currentLoadPct) +
                   "|" + String((int)currentTrend) +
                   "|" + trendStr +
                   "|" + String(minutesToFault));
    lastPrint = millis();
  }

  // ── LISTEN FOR MFA RESET ─────────────────────────────────
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "MFA_RESET_OK" && jointShutdown) {
      jointShutdown = false;
      noTone(BUZZER_PIN);
      setGreen();
      Serial.println("JOINT_RESET|OK");
    }
  }
}
