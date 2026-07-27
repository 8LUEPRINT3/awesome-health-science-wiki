// ============================================================
// SQUAD 1: CONTINUOUS VERIFICATION POWER LOOP
// UR10e Elbow Joint — ZTA Micro-Segmentation
// Hardware: Potentiometer + 5V Relay + Stepper Motor + LEDs
// ============================================================
// WIRING:
//   Potentiometer middle → A0, sides → 5V & GND
//   Relay IN             → Pin 7
//   Relay COM            → Stepper VCC
//   Green LED            → Pin 4 (220Ω to GND)
//   Red LED              → Pin 5 (220Ω to GND)
//   Stepper IN1-IN4      → Pins 8,9,10,11 (28BYJ-48)
// ============================================================

#include <Stepper.h>

// ── PINS ────────────────────────────────────────────────────
#define POT_PIN      A0
#define RELAY_PIN     7
#define GREEN_LED     4
#define RED_LED       5

// Stepper (28BYJ-48 = 2048 steps/rev via ULN2003 driver)
#define STEPS_PER_REV 2048
Stepper elbowJoint(STEPS_PER_REV, 8, 10, 9, 11);

// ── THRESHOLDS ───────────────────────────────────────────────
// Potentiometer = simulated joint current draw (0–1023)
// Normal operating load for UR10e elbow: mid-range
#define LOAD_LOW     250   // Below = underload / joint stall
#define LOAD_HIGH    750   // Above = overload / gear strip risk

// ── GLOBALS ─────────────────────────────────────────────────
enum JointState { RUNNING, FAULT_OVERLOAD, FAULT_STALL, LOCKED };
JointState jointState = RUNNING;

int   currentLoad    = 0;
bool  stepperRunning = false;
unsigned long lastPrint = 0;

// ── SETUP ───────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED,   OUTPUT);

  elbowJoint.setSpeed(12); // 12 RPM — smooth cobot speed

  Serial.println("=== UR10e ELBOW JOINT — ZTA MONITOR ===");
  Serial.println("Joint: ONLINE | Trust: VERIFIED");
  setRunning();
}

// ── HELPERS ─────────────────────────────────────────────────
void setRunning() {
  jointState   = RUNNING;
  stepperRunning = true;

  // Relay CLOSED = joint powered
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED,   LOW);

  Serial.println("JOINT STATUS: RUNNING | RELAY: CLOSED | TRUST: VERIFIED");
}

void cutJoint(String reason) {
  jointState   = LOCKED;
  stepperRunning = false;

  // Relay OPEN = joint air-gapped (micro-segmented)
  digitalWrite(RELAY_PIN, HIGH);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED,   HIGH);

  Serial.println("ZTA LOCKOUT: UR10e ELBOW FAULT");
  Serial.println("REASON: " + reason);
  Serial.println("MICRO-SEGMENTATION: ACTIVE");
  Serial.println("AWAITING MFA RECOVERY...");

  // Send structured data for dashboard
  Serial.println("FAULT|" + reason + "|" + String(currentLoad));
}

// ── MAIN LOOP ───────────────────────────────────────────────
void loop() {
  currentLoad = analogRead(POT_PIN);

  // Print telemetry every 300ms for dashboard
  if (millis() - lastPrint > 300) {
    int loadPct = map(currentLoad, 0, 1023, 0, 100);
    Serial.println("LOAD|" + String(currentLoad) + "|" + String(loadPct));
    lastPrint = millis();
  }

  if (jointState == RUNNING) {

    // ── OVERLOAD: gear stripping risk ──────────────────────
    if (currentLoad > LOAD_HIGH) {
      cutJoint("OVERLOAD");
    }
    // ── STALL: joint physically blocked ────────────────────
    else if (currentLoad < LOAD_LOW) {
      cutJoint("JOINT STALL");
    }
    // ── NORMAL: keep spinning ──────────────────────────────
    else {
      // Spin speed proportional to load (realistic cobot behavior)
      int rpm = map(currentLoad, LOAD_LOW, LOAD_HIGH, 6, 15);
      elbowJoint.setSpeed(rpm);
      elbowJoint.step(64); // Small incremental steps
    }

  } else if (jointState == LOCKED) {

    // Flash red LED while locked
    static unsigned long lastBlink = 0;
    static bool ledState = false;
    if (millis() - lastBlink > 400) {
      ledState = !ledState;
      digitalWrite(RED_LED, ledState);
      lastBlink = millis();
    }

    // Listen for MFA reset command from Squad 2 over Serial
    if (Serial.available()) {
      String cmd = Serial.readStringUntil('\n');
      cmd.trim();
      if (cmd == "MFA_RESET_OK") {
        Serial.println("TRUST VERIFIED: JOINT RESET");
        setRunning();
      }
    }
  }

  // No delay — poll as fast as possible (ZTA continuous verification)
}
