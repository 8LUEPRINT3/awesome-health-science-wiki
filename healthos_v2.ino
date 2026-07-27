#include <M5StickCPlus2.h>
#include <WiFi.h>
#include <WebServer.h>
#include <math.h>
#include "esp32-hal-cpu.h"

// ── SETTINGS ──────────────────────────
#define STEP_THRESHOLD    0.20
#define SLOUCH_ANGLE      20.0
#define IMU_SAMPLE_RATE   20
#define UI_UPDATE_RATE    80

const char* ap_ssid     = "HealthOS-Watch";
const char* ap_password = "password123";

WebServer server(80);
M5Canvas canvas(&M5.Lcd);
TaskHandle_t WebServerTaskHandle;

// ── STATE MACHINE ──────────────────────
enum AppMode { APP_HOME = 0, APP_POSTURE, APP_BALANCE, APP_SLEEP };
volatile AppMode currentApp = APP_HOME;

// ── GLOBAL VITALS ──────────────────────
volatile int   stepCount      = 0;
volatile bool  isPanicMode    = false;
volatile bool  isSlouching    = false;
volatile float stabilityScore = 100.0;
volatile int   batteryLevel   = 100;

// ── INTERNAL ───────────────────────────
unsigned long buttonAPressTime = 0;
unsigned long lastImuTime      = 0;
unsigned long lastUiTime       = 0;
unsigned long panicFlashTimer  = 0;
bool panicColorRed = true;

// Pedometer
float filteredMag  = 1.0;
int   stepBuffer   = 0;
unsigned long lastPeakTime = 0;
bool isPeak = false;

// Posture
float currentPitch = 0, currentRoll = 0;
float basePitch    = 0, baseRoll    = 0;
unsigned long slouchStartTime = 0;

// Balance
bool  balanceTimerActive = false;
unsigned long balanceStartTime = 0;
float cumulativeTremor = 0.0;

// Animation
float pulsePhase   = 0.0;
int   animFrame    = 0;
unsigned long lastAnimTime = 0;

// ── COLORS ─────────────────────────────
#define C_BG        0x0861   // #080C12 deep space
#define C_CARD      0x10A2   // #101420
#define C_ACCENT    0x051F   // #0033FF neon blue
#define C_GREEN     0x07E6   // #00FF30 neon green
#define C_RED       0xF805   // #FF0828 neon red
#define C_ORANGE    0xFD20   // #FF6800 neon orange
#define C_CYAN      0x07FF   // #00FFFF
#define C_PURPLE    0x881F   // #8800FF
#define C_YELLOW    0xFFE0   // #FFFF00
#define C_DIM       0x4208   // #404040 dimmed

