// ============================================================
// POWER-SHIFT REDUNDANCY MATRIX — Live Dashboard
// Processing 4.x  (processing.org — free download)
// Run this WHILE Arduino is connected via USB
// ============================================================
// Change COM_PORT to match your Arduino port:
//   Windows: "COM3", "COM4", etc.
//   Mac/Linux: "/dev/ttyUSB0" or "/dev/ttyACM0"
// ============================================================

import processing.serial.*;

Serial port;
String COM_PORT = "COM3"; // ← CHANGE THIS

// State
float voltage = 220;
float voltageHistory[] = new float[200];
String systemState = "NORMAL";
String faultMsg = "";
int faultFlash = 0;
long lastUpdate = 0;

// Colors
color BG        = color(10, 14, 20);
color GREEN     = color(0, 210, 100);
color RED       = color(248, 81, 73);
color YELLOW    = color(227, 179, 65);
color BLUE      = color(88, 166, 255);
color DIM       = color(40, 50, 65);
color WHITE     = color(220, 225, 235);

void setup() {
  size(900, 520);
  smooth(4);
  textFont(createFont("Courier New Bold", 14));

  // Shift voltage history
  for (int i = 0; i < voltageHistory.length; i++) voltageHistory[i] = 220;

  // Connect to Arduino
  try {
    port = new Serial(this, COM_PORT, 9600);
    port.bufferUntil('\n');
  } catch (Exception e) {
    println("Serial port not found — running in DEMO mode");
  }
}

void serialEvent(Serial p) {
  String raw = trim(p.readStringUntil('\n'));
  if (raw == null) return;
  println("SERIAL: " + raw);

  // Parse "Power reading: 512 | State: NORMAL"
  if (raw.startsWith("Power reading:")) {
    String[] parts = raw.split("\\|");
    // Extract raw ADC value and map to voltage
    String numStr = parts[0].replace("Power reading:", "").trim();
    int adc = int(numStr);
    voltage = map(adc, 0, 1023, 0, 440);

    // Extract state
    if (parts.length > 1) {
      String statePart = parts[1].replace("State:", "").trim();
      systemState = statePart;
    }
  }
  if (raw.contains("SURGE DETECTED"))    { systemState = "SURGE";    faultMsg = "POWER SURGE"; }
  if (raw.contains("BROWNOUT DETECTED")) { systemState = "BROWNOUT"; faultMsg = "BROWNOUT"; }
  if (raw.contains("RESETTING"))         { systemState = "NORMAL";   faultMsg = ""; }

  lastUpdate = millis();
}

void draw() {
  background(BG);

  // Demo mode: animate voltage if no serial
  if (port == null) {
    voltage = 220 + sin(frameCount * 0.03) * 30;
    if (frameCount % 300 == 0) {
      systemState = "SURGE"; faultMsg = "POWER SURGE";
    }
    if (frameCount % 400 == 0) {
      systemState = "NORMAL"; faultMsg = "";
    }
  }

  // Scroll voltage history
  for (int i = 0; i < voltageHistory.length - 1; i++) {
    voltageHistory[i] = voltageHistory[i + 1];
  }
  voltageHistory[voltageHistory.length - 1] = voltage;

  drawHeader();
  drawVoltageGauge();
  drawWaveform();
  drawStatusPanel();
  drawRelayStatus();
  drawFooter();
}

void drawHeader() {
  fill(WHITE); textSize(18);
  text("⚡  POWER-SHIFT REDUNDANCY MATRIX", 24, 36);
  fill(DIM); textSize(11);
  text("INDUSTRIAL GRID FAULT DETECTION  |  REAL-TIME MONITOR", 24, 54);

  // Connection dot
  fill(port != null ? GREEN : YELLOW);
  ellipse(870, 28, 10, 10);
  fill(DIM); textSize(10);
  text(port != null ? "LIVE" : "DEMO", 845, 32);

  // Divider
  stroke(DIM); strokeWeight(1);
  line(20, 62, 880, 62);
  noStroke();
}

