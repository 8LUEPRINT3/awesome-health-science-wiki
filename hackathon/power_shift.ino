// ============================================================
// POWER-SHIFT REDUNDANCY MATRIX
// Hackathon 2026 — Industrial Power Fault Detection System
// ============================================================
// Libraries needed (install via Arduino Library Manager):
//   - LiquidCrystal I2C  (by Frank de Bruijn / johnrickman)
//   - MFRC522             (by GithubCommunity)
// ============================================================

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

// ── PIN DEFINITIONS ─────────────────────────────────────────
#define POT_PIN       A0   // Potentiometer (simulates voltage)
#define RELAY_PIN      7   // 5V Relay module (IN pin)
#define GREEN_LED      4   // Normal power indicator
#define RED_LED        5   // Fault indicator
#define RFID_RST_PIN   9   // RFID reset
#define RFID_SS_PIN   53   // RFID SDA/SS

// ── POWER THRESHOLDS ────────────────────────────────────────
// Potentiometer reads 0–1023 on analog input
// Treat middle range as "normal" power
#define NORMAL_LOW   300   // Below this = BROWNOUT
#define NORMAL_HIGH  700   // Above this = SURGE

// ── SYSTEM STATES ───────────────────────────────────────────
enum SystemState {
  NORMAL,
  FAULT_SURGE,
  FAULT_BROWNOUT,
  LOCKED_AWAITING_TECH
};

// ── OBJECTS ─────────────────────────────────────────────────
LiquidCrystal_I2C lcd(0x27, 16, 2);  // I2C addr 0x27 (try 0x3F if blank)
MFRC522 rfid(RFID_SS_PIN, RFID_RST_PIN);

// ── GLOBALS ─────────────────────────────────────────────────
SystemState currentState = NORMAL;
String faultType = "";

// ── YOUR AUTHORIZED RFID TAG UID ────────────────────────────
// Run the system once with Serial Monitor open — it will print
// the UID of any card you scan. Paste it here.
// Example: {0xDE, 0xAD, 0xBE, 0xEF}
byte authorizedUID[] = {0xDE, 0xAD, 0xBE, 0xEF};
byte authorizedUIDLength = 4;

// ── HELPERS ─────────────────────────────────────────────────
void setNormalState() {
  currentState = NORMAL;
  faultType = "";

  // Relay OPEN = power flowing normally
  // Most relay modules: LOW = relay ON (coil energized = connected)
  // We want relay CLOSED (motor connected) when normal:
  digitalWrite(RELAY_PIN, LOW);   // Relay ON = circuit closed = motor powered
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("GRID: NOMINAL   ");
  lcd.setCursor(0, 1);
  lcd.print("POWER STABLE    ");
}

void setFaultState(String fault) {
  currentState = LOCKED_AWAITING_TECH;
  faultType = fault;

  // Relay OFF = motor disconnected = protected
  digitalWrite(RELAY_PIN, HIGH);  // Relay OFF = circuit open = motor safe
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, HIGH);

  lcd.clear();
  lcd.setCursor(0, 0);
  if (fault == "SURGE") {
    lcd.print("SYS LOCK: SURGE ");
  } else {
    lcd.print("SYS LOCK:BROWNOUT");
  }
  lcd.setCursor(0, 1);
  lcd.print("SCAN BADGE:RESET");
}

void setAuthorizedState() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TECH AUTHORIZED ");
  lcd.setCursor(0, 1);
  lcd.print("GRID RESETTING..");

  digitalWrite(RED_LED, LOW);
  // Blink green 3x as visual confirmation
  for (int i = 0; i < 3; i++) {
    digitalWrite(GREEN_LED, HIGH);
    delay(200);
    digitalWrite(GREEN_LED, LOW);
    delay(200);
  }
  delay(1000);
  setNormalState();
}

bool checkRFID() {
  // Check if a card is present
  if (!rfid.PICC_IsNewCardPresent()) return false;
  if (!rfid.PICC_ReadCardSerial()) return false;

  // Print UID to serial (useful for finding your card's UID)
  Serial.print("Card UID: ");
  for (byte i = 0; i < rfid.uid.size; i++) {
    Serial.print(rfid.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(rfid.uid.uidByte[i], HEX);
  }
  Serial.println();

  // Check if UID matches authorized card
  bool match = (rfid.uid.size == authorizedUIDLength);
  if (match) {
    for (byte i = 0; i < authorizedUIDLength; i++) {
      if (rfid.uid.uidByte[i] != authorizedUID[i]) {
        match = false;
        break;
      }
    }
  }

  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
  return match;
}

// ── SETUP ───────────────────────────────────────────────────
void setup() {
  Serial.begin(9600);

  // Pin modes
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  // LCD init
  lcd.init();
  lcd.backlight();

  // RFID init
  SPI.begin();
  rfid.PCD_Init();

  // Boot splash
  lcd.setCursor(0, 0);
  lcd.print("POWER-SHIFT v1.0");
  lcd.setCursor(0, 1);
  lcd.print("  INITIALIZING  ");
  delay(2000);

  // Start in normal state
  setNormalState();

  Serial.println("=== POWER-SHIFT REDUNDANCY MATRIX ===");
  Serial.println("Monitoring power grid...");
  Serial.print("NORMAL range: ");
  Serial.print(NORMAL_LOW);
  Serial.print(" - ");
  Serial.println(NORMAL_HIGH);
}

// ── MAIN LOOP ───────────────────────────────────────────────
void loop() {
  int powerReading = analogRead(POT_PIN);

  // Always print to serial for debugging
  Serial.print("Power reading: ");
  Serial.print(powerReading);
  Serial.print(" | State: ");
  Serial.println(currentState == NORMAL ? "NORMAL" :
                 currentState == LOCKED_AWAITING_TECH ? "LOCKED" : "FAULT");

  if (currentState == NORMAL) {
    // ── NORMAL MODE: watch for faults ──────────────────────
    if (powerReading > NORMAL_HIGH) {
      Serial.println(">>> SURGE DETECTED <<<");
      setFaultState("SURGE");

    } else if (powerReading < NORMAL_LOW) {
      Serial.println(">>> BROWNOUT DETECTED <<<");
      setFaultState("BROWNOUT");

    } else {
      // Update voltage display in real-time
      // Map raw reading to a fake "voltage" 0–440V for realism
      int displayVoltage = map(powerReading, 0, 1023, 0, 440);
      lcd.setCursor(0, 1);
      lcd.print("VOLTAGE: ");
      lcd.print(displayVoltage);
      lcd.print("V   ");
    }

  } else if (currentState == LOCKED_AWAITING_TECH) {
    // ── LOCKED MODE: wait for RFID badge ──────────────────
    if (checkRFID()) {
      Serial.println(">>> AUTHORIZED TECH SCANNED — RESETTING <<<");
      setAuthorizedState();
    } else {
      // Flash red LED to show system is locked
      static unsigned long lastBlink = 0;
      static bool ledState = false;
      if (millis() - lastBlink > 500) {
        ledState = !ledState;
        digitalWrite(RED_LED, ledState);
        lastBlink = millis();
      }
    }
  }

  delay(150); // Read ~6x per second
}