// ── WEB DASHBOARD ──────────────────────
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width,initial-scale=1">
<title>HealthOS</title>
<style>
  @import url('https://fonts.googleapis.com/css2?family=Inter:wght@300;400;600;700;800&display=swap');
  *{margin:0;padding:0;box-sizing:border-box}
  :root{
    --bg:#080c12;--card:rgba(255,255,255,0.04);--border:rgba(255,255,255,0.08);
    --green:#00ff41;--red:#ff0828;--blue:#0a84ff;--orange:#ff6b00;--cyan:#00e5ff;--purple:#bf5af2;
    --text:#f0f0f0;--dim:#666
  }
  body{font-family:'Inter',sans-serif;background:var(--bg);color:var(--text);min-height:100vh;padding:20px;overflow-x:hidden}
  body::before{content:'';position:fixed;top:0;left:0;right:0;bottom:0;
    background:radial-gradient(ellipse at 20% 20%,rgba(10,132,255,0.06) 0%,transparent 60%),
               radial-gradient(ellipse at 80% 80%,rgba(0,229,255,0.04) 0%,transparent 60%);
    pointer-events:none;z-index:0}

  .container{max-width:480px;margin:0 auto;position:relative;z-index:1}

  /* Header */
  header{display:flex;align-items:center;justify-content:space-between;margin-bottom:24px;padding:16px 20px;
    background:var(--card);border:1px solid var(--border);border-radius:18px;backdrop-filter:blur(20px)}
  .logo{display:flex;align-items:center;gap:10px}
  .logo-dot{width:10px;height:10px;border-radius:50%;background:var(--green);box-shadow:0 0 10px var(--green);animation:blink 2s infinite}
  @keyframes blink{0%,100%{opacity:1}50%{opacity:0.3}}
  .logo-text{font-size:1.1rem;font-weight:800;letter-spacing:1px;
    background:linear-gradient(135deg,#0a84ff,#00e5ff);-webkit-background-clip:text;-webkit-text-fill-color:transparent}
  #mode-chip{font-size:0.65rem;font-weight:700;letter-spacing:1.5px;padding:5px 12px;border-radius:100px;
    background:rgba(10,132,255,0.15);border:1px solid rgba(10,132,255,0.3);color:var(--blue);text-transform:uppercase}

  /* Panic Banner */
  #panic-banner{display:none;background:linear-gradient(135deg,#ff0828,#ff4500);
    border-radius:16px;padding:18px;text-align:center;font-weight:800;font-size:1.3rem;
    margin-bottom:20px;letter-spacing:2px;animation:panic-pulse 0.4s infinite alternate;
    box-shadow:0 0 40px rgba(255,8,40,0.5)}
  @keyframes panic-pulse{from{box-shadow:0 0 20px rgba(255,8,40,0.5)}to{box-shadow:0 0 60px rgba(255,8,40,0.9)}}

  /* Step Ring */
  .ring-card{background:var(--card);border:1px solid var(--border);border-radius:22px;
    padding:28px 20px;margin-bottom:16px;display:flex;align-items:center;gap:24px;backdrop-filter:blur(20px)}
  .ring-wrap{position:relative;flex-shrink:0}
  .ring-wrap svg{transform:rotate(-90deg)}
  .ring-bg{fill:none;stroke:rgba(255,255,255,0.06);stroke-width:8}
  .ring-fill{fill:none;stroke:url(#ringGrad);stroke-width:8;stroke-linecap:round;
    stroke-dasharray:283;transition:stroke-dashoffset 0.8s cubic-bezier(.4,0,.2,1)}
  .ring-center{position:absolute;inset:0;display:flex;flex-direction:column;align-items:center;justify-content:center}
  .ring-num{font-size:1.5rem;font-weight:800;color:var(--blue)}
  .ring-sub{font-size:0.55rem;font-weight:600;letter-spacing:1px;color:var(--dim);text-transform:uppercase}
  .ring-info .metric-label{font-size:0.65rem;font-weight:700;letter-spacing:1.5px;text-transform:uppercase;color:var(--dim);margin-bottom:4px}
  .ring-info .metric-val{font-size:1.4rem;font-weight:800;margin-bottom:14px}

  /* Grid */
  .grid{display:grid;grid-template-columns:1fr 1fr;gap:12px;margin-bottom:16px}
  .card{background:var(--card);border:1px solid var(--border);border-radius:18px;
    padding:18px 16px;backdrop-filter:blur(20px);position:relative;overflow:hidden;transition:transform 0.2s}
  .card::before{content:'';position:absolute;top:0;left:0;right:0;height:2px;opacity:0.6;border-radius:18px 18px 0 0}
  .card.green::before{background:linear-gradient(90deg,transparent,var(--green),transparent)}
  .card.red::before{background:linear-gradient(90deg,transparent,var(--red),transparent)}
  .card.blue::before{background:linear-gradient(90deg,transparent,var(--blue),transparent)}
  .card.orange::before{background:linear-gradient(90deg,transparent,var(--orange),transparent)}
  .card.full{grid-column:span 2}
  .c-label{font-size:0.6rem;font-weight:700;letter-spacing:1.5px;text-transform:uppercase;color:var(--dim);margin-bottom:8px}
  .c-val{font-size:1.8rem;font-weight:800;line-height:1}
  .c-val.green{color:var(--green);text-shadow:0 0 20px rgba(0,255,65,0.4)}
  .c-val.red{color:var(--red);text-shadow:0 0 20px rgba(255,8,40,0.4)}
  .c-val.blue{color:var(--blue);text-shadow:0 0 20px rgba(10,132,255,0.4)}
  .c-val.orange{color:var(--orange);text-shadow:0 0 20px rgba(255,107,0,0.4)}

  /* Battery bar */
  .batt-bar{height:6px;background:rgba(255,255,255,0.08);border-radius:3px;margin-top:8px;overflow:hidden}
  .batt-fill{height:100%;border-radius:3px;transition:width 1s ease,background 1s}

  /* Balance arc */
  .balance-wrap{display:flex;align-items:center;justify-content:space-between;gap:16px}
  .balance-arc{position:relative;width:80px;height:80px;flex-shrink:0}
  .balance-arc svg{transform:rotate(-90deg)}
  .arc-bg{fill:none;stroke:rgba(255,255,255,0.06);stroke-width:7}
  .arc-fill{fill:none;stroke-width:7;stroke-linecap:round;stroke-dasharray:188;transition:stroke-dashoffset 1s}
  .arc-text{position:absolute;inset:0;display:flex;align-items:center;justify-content:center;
    font-size:1rem;font-weight:800;color:var(--orange)}

  /* Footer */
  footer{text-align:center;font-size:0.65rem;color:var(--dim);margin-top:20px;letter-spacing:1px}

  /* Pulse dot */
  .pulse{display:inline-block;width:8px;height:8px;border-radius:50%;margin-right:6px;vertical-align:middle}
  .pulse.on{background:var(--green);box-shadow:0 0 8px var(--green);animation:blink 1.5s infinite}
  .pulse.off{background:var(--dim)}
</style>
</head>
<body>
<div class="container">
  <header>
    <div class="logo">
      <div class="logo-dot"></div>
      <span class="logo-text">HEALTHOS</span>
    </div>
    <div id="mode-chip">Connecting...</div>
  </header>

  <div id="panic-banner">🚨 &nbsp; SOS ALARM ACTIVE &nbsp; 🚨</div>

  <!-- Step Ring Card -->
  <div class="ring-card">
    <div class="ring-wrap">
      <svg width="90" height="90" viewBox="0 0 90 90">
        <defs>
          <linearGradient id="ringGrad" x1="0%" y1="0%" x2="100%" y2="100%">
            <stop offset="0%" stop-color="#0a84ff"/>
            <stop offset="100%" stop-color="#00e5ff"/>
          </linearGradient>
        </defs>
        <circle class="ring-bg" cx="45" cy="45" r="34"/>
        <circle class="ring-fill" id="step-ring" cx="45" cy="45" r="34" stroke-dashoffset="283"/>
      </svg>
      <div class="ring-center">
        <div class="ring-num" id="steps">0</div>
        <div class="ring-sub">steps</div>
      </div>
    </div>
    <div class="ring-info">
      <div class="metric-label">Daily Goal</div>
      <div class="metric-val" style="color:var(--blue)" id="step-pct">0%</div>
      <div class="metric-label">Target: 10,000</div>
    </div>
  </div>

  <!-- Grid -->
  <div class="grid">
    <div class="card green">
      <div class="c-label">Posture</div>
      <div class="c-val green" id="posture">GOOD</div>
    </div>
    <div class="card blue">
      <div class="c-label">Battery</div>
      <div class="c-val blue" id="batt">100%</div>
      <div class="batt-bar"><div class="batt-fill" id="batt-bar" style="width:100%;background:var(--green)"></div></div>
    </div>
    <div class="card orange full">
      <div class="balance-wrap">
        <div>
          <div class="c-label">Balance Score</div>
          <div class="c-val orange" id="balance-val">100%</div>
          <div style="font-size:0.7rem;color:var(--dim);margin-top:6px">Last Asana Session</div>
        </div>
        <div class="balance-arc">
          <svg width="80" height="80" viewBox="0 0 80 80">
            <circle class="arc-bg" cx="40" cy="40" r="30"/>
            <circle class="arc-fill" id="balance-arc" cx="40" cy="40" r="30"
              stroke="var(--orange)" stroke-dashoffset="0"/>
          </svg>
          <div class="arc-text" id="balance-pct">100</div>
        </div>
      </div>
    </div>
  </div>

  <footer>
    <span class="pulse on" id="conn-dot"></span>
    <span id="conn-text">LIVE · Updates every second</span>
  </footer>
</div>

<script>
const GOAL = 10000;
const modes = ["HOME DASHBOARD","POSTURE COACH","ASANA BALANCE","SLEEPING"];
let connected = true;

function updateRing(steps){
  const pct = Math.min(steps/GOAL,1);
  const offset = 283 - (283*pct);
  document.getElementById('step-ring').style.strokeDashoffset = offset;
  document.getElementById('step-pct').innerText = Math.round(pct*100)+'%';
}

function updateBalance(score){
  const offset = 188 - (188*(score/100));
  document.getElementById('balance-arc').style.strokeDashoffset = offset;
  document.getElementById('balance-pct').innerText = score;
  const c = score > 75 ? 'var(--green)' : score > 40 ? 'var(--orange)' : 'var(--red)';
  document.getElementById('balance-arc').style.stroke = c;
  document.getElementById('balance-val').style.color = c;
  document.getElementById('balance-pct').style.color = c;
}

function updateBatt(b){
  const bar = document.getElementById('batt-bar');
  bar.style.width = b+'%';
  bar.style.background = b>50?'var(--green)':b>20?'var(--orange)':'var(--red)';
  document.getElementById('batt').style.color = b>50?'var(--blue)':b>20?'var(--orange)':'var(--red)';
}

setInterval(()=>{
  fetch('/data').then(r=>r.json()).then(d=>{
    if(!connected){
      connected=true;
      document.getElementById('conn-dot').className='pulse on';
      document.getElementById('conn-text').innerText='LIVE · Updates every second';
    }
    document.getElementById('mode-chip').innerText = modes[d.mode]||'UNKNOWN';
    document.getElementById('panic-banner').style.display = d.panic ? 'block':'none';
    document.getElementById('steps').innerText = d.steps;
    updateRing(d.steps);

    const sl = d.slouch || d.mode===3;
    const postEl = document.getElementById('posture');
    if(d.mode===3){postEl.innerText='ASLEEP';postEl.className='c-val';postEl.style.color='var(--dim)'}
    else if(d.slouch){postEl.innerText='SLOUCH!';postEl.className='c-val red'}
    else{postEl.innerText='GOOD';postEl.className='c-val green'}

    document.getElementById('batt').innerText = d.batt+'%';
    updateBatt(d.batt);
    document.getElementById('balance-val').innerText = d.score+'%';
    updateBalance(d.score);
  }).catch(()=>{
    connected=false;
    document.getElementById('conn-dot').className='pulse off';
    document.getElementById('conn-text').innerText='WATCH SLEEPING · Wi-Fi off';
    document.getElementById('mode-chip').innerText='SLEEPING';
  });
},1000);
</script>
</body>
</html>
)rawliteral";