void drawVoltageGauge() {
  int cx = 130, cy = 230, r = 95;

  // Determine color
  color gaugeColor = GREEN;
  if (voltage > 300 || voltage < 140) gaugeColor = RED;
  else if (voltage > 270 || voltage < 170) gaugeColor = YELLOW;

  // Background arc
  stroke(DIM); strokeWeight(14); noFill();
  arc(cx, cy, r*2, r*2, PI * 0.75, PI * 2.25);

  // Value arc
  float angle = map(constrain(voltage, 0, 440), 0, 440, PI * 0.75, PI * 2.25);
  stroke(gaugeColor); strokeWeight(12);
  arc(cx, cy, r*2, r*2, PI * 0.75, angle);
  noStroke();

  // Center value
  fill(gaugeColor); textSize(28);
  textAlign(CENTER, CENTER);
  text(nf(voltage, 0, 0) + "V", cx, cy - 10);
  fill(DIM); textSize(11);
  text("GRID VOLTAGE", cx, cy + 22);
  textAlign(LEFT, BASELINE);

  // Zone labels
  fill(GREEN); textSize(9);
  text("NORMAL", cx - 48, cy + 88);
  fill(RED);
  text("SURGE", cx + 22, cy + 88);
  fill(RED);
  text("LOW", cx - 92, cy + 20);

  // Safe range markers
  fill(DIM); textSize(10);
  text("140V", cx - 92, cy + 42);
  text("300V", cx + 52, cy + 42);
}

void drawWaveform() {
  int wx = 260, wy = 100, ww = 600, wh = 150;

  // Background
  fill(15, 20, 30); noStroke();
  rect(wx, wy, ww, wh, 6);

  // Grid lines
  stroke(DIM); strokeWeight(0.5);
  for (int i = 1; i < 4; i++) {
    line(wx, wy + wh * i/4, wx + ww, wy + wh * i/4);
  }
  // Danger zone lines
  stroke(RED); strokeWeight(0.8);
  float surgeY  = map(300, 0, 440, wy + wh, wy);
  float brownoutY = map(140, 0, 440, wy + wh, wy);
  line(wx, surgeY, wx + ww, surgeY);
  line(wx, brownoutY, wx + ww, brownoutY);

  // Waveform
  noFill();
  strokeWeight(2);
  beginShape();
  for (int i = 0; i < voltageHistory.length; i++) {
    float x = map(i, 0, voltageHistory.length - 1, wx, wx + ww);
    float y = map(voltageHistory[i], 0, 440, wy + wh, wy);
    color c = (voltageHistory[i] > 300 || voltageHistory[i] < 140) ? RED : GREEN;
    stroke(c);
    vertex(x, y);
  }
  endShape();
  noStroke();

  // Labels
  fill(DIM); textSize(9);
  text("SURGE THRESHOLD 300V", wx + 4, surgeY - 3);
  text("BROWNOUT THRESHOLD 140V", wx + 4, brownoutY - 3);
  fill(WHITE); textSize(11);
  text("VOLTAGE WAVEFORM", wx + 4, wy + 14);
  fill(DIM); textSize(10);
  text("REAL-TIME  ←──────────────────────────────────────────────────────", wx + 100, wy + 14);
}