// ── WEB HANDLERS ───────────────────────
void handleRoot() { server.send(200, "text/html", index_html); }
void handleData() {
  String json = "{";
  json += "\"mode\":"  + String(currentApp) + ",";
  json += "\"steps\":" + String(stepCount)  + ",";
  json += "\"panic\":" + String(isPanicMode ? 1 : 0) + ",";
  json += "\"slouch\":" + String(isSlouching ? 1 : 0) + ",";
  json += "\"score\":" + String((int)stabilityScore) + ",";
  json += "\"batt\":"  + String(batteryLevel);
  json += "}";
  server.send(200, "application/json", json);
}

// ── CORE 0: WEBSERVER TASK ─────────────
void WebServerWorker(void * parameter) {
  WiFi.softAP(ap_ssid, ap_password);
  server.on("/", handleRoot);
  server.on("/data", handleData);
  server.begin();
  for(;;) { server.handleClient(); vTaskDelay(10 / portTICK_PERIOD_MS); }
}

// ── CORE 1: SENSOR LOOP ────────────────
void runBackgroundVitals() {
  unsigned long now = millis();
  if (now - lastImuTime < IMU_SAMPLE_RATE) return;
  lastImuTime = now;

  batteryLevel = M5.Power.getBatteryLevel();

  float ax, ay, az;
  M5.Imu.getAccel(&ax, &ay, &az);
  float mag = sqrt(ax*ax + ay*ay + az*az);
  filteredMag = (0.2 * mag) + (0.8 * filteredMag);

  currentPitch = atan2(-ax, sqrt(ay*ay + az*az)) * 180.0 / PI;
  currentRoll  = atan2(ay, az) * 180.0 / PI;

  if (currentApp != APP_SLEEP) {
    float delta = abs(filteredMag - 1.0);
    if (delta > STEP_THRESHOLD && !isPeak) {
      isPeak = true;
      unsigned long dt = now - lastPeakTime;
      if (dt > 300 && dt < 1200) {
        stepBuffer++;
        if (stepBuffer >= 4) {
          if (stepBuffer == 4) stepCount += 4; else stepCount++;
        }
      } else if (dt >= 1200) { stepBuffer = 1; }
      lastPeakTime = now;
    }
    if (abs(filteredMag - 1.0) < 0.1) isPeak = false;
  }

  if (currentApp == APP_POSTURE) {
    float dP = abs(currentPitch - basePitch);
    float dR = abs(currentRoll  - baseRoll);
    if (dP > SLOUCH_ANGLE || dR > SLOUCH_ANGLE) {
      if (!isSlouching) slouchStartTime = now;
      isSlouching = true;
      if (now - slouchStartTime > 3000) M5.Speaker.tone(4000, 50);
    } else { isSlouching = false; }
  }

  if (currentApp == APP_BALANCE && balanceTimerActive) {
    float t = abs(mag - filteredMag);
    cumulativeTremor += t;
    stabilityScore = 100.0 - (cumulativeTremor * 10.0);
    if (stabilityScore < 0) stabilityScore = 0;
  }
}

// ── HELPERS ────────────────────────────
// Draw a thin arc — used for battery/step indicators on device
void drawArc(M5Canvas &c, int cx, int cy, int r, int thickness,
             float startDeg, float endDeg, uint16_t color) {
  for (float a = startDeg; a <= endDeg; a += 1.5f) {
    float rad = a * PI / 180.0;
    int x1 = cx + (int)(cos(rad) * r);
    int y1 = cy + (int)(sin(rad) * r);
    int x2 = cx + (int)(cos(rad) * (r - thickness));
    int y2 = cy + (int)(sin(rad) * (r - thickness));
    c.drawLine(x1, y1, x2, y2, color);
  }
}

// ── STATUS BAR ─────────────────────────
const char* appNames[] = { "DASHBOARD", "POSTURE", "BALANCE", "SLEEP" };
const uint16_t appColors[] = { C_CYAN, C_ORANGE, C_PURPLE, 0x2945 };

void drawStatusBar(uint16_t accentColor) {
  canvas.fillRect(0, 0, 240, 20, 0x0000);
  canvas.drawFastHLine(0, 20, 240, accentColor);

  // App name
  canvas.setTextDatum(ML_DATUM);
  canvas.setTextColor(accentColor);
  canvas.setFont(&fonts::Font2);
  canvas.drawString(appNames[currentApp], 6, 10);

  // Battery icon
  int bx = 210, by = 4, bw = 22, bh = 12;
  canvas.drawRect(bx, by, bw, bh, C_DIM);
  canvas.fillRect(bx + bw, by + 3, 2, 6, C_DIM);
  int fill = (batteryLevel * (bw - 2)) / 100;
  uint16_t bc = batteryLevel > 50 ? C_GREEN : batteryLevel > 20 ? C_ORANGE : C_RED;
  canvas.fillRect(bx + 1, by + 1, fill, bh - 2, bc);

  // Step mini count
  canvas.setTextDatum(MR_DATUM);
  canvas.setTextColor(0x8410);
  canvas.drawString(String(stepCount), 205, 10);
}