void drawStatusPanel() {
  int px = 260, py = 270;

  // State box
  color stateColor = (systemState.equals("NORMAL")) ? GREEN : RED;
  if (systemState.equals("LOCKED")) stateColor = YELLOW;

  fill(stateColor, 30);
  rect(px, py, 290, 110, 6);
  stroke(stateColor); strokeWeight(1.5);
  rect(px, py, 290, 110, 6);
  noStroke();

  fill(stateColor); textSize(13);
  text("SYSTEM STATE", px + 12, py + 22);

  textSize(20);
  if (systemState.equals("NORMAL")) {
    text("● NOMINAL", px + 12, py + 52);
    fill(DIM); textSize(11);
    text("All systems operating within", px + 12, py + 74);
    text("safe parameters.", px + 12, py + 90);
  } else if (systemState.equals("SURGE")) {
    faultFlash++;
    fill(faultFlash % 20 < 10 ? RED : color(180,40,40)); textSize(20);
    text("⚠ POWER SURGE", px + 12, py + 52);
    fill(WHITE); textSize(11);
    text("Motor disconnected. Grid locked.", px + 12, py + 74);
    text("Awaiting technician badge.", px + 12, py + 90);
  } else if (systemState.equals("BROWNOUT")) {
    faultFlash++;
    fill(faultFlash % 20 < 10 ? RED : color(180,40,40)); textSize(20);
    text("⚠ BROWNOUT", px + 12, py + 52);
    fill(WHITE); textSize(11);
    text("Undervoltage detected. Grid locked.", px + 12, py + 74);
    text("Awaiting technician badge.", px + 12, py + 90);
  } else if (systemState.equals("LOCKED")) {
    fill(YELLOW); textSize(20);
    text("🔒 LOCKED", px + 12, py + 52);
    fill(WHITE); textSize(11);
    text("Scan authorized RFID badge", px + 12, py + 74);
    text("to reset the grid.", px + 12, py + 90);
  }
}

void drawRelayStatus() {
  int rx = 570, ry = 270;

  boolean relayOpen = !systemState.equals("NORMAL");
  color relayColor = relayOpen ? RED : GREEN;

  fill(20, 26, 36); noStroke();
  rect(rx, ry, 290, 110, 6);
  stroke(DIM); strokeWeight(1);
  rect(rx, ry, 290, 110, 6);
  noStroke();

  fill(WHITE); textSize(13);
  text("RELAY / MOTOR STATUS", rx + 12, ry + 22);

  // Relay diagram
  int lx = rx + 20, ly = ry + 55;
  stroke(relayColor); strokeWeight(3);
  // Input wire
  line(lx, ly, lx + 40, ly);
  // Relay switch
  if (relayOpen) {
    // Open circuit — angled gap
    line(lx + 40, ly, lx + 65, ly - 20);
    line(lx + 75, ly, lx + 110, ly);
  } else {
    // Closed circuit
    line(lx + 40, ly, lx + 110, ly);
  }
  // Output wire
  line(lx + 110, ly, lx + 150, ly);
  noStroke();

  // Motor icon
  fill(relayColor, 60);
  ellipse(lx + 170, ly, 32, 32);
  fill(relayColor); textSize(11);
  textAlign(CENTER, CENTER);
  text("M", lx + 170, ly);
  textAlign(LEFT, BASELINE);

  fill(relayColor); textSize(12);
  text(relayOpen ? "OPEN — Motor Protected" : "CLOSED — Motor Running", rx + 12, ry + 92);
}

void drawFooter() {
  stroke(DIM); strokeWeight(1);
  line(20, 460, 880, 460);
  noStroke();

  fill(DIM); textSize(10);
  text("NORMAL RANGE: 140V – 300V    |    SURGE THRESHOLD: > 300V    |    BROWNOUT THRESHOLD: < 140V    |    PRESS 'R' TO SIMULATE RESET", 24, 478);

  // Time since last update
  if (port != null) {
    long ago = (millis() - lastUpdate) / 1000;
    text("LAST DATA: " + ago + "s ago", 700, 500);
  }
}

// Press R to simulate tech reset (for demo without RFID)
void keyPressed() {
  if (key == 'r' || key == 'R') {
    systemState = "NORMAL";
    faultMsg = "";
    println("Manual reset triggered");
  }
  if (key == 's') { systemState = "SURGE"; faultMsg = "POWER SURGE"; }
  if (key == 'b') { systemState = "BROWNOUT"; faultMsg = "BROWNOUT"; }
}