// ── HOME SCREEN ────────────────────────
void drawHome() {
  drawStatusBar(C_CYAN);

  // Clock
  m5::rtc_time_t t;
  M5.Rtc.getTime(&t);
  char timeStr[6];
  sprintf(timeStr, "%02d:%02d", t.hours, t.minutes);

  canvas.setTextDatum(MC_DATUM);
  canvas.setFont(&fonts::FreeSansBold18pt7b);

  // Neon glow effect (draw twice with offset for glow)
  canvas.setTextColor(0x0219);  // dark cyan shadow
  canvas.drawString(timeStr, 121, 56);
  canvas.setTextColor(C_CYAN);
  canvas.drawString(timeStr, 120, 55);

  // Step arc ring (background)
  drawArc(canvas, 120, 55, 52, 4, 150, 390, C_DIM);
  // Step arc fill
  float stepPct = min((float)stepCount / 10000.0f, 1.0f);
  float endAngle = 150 + (stepPct * 240);
  if (endAngle > 150.1) drawArc(canvas, 120, 55, 52, 4, 150, endAngle, C_ACCENT);

  // Steps label
  canvas.setFont(&fonts::FreeSans9pt7b);
  canvas.setTextColor(C_DIM);
  canvas.drawString(String(stepCount) + " steps", 120, 90);

  // Bottom hint
  canvas.setFont(&fonts::Font2);
  canvas.setTextColor(0x4208);
  canvas.drawString("HOLD A: SOS    B: APPS", 120, 122);
}

// ── POSTURE SCREEN ─────────────────────
void drawPosture() {
  drawStatusBar(C_ORANGE);

  int cx = 120, cy = 72;

  // Target rings
  canvas.drawCircle(cx, cy, 30, C_DIM);
  canvas.drawCircle(cx, cy, 15, 0x2104);

  // Crosshairs
  canvas.drawFastHLine(cx - 30, cy, 60, 0x1082);
  canvas.drawFastVLine(cx, cy - 30, 60, 0x1082);

  // Bubble position
  float dx = (currentRoll  - baseRoll)  * 1.8;
  float dy = (currentPitch - basePitch) * 1.8;
  int bx = constrain((int)(cx + dx), cx - 28, cx + 28);
  int by = constrain((int)(cy + dy), cy - 28, cy + 28);

  float dist = sqrt(dx * dx + dy * dy);
  uint16_t bubbleColor;
  if (dist < 10)       bubbleColor = C_GREEN;
  else if (dist < 20)  bubbleColor = C_ORANGE;
  else                 bubbleColor = C_RED;

  // Bubble glow
  canvas.fillCircle(bx, by, 10, 0x0000);
  canvas.drawCircle(bx, by, 11, bubbleColor);
  canvas.fillCircle(bx, by, 9, bubbleColor);

  // Status text
  canvas.setFont(&fonts::Font2);
  canvas.setTextDatum(MC_DATUM);
  if (isSlouching) {
    canvas.setTextColor(C_RED);
    canvas.drawString("STRAIGHTEN UP!", 120, 115);
  } else {
    canvas.setTextColor(C_GREEN);
    canvas.drawString("POSTURE OK", 120, 115);
  }

  canvas.setTextColor(C_DIM);
  canvas.drawString("Tap A to recenter", 120, 128);
}

// ── BALANCE SCREEN ─────────────────────
void drawBalance() {
  drawStatusBar(C_PURPLE);

  canvas.setTextDatum(MC_DATUM);

  if (!balanceTimerActive) {
    // Score display with arc
    int score = (int)stabilityScore;
    float endA = 210 + ((score / 100.0) * 300);
    drawArc(canvas, 120, 72, 42, 6, 210, 510, C_DIM);
    if (score > 0) {
      uint16_t ac = score > 75 ? C_GREEN : score > 40 ? C_ORANGE : C_RED;
      drawArc(canvas, 120, 72, 42, 6, 210, min(endA, 510.0f), ac);
    }

    canvas.setFont(&fonts::FreeSansBold18pt7b);
    uint16_t sc = (int)stabilityScore > 75 ? C_GREEN : (int)stabilityScore > 40 ? C_ORANGE : C_RED;
    canvas.setTextColor(sc);
    canvas.drawString(String(score)+"%", 120, 75);

    canvas.setFont(&fonts::Font2);
    canvas.setTextColor(C_DIM);
    canvas.drawString("LAST SCORE", 120, 100);
    canvas.setTextColor(C_PURPLE);
    canvas.drawString("PRESS A TO START", 120, 120);
  } else {
    unsigned long elapsed = (millis() - balanceStartTime) / 1000;

    // Timer ring
    float ringPct = min(elapsed / 60.0f, 1.0f);
    drawArc(canvas, 120, 65, 38, 5, 270, 630, C_DIM);
    drawArc(canvas, 120, 65, 38, 5, 270, 270 + (ringPct * 360), C_PURPLE);

    canvas.setFont(&fonts::FreeSansBold18pt7b);
    canvas.setTextColor(WHITE);
    canvas.drawString(String(elapsed)+"s", 120, 65);

    uint16_t sc = (int)stabilityScore > 75 ? C_GREEN : (int)stabilityScore > 40 ? C_ORANGE : C_RED;
    canvas.setFont(&fonts::FreeSans9pt7b);
    canvas.setTextColor(sc);
    canvas.drawString("Stability: "+String((int)stabilityScore)+"%", 120, 95);

    canvas.setFont(&fonts::Font2);
    canvas.setTextColor(C_DIM);
    canvas.drawString("PRESS A TO STOP", 120, 118);
  }
}

// ── SLEEP SCREEN ───────────────────────
void drawSleep() {
  // Just stay black — screen brightness is 0 anyway
  // But we do pulse a tiny indicator so it looks alive
  pulsePhase += 0.15;
  int alpha = (int)(sin(pulsePhase) * 20 + 20);
  canvas.fillCircle(120, 67, 3, canvas.color565(0, alpha/2, alpha));
}

// ── PANIC SCREEN ───────────────────────
void drawPanic() {
  unsigned long m = millis();
  if (m - panicFlashTimer > 180) {
    panicFlashTimer = m;
    panicColorRed = !panicColorRed;
    M5.Speaker.tone(panicColorRed ? 2000 : 3000, 80);
  }
  canvas.fillSprite(panicColorRed ? C_RED : WHITE);
  canvas.setTextDatum(MC_DATUM);
  canvas.setTextColor(panicColorRed ? WHITE : C_RED);
  canvas.setFont(&fonts::FreeSansBold18pt7b);
  canvas.drawString("SOS", 120, 52);
  canvas.setFont(&fonts::FreeSans9pt7b);
  canvas.drawString("ALARM ACTIVE", 120, 82);
  canvas.setFont(&fonts::Font2);
  canvas.setTextColor(panicColorRed ? 0xFB00 : C_RED);
  canvas.drawString("HOLD A TO CANCEL", 120, 108);
}

// ── DRAW ───────────────────────────────
void drawScreen() {
  canvas.fillSprite(C_BG);

  if (isPanicMode) {
    drawPanic();
  } else {
    switch (currentApp) {
      case APP_HOME:    drawHome();    break;
      case APP_POSTURE: drawPosture(); break;
      case APP_BALANCE: drawBalance(); break;
      case APP_SLEEP:   drawSleep();   break;
    }
  }

  canvas.pushSprite(0, 0);
}

// ── SETUP ──────────────────────────────
void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  canvas.createSprite(240, 135);

  M5.Speaker.begin();
  M5.Speaker.setVolume(128);

  // Boot screen
  canvas.fillSprite(C_BG);
  canvas.setTextDatum(MC_DATUM);
  canvas.setFont(&fonts::FreeSansBold18pt7b);
  canvas.setTextColor(C_CYAN);
  canvas.drawString("HealthOS", 120, 50);
  canvas.setFont(&fonts::Font2);
  canvas.setTextColor(C_DIM);
  canvas.drawString("v2.0  Booting...", 120, 90);
  canvas.pushSprite(0, 0);
  delay(1200);

  m5::rtc_time_t ts;
  ts.hours = 12; ts.minutes = 0; ts.seconds = 0;
  M5.Rtc.setTime(&ts);

  xTaskCreatePinnedToCore(WebServerWorker, "Web", 4096, NULL, 1, &WebServerTaskHandle, 0);
}

// ── LOOP ───────────────────────────────
void loop() {
  M5.update();
  runBackgroundVitals();

  // Button B — cycle apps
  if (M5.BtnB.wasPressed() && !isPanicMode) {
    AppMode prev = currentApp;
    currentApp = static_cast<AppMode>((currentApp + 1) % 4);

    if (prev == APP_SLEEP && currentApp != APP_SLEEP) {
      M5.Lcd.setBrightness(128);
      setCpuFrequencyMhz(240);
      WiFi.softAP(ap_ssid, ap_password);
      M5.Speaker.tone(1500, 50);
    }
    if (currentApp == APP_SLEEP) {
      M5.Lcd.setBrightness(0);
      WiFi.mode(WIFI_OFF);
      setCpuFrequencyMhz(80);
    } else {
      if (currentApp != APP_BALANCE) balanceTimerActive = false;
      M5.Speaker.tone(1500, 50);
    }
  }

  // Button A — hold for SOS, tap for action
  if (M5.BtnA.wasPressed()) buttonAPressTime = millis();

  if (M5.BtnA.isPressed() && (millis() - buttonAPressTime > 3000)) {
    isPanicMode = !isPanicMode;
    buttonAPressTime = millis();
    if (!isPanicMode) M5.Speaker.end();
    if (isPanicMode && currentApp == APP_SLEEP) {
      M5.Lcd.setBrightness(128);
      setCpuFrequencyMhz(240);
      WiFi.softAP(ap_ssid, ap_password);
    }
  }

  if (M5.BtnA.wasReleased()) {
    if (!isPanicMode && (millis() - buttonAPressTime < 1000)) {
      if (currentApp == APP_BALANCE) {
        balanceTimerActive = !balanceTimerActive;
        if (balanceTimerActive) {
          balanceStartTime = millis();
          stabilityScore   = 100.0;
          cumulativeTremor = 0.0;
          M5.Speaker.tone(2000, 100);
        }
      } else if (currentApp == APP_POSTURE) {
        basePitch = currentPitch;
        baseRoll  = currentRoll;
        M5.Speaker.tone(1000, 100);
      }
    }
  }

  if (currentApp != APP_SLEEP && (millis() - lastUiTime > UI_UPDATE_RATE)) {
    lastUiTime = millis();
    drawScreen();
  }
}
