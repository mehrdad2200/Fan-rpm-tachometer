/*
  fan_rpm_pro  —  تاکومتر پیشرفته فن با ESP32-S3 + ماژول TCRT5000  (نسخه 2.0)
  ==========================================================================
  سیم‌کشی:
    VCC -> 3V3 | GND -> GND (GND منبع فن هم مشترک) | D0 -> GPIO 4
    فن را فقط از منبع جدا تغذیه کن. روی یکی از پره‌ها/هاب یک نوار بازتابنده بچسبان.
    اختیاری: LED_PIN (چشمک با هر پالس) و BUZZER_PIN (بیزر هشدار) را پایین تنظیم کن.

  Arduino IDE:  Board: "ESP32S3 Dev Module"  |  پوشه‌ی اسکچ باید fan_rpm_pro باشد
  (همه‌ی کتابخانه‌ها جزو هسته‌ی ESP32 هستند؛ چیزی نصب نکن.)

  فهرست قابلیت‌ها
  ---------------
  اندازه‌گیری:
   [1] RPM لحظه‌ای (از فاصله‌ی پالس‌ها)   [2] دور بر ثانیه Hz لحظه‌ای   [3] تعداد دور در آخرین ثانیه
   [4] پالس خام در ثانیه   [5] میانگین ۲ ثانیه   [6] میانگین ۱۰ ثانیه   [7] میانگین ۱ دقیقه
   [8] بیشینه از روشن شدن   [9] بیشینه تاریخی (ماندگار)   [10] کمینه در حال چرخش   [11] میانگین نوبت
   [12] شتاب RPM/s   [13] پایداری %   [14] فاصله‌ی پالس‌ها   [15] تشخیص ایستادن/چرخیدن
   [16] شمارش نوبت‌های چرخش   [17] دور نوبت   [18] مدت نوبت   [19] زمان کارکرد کل   [20] مجموع دور
   [21] دور امروز   [22] دور این ساعت   [23] دور ۶۰ ثانیه   [24] تاریخچه‌ی ثانیه‌ای ۵ دقیقه (بدون نیاز به اینترنت)
   [25] آمار دقیقه   [26] آمار ساعت   [27] آمار روز   [28] آمار ماه   [29] ضریب کالیبراسیون
   [30] پالس در هر دور   [31] تعداد پره + فرکانس عبور پره   [32] سرعت نوک پره m/s   [33] سرعت نوک پره km/h
   [34] واحد rad/s   [35] واحد deg/s   [36] واحد Hz   [37] تغییر واحد نمایش
  تست زمان‌دار:
   [38] تست بر اساس مدت   [39] تست تا رسیدن به N دور   [40] نوار پیشرفت زنده   [41] نام‌گذاری تست
   [42] تاریخچه‌ی ۲۰ تست (ماندگار)   [43] نمایش آخرین نتیجه   [44] پاک کردن تاریخچه   [45] خروجی CSV تست‌ها
   [46] توقف دستی تست
  هشدار و حفاظت:
   [47] هشدار RPM بالا   [48] هشدار RPM پایین   [49] هشدار توقف ناگهانی   [50] هشدار نویز   [51] بیزر دستگاه
   [52] بوق مرورگر   [53] بی‌صدا کردن هشدار   [54] LED پالس   [55] قطع خودکار وقفه هنگام طوفان نویز
   [56] شمارنده‌ی پالس‌های ردشده   [57] تشخیص ریست بر اثر افت ولتاژ (Brownout)   [58] دیبانس قابل تنظیم
  داده:
   [59] CSV ساعت   [60] CSV دقیقه   [61] CSV نمونه‌های ثانیه‌ای   [62] خروجی JSON   [63] پشتیبان باینری
   [64] ریست رکوردها   [65] پاک کردن تست‌ها   [66] پاک کردن همه   [67] ذخیره‌ی فوری   [68] ذخیره‌ی خودکار
   [69] تنظیمات ماندگار   [70] انتخاب منطقه‌ی زمانی   [71] بازگشت به تنظیمات کارخانه
  شبکه و سیستم:
   [72] mDNS   [73] به‌روزرسانی OTA   [74] رمز عبور برای عملیات حساس   [75] هات‌اسپات جایگزین   [76] CORS برای API
   [77] REST API کامل   [78] تشخیص دستگاه   [79] حافظه‌ی آزاد   [80] مصرف فلش   [81] دمای چیپ   [82] RSSI
   [83] مدل چیپ/CPU/MAC/نسخه   [84] ری‌استارت از وب   [85] لاگ سریال   [86] هشدار همگام‌نبودن ساعت
  رابط کاربری:
   [87] گیج آنالوگ   [88] نمودار کوچک   [89] فارسی/انگلیسی   [90] شمسی/میلادی   [91] تم تیره/روشن
   [92] حالت نمایش بزرگ   [93] تمام‌صفحه   [94] نمودار ستونی/خطی   [95] ثابت کردن نمودار   [96] انتخاب تعداد نقاط
   [97] تولتیپ لمسی/ماوس   [98] آمار بازه (جمع/میانگین/بیشینه/کمینه)   [99] انیمیشن نرم   [100] RPM در عنوان تب
   [101] میانبر کیبورد   [102] نرخ به‌روزرسانی قابل انتخاب   [103] چشمک با هر پالس   [104] نمای چاپ
   [105] ریسپانسیو   [106] نشانگر اتصال   [107] مدت روشن بودن دستگاه   [108] بنر هشدارها
*/

#include <WiFi.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <LittleFS.h>
#include <Preferences.h>
#include <ArduinoOTA.h>
#include <esp_system.h>
#include <time.h>

// ================= تنظیمات ثابت =================
const char* WIFI_SSID = "YOUR_WIFI_NAME";       // اسم مودم / your Wi-Fi name
const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";   // رمز مودم / your Wi-Fi password
const char* HOSTNAME  = "fan-counter";          // http://fan-counter.local
const char* DEFAULT_TZ = "CET-1CEST,M3.5.0,M10.5.0/3";   // ایران: "<+0330>-3:30"
const char* FW_VERSION = "2.0";

const int SENSOR_PIN = 4;     // D0 ماژول
const int LED_PIN    = -1;    // مثلاً 2 ؛ -1 = غیرفعال
const int BUZZER_PIN = -1;    // مثلاً 5 ؛ -1 = غیرفعال
const uint32_t SAVE_EVERY_MS = 5UL * 60UL * 1000UL;
const uint32_t NOISE_LIMIT   = 20000;   // بیش از این تعداد پالس ردشده در ثانیه = طوفان نویز
// =================================================

constexpr int MIN_N    = 1440;
constexpr int HOUR_N   = 24 * 366;
constexpr int RING_N   = 300;     // ۳۰۰ ثانیه‌ی اخیر
constexpr int TEST_MAX = 20;

uint32_t minTag[MIN_N];   uint32_t minCnt[MIN_N];
uint32_t hourTag[HOUR_N]; uint32_t hourCnt[HOUR_N];
uint32_t ppsRing[RING_N]; uint32_t sampleN = 0;

uint32_t totalCount = 0;      // مجموع پالس‌ها
uint32_t runtimeSec = 0;
uint32_t sessions   = 0;
float    peakAll    = 0;
bool     dirty = false;
uint32_t lastSave = 0;

// ---- تنظیمات ----
struct Settings {
  uint16_t ppr = 1;
  uint16_t blades = 0;
  float    radiusMm = 0;
  float    calib = 1.0f;
  uint32_t debounce = 300;
  uint16_t stopSec = 3;
  uint32_t rpmHigh = 0, rpmLow = 0;
  bool     buzzer = true, serialLog = false, alStall = true;
  char     tz[48];
  char     pass[24];
} S;
Preferences prefs;

// ---- وقفه ----
volatile uint32_t pending = 0, lastIsrUs = 0, periodUs = 0, rejected = 0, debounceUs = 300;
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
bool isrAttached = false;

// ---- وضعیت چرخش ----
bool     everPulsed = false;
uint32_t lastPulseMs = 0;
bool     wasRunning = false;
uint32_t sessStartMs = 0, sessStartTotal = 0;
float    sessPeak = 0, peakSession = 0, minSession = 0;
double   lastSessRevs = 0, lastSessDur = 0; float lastSessPeak = 0;
uint32_t lastSampleTotal = 0, nextTick = 0;
uint32_t prevRej = 0, noiseUntil = 0, noiseEvents = 0, lastNoiseMs = 0;
float    rejPerSec = 0;
bool     stallLatched = false, silenced = false;
bool     alHigh = false, alLow = false, alNoise = false;
uint32_t ledOffMs = 0;

// ---- تست زمان‌دار ----
struct TestRec { uint32_t ts; uint32_t durMs; uint32_t pulses; uint8_t mode; char name[24]; };
TestRec  recs[TEST_MAX]; uint8_t recN = 0; uint32_t testSerial = 0;
bool     tActive = false; uint8_t tMode = 0;
uint32_t tStartMs = 0, tDurMs = 0, tTargetPulses = 0, tStartTotal = 0;
char     tName[24] = "";

WebServer server(80);
const uint32_t MAGIC = 0x50434E56;
struct Meta { uint32_t magic, total, runtimeSec, sessions; float peakAll; uint32_t reserved; };

// ---------- وقفه سنسور ----------
void IRAM_ATTR onPass() {
  uint32_t n = (uint32_t)esp_timer_get_time();
  uint32_t d = n - lastIsrUs;
  if (d >= debounceUs) { periodUs = d; lastIsrUs = n; pending++; }
  else rejected++;
}

// ---------- ابزارها ----------
bool timeOk() { return time(nullptr) > 1700000000; }
double rv(uint32_t p) { return (double)p * S.calib / (double)S.ppr; }
float rpmFromPps(uint32_t p) { return (float)p * 60.0f * S.calib / (float)S.ppr; }

uint32_t minGet(uint32_t m)  { uint32_t i = m % MIN_N;  return minTag[i]  == m ? minCnt[i]  : 0; }
uint32_t hourGet(uint32_t h) { uint32_t i = h % HOUR_N; return hourTag[i] == h ? hourCnt[i] : 0; }

void bump(uint32_t* tag, uint32_t* cnt, int size, uint32_t key, uint32_t n) {
  uint32_t i = key % size;
  if (tag[i] != key) { tag[i] = key; cnt[i] = 0; }
  cnt[i] += n;
}

void recordPasses(uint32_t n) {
  totalCount += n;
  dirty = true;
  if (!timeOk()) return;
  uint32_t now = (uint32_t)time(nullptr);
  bump(minTag, minCnt, MIN_N, now / 60, n);
  bump(hourTag, hourCnt, HOUR_N, now / 3600, n);
}

uint32_t sumHours(time_t s, time_t e) {
  uint32_t sum = 0;
  for (uint32_t h = s / 3600; h <= (uint32_t)((e - 1) / 3600); h++) sum += hourGet(h);
  return sum;
}

void rangeOf(bool month, int back, time_t& s, time_t& e) {
  time_t now = time(nullptr);
  tm lt; localtime_r(&now, &lt);
  lt.tm_hour = 0; lt.tm_min = 0; lt.tm_sec = 0;
  tm a = lt, b = lt;
  if (month) {
    a.tm_mday = 1; b.tm_mday = 1;
    a.tm_mon = lt.tm_mon - back;
    b.tm_mon = lt.tm_mon - back + 1;
  } else {
    a.tm_mday = lt.tm_mday - back;
    b.tm_mday = lt.tm_mday - back + 1;
  }
  a.tm_isdst = -1; b.tm_isdst = -1;
  s = mktime(&a); e = mktime(&b);
}

// حلقه‌ی ۳۰۰ ثانیه‌ای: back=0 یعنی آخرین ثانیه‌ی کامل
uint32_t ringBack(uint32_t back) {
  if (sampleN <= back) return 0;
  return ppsRing[(sampleN - 1 - back) % RING_N];
}
float avgRpm(uint32_t n) {
  uint32_t sum = 0;
  for (uint32_t i = 0; i < n; i++) sum += ringBack(i);
  return rpmFromPps(sum) / (float)n;
}

bool isRunning() { return everPulsed && (millis() - lastPulseMs) < (uint32_t)S.stopSec * 1000UL; }

float instRpm() {
  if (!isRunning()) return 0;
  uint32_t p;
  portENTER_CRITICAL(&mux); p = periodUs; portEXIT_CRITICAL(&mux);
  if (p == 0) return 0;
  return 60000000.0f / ((float)p * (float)S.ppr) * S.calib;
}

float stability() {
  if (!isRunning()) return 0;
  double sum = 0, sq = 0; const int N = 10;
  for (int i = 0; i < N; i++) { double v = ringBack(i); sum += v; sq += v * v; }
  double mean = sum / N;
  if (mean <= 0) return 0;
  double var = sq / N - mean * mean; if (var < 0) var = 0;
  double cv = sqrt(var) / mean;
  double st = 100.0 - cv * 100.0;
  return st < 0 ? 0 : (float)st;
}

float accel() { return (rpmFromPps(ringBack(0)) - rpmFromPps(ringBack(3))) / 3.0f; }

void curSession(double& revs, double& dur, float& pk) {
  if (isRunning()) {
    revs = totalCount >= sessStartTotal ? rv(totalCount - sessStartTotal) : 0;
    dur = (millis() - sessStartMs) / 1000.0; pk = sessPeak;
  } else { revs = lastSessRevs; dur = lastSessDur; pk = lastSessPeak; }
}

void utf8Trim(char* s) {
  int len = strlen(s); if (len == 0) return;
  int i = len - 1;
  while (i > 0 && ((uint8_t)s[i] & 0xC0) == 0x80) i--;
  uint8_t lead = (uint8_t)s[i];
  int need = lead >= 0xF0 ? 4 : lead >= 0xE0 ? 3 : lead >= 0xC0 ? 2 : 1;
  if (len - i < need) s[i] = 0;
}

// ---------- ذخیره/بازیابی ----------
void saveData() {
  File f = LittleFS.open("/d.bin", "w");
  if (!f) return;
  Meta m{MAGIC, totalCount, runtimeSec, sessions, peakAll, 0};
  f.write((uint8_t*)&m, sizeof m);
  f.write((uint8_t*)minTag, sizeof(minTag));
  f.write((uint8_t*)minCnt, sizeof(minCnt));
  f.write((uint8_t*)hourTag, sizeof(hourTag));
  f.write((uint8_t*)hourCnt, sizeof(hourCnt));
  f.close();
  dirty = false;
}

void loadData() {
  File f = LittleFS.open("/d.bin", "r");
  if (!f) return;
  Meta m;
  if (f.read((uint8_t*)&m, sizeof m) != sizeof m || m.magic != MAGIC) { f.close(); return; }
  totalCount = m.total; runtimeSec = m.runtimeSec; sessions = m.sessions; peakAll = m.peakAll;
  f.read((uint8_t*)minTag, sizeof(minTag));
  f.read((uint8_t*)minCnt, sizeof(minCnt));
  f.read((uint8_t*)hourTag, sizeof(hourTag));
  f.read((uint8_t*)hourCnt, sizeof(hourCnt));
  f.close();
}

void saveTests() {
  File f = LittleFS.open("/t.bin", "w");
  if (!f) return;
  f.write(&recN, 1);
  f.write((uint8_t*)recs, sizeof(recs));
  f.close();
}
void loadTests() {
  File f = LittleFS.open("/t.bin", "r");
  if (!f) return;
  uint8_t n = 0; f.read(&n, 1);
  if (n > TEST_MAX) n = 0;
  if (f.read((uint8_t*)recs, sizeof(recs)) == sizeof(recs)) recN = n;
  f.close();
}

void loadSettings() {
  prefs.begin("fan", false);
  S.ppr = prefs.getUShort("ppr", 1); if (S.ppr < 1) S.ppr = 1;
  S.blades = prefs.getUShort("bl", 0);
  S.radiusMm = prefs.getFloat("rad", 0);
  S.calib = prefs.getFloat("cal", 1.0f); if (S.calib <= 0) S.calib = 1.0f;
  S.debounce = prefs.getUInt("deb", 300);
  S.stopSec = prefs.getUShort("stp", 3); if (S.stopSec < 1) S.stopSec = 3;
  S.rpmHigh = prefs.getUInt("hi", 0);
  S.rpmLow = prefs.getUInt("lo", 0);
  S.buzzer = prefs.getBool("buz", true);
  S.serialLog = prefs.getBool("ser", false);
  S.alStall = prefs.getBool("stl", true);
  String tz = prefs.getString("tz", DEFAULT_TZ); strlcpy(S.tz, tz.c_str(), sizeof S.tz);
  String pw = prefs.getString("pw", "");         strlcpy(S.pass, pw.c_str(), sizeof S.pass);
  prefs.end();
  debounceUs = S.debounce;
}
void saveSettings() {
  prefs.begin("fan", false);
  prefs.putUShort("ppr", S.ppr); prefs.putUShort("bl", S.blades);
  prefs.putFloat("rad", S.radiusMm); prefs.putFloat("cal", S.calib);
  prefs.putUInt("deb", S.debounce); prefs.putUShort("stp", S.stopSec);
  prefs.putUInt("hi", S.rpmHigh); prefs.putUInt("lo", S.rpmLow);
  prefs.putBool("buz", S.buzzer); prefs.putBool("ser", S.serialLog); prefs.putBool("stl", S.alStall);
  prefs.putString("tz", S.tz); prefs.putString("pw", S.pass);
  prefs.end();
}

// ---------- JSON ----------
String jsonEsc(const char* s) {
  String o;
  for (; *s; s++) {
    char c = *s;
    if (c == '"' || c == '\\') { o += '\\'; o += c; }
    else if ((uint8_t)c < 32) o += ' ';
    else o += c;
  }
  return o;
}
struct JsonB {
  String s = "{"; bool first = true;
  void k(const char* key) { if (!first) s += ','; first = false; s += '"'; s += key; s += "\":"; }
  void f(const char* key, double v, int d = 2) { k(key); if (!isfinite(v)) v = 0; s += String(v, d); }
  void u(const char* key, unsigned long v) { k(key); s += String(v); }
  void b(const char* key, bool v) { k(key); s += v ? "true" : "false"; }
  void t(const char* key, const char* v) { k(key); s += '"'; s += jsonEsc(v); s += '"'; }
  String done() { return s + "}"; }
};
void sendJson(const String& s) {
  server.sendHeader("Cache-Control", "no-store");
  server.sendHeader("Access-Control-Allow-Origin", "*");
  server.send(200, "application/json", s);
}
bool authOk() {
  if (!S.pass[0]) return true;
  if (server.authenticate("admin", S.pass)) return true;
  server.requestAuthentication();
  return false;
}

// ---------- تست زمان‌دار ----------
void finishTest(uint32_t elapsed) {
  TestRec r{};
  r.ts = timeOk() ? (uint32_t)time(nullptr) : 0;
  r.durMs = elapsed;
  r.pulses = totalCount >= tStartTotal ? totalCount - tStartTotal : 0;
  r.mode = tMode;
  strlcpy(r.name, tName, sizeof r.name);
  int top = recN < TEST_MAX ? recN : TEST_MAX - 1;
  for (int i = top; i > 0; i--) recs[i] = recs[i - 1];
  recs[0] = r;
  if (recN < TEST_MAX) recN++;
  testSerial++;
  tActive = false;
  saveTests();
}
void testTick() {
  if (!tActive) return;
  if (totalCount < tStartTotal) { tActive = false; return; }
  uint32_t el = millis() - tStartMs;
  uint32_t p = totalCount - tStartTotal;
  if (tMode == 0 && el >= tDurMs) finishTest(tDurMs);
  else if (tMode == 1 && p >= tTargetPulses) finishTest(el);
}

// ---------- API ----------
void apiLive() {
  bool ok = timeOk();
  uint32_t nowE = ok ? (uint32_t)time(nullptr) : 0;
  bool run = isRunning();
  uint32_t today = 0, hour = 0;
  if (ok) { time_t s, e; rangeOf(false, 0, s, e); today = sumHours(s, e); hour = hourGet(nowE / 3600); }
  uint32_t m60 = 0; for (int i = 0; i < 60; i++) m60 += ringBack(i);
  float rpm = instRpm();
  double sRev, sDur; float sPk; curSession(sRev, sDur, sPk);
  uint32_t per = 0; portENTER_CRITICAL(&mux); per = periodUs; portEXIT_CRITICAL(&mux);
  bool ap = WiFi.getMode() == WIFI_AP;
  IPAddress ip = ap ? WiFi.softAPIP() : WiFi.localIP();

  JsonB j;
  j.u("now", ok ? nowE : millis() / 1000); j.b("sync", ok); j.b("run", run);
  j.u("pps", ringBack(0)); j.f("rps", rv(ringBack(0)), 2); j.f("hz", rpm / 60.0, 2); j.f("rpm", rpm, 1);
  j.f("r2", avgRpm(2), 1); j.f("r10", avgRpm(10), 1); j.f("r60", avgRpm(60), 1);
  j.f("pkS", peakSession, 1); j.f("pkA", peakAll, 1); j.f("mnS", minSession, 1);
  j.f("avS", sDur > 0 ? sRev / sDur * 60.0 : 0, 1);
  j.f("acc", accel(), 1); j.f("stab", stability(), 0); j.f("per", run ? per / 1000.0 : 0, 3);
  j.f("tot", rv(totalCount), 2); j.f("tod", rv(today), 2); j.f("hr", rv(hour), 2); j.f("mn60", rv(m60), 2);
  j.u("rt", runtimeSec); j.u("ses", sessions); j.f("sRev", sRev, 2); j.f("sDur", sDur, 1); j.f("sPk", sPk, 1);
  j.f("rej", rejPerSec, 0); j.u("ne", noiseEvents);
  j.b("alH", alHigh); j.b("alL", alLow); j.b("alS", stallLatched); j.b("alN", alNoise); j.b("sil", silenced);
  j.b("ta", tActive); j.u("tmode", tMode); j.u("tel", tActive ? millis() - tStartMs : 0); j.u("tdur", tDurMs);
  j.f("tp", tActive && totalCount >= tStartTotal ? rv(totalCount - tStartTotal) : 0, 2);
  j.f("tT", rv(tTargetPulses), 2); j.t("tname", tName); j.u("tser", testSerial);
  j.t("ip", ip.toString().c_str()); j.u("rssi", 0); // مقدار واقعی در /api/sys
  j.u("up", millis() / 1000); j.b("ap", ap);
  sendJson(j.done());
}

void apiSeries() {
  String r = server.arg("res");
  bool ok = timeOk();
  uint32_t nowE = ok ? (uint32_t)time(nullptr) : 0;
  bool ring = (r == "rpm" || r == "second");
  bool up = ring && !ok;
  String o; o.reserve(3800);
  o += "{\"res\":\""; o += r; o += "\",\"synced\":"; o += ok ? "true" : "false";
  o += ",\"clock\":\""; o += up ? "up" : "epoch"; o += "\",\"now\":";
  o += String((unsigned long)(up ? millis() / 1000 : nowE)); o += ",\"data\":[";
  bool first = true;
  auto addD = [&](uint32_t t, double v, int d) {
    if (!first) o += ',';
    first = false;
    o += '['; o += String((unsigned long)t); o += ','; o += String(v, d); o += ']';
  };

  if (ring) {
    int def = r == "rpm" ? 120 : 60;
    int n = server.hasArg("n") ? server.arg("n").toInt() : def;
    n = constrain(n, 5, RING_N);
    uint32_t c = sampleN < (uint32_t)n ? sampleN : (uint32_t)n;
    uint32_t tNow = up ? millis() / 1000 : nowE;
    for (int i = (int)c - 1; i >= 0; i--) {
      uint32_t p = ringBack(i);
      if (r == "rpm") addD(tNow - i, rpmFromPps(p), 1); else addD(tNow - i, rv(p), 2);
    }
  } else if (!ok) {
    // ساعت هنوز همگام نشده
  } else if (r == "minute") {
    for (int i = 59; i >= 0; i--) { uint32_t m = nowE / 60 - i; addD(m * 60, rv(minGet(m)), 2); }
  } else if (r == "hour") {
    for (int i = 23; i >= 0; i--) { uint32_t h = nowE / 3600 - i; addD(h * 3600, rv(hourGet(h)), 2); }
  } else if (r == "day") {
    for (int i = 29; i >= 0; i--) { time_t s, e; rangeOf(false, i, s, e); addD(s + 3600, rv(sumHours(s, e)), 2); }
  } else if (r == "month") {
    for (int i = 11; i >= 0; i--) { time_t s, e; rangeOf(true, i, s, e); addD(s + 3600 * 24 * 3, rv(sumHours(s, e)), 2); }
  }
  o += "]}";
  sendJson(o);
}

void apiSys() {
  JsonB j;
  j.u("heap", ESP.getFreeHeap()); j.u("heapT", ESP.getHeapSize());
  j.u("fsU", LittleFS.usedBytes()); j.u("fsT", LittleFS.totalBytes());
  j.f("temp", temperatureRead(), 1);
  bool ap = WiFi.getMode() == WIFI_AP;
  j.u("rssi", 0); j.f("rssiV", ap ? 0 : WiFi.RSSI(), 0);
  j.t("ssid", ap ? "AP" : WiFi.SSID().c_str());
  j.t("mac", WiFi.macAddress().c_str());
  j.t("chip", ESP.getChipModel()); j.u("cpu", ESP.getCpuFreqMHz());
  j.t("fw", FW_VERSION); j.u("sketch", ESP.getSketchSize());
  j.u("rr", (unsigned long)esp_reset_reason());
  j.u("rejT", rejected); j.u("ne", noiseEvents);
  j.b("pw", S.pass[0] != 0);
  sendJson(j.done());
}

void apiSettingsGet() {
  JsonB j;
  j.u("ppr", S.ppr); j.u("blades", S.blades); j.f("radius", S.radiusMm, 1); j.f("calib", S.calib, 3);
  j.u("deb", S.debounce); j.u("stop", S.stopSec); j.u("high", S.rpmHigh); j.u("low", S.rpmLow);
  j.b("buz", S.buzzer); j.b("ser", S.serialLog); j.b("stl", S.alStall);
  j.t("tz", S.tz); j.b("pw", S.pass[0] != 0);
  sendJson(j.done());
}

void apiSettingsPost() {
  if (!authOk()) return;
  auto A = [&](const char* k) { return server.hasArg(k); };
  if (A("ppr"))    S.ppr = constrain(server.arg("ppr").toInt(), 1, 64);
  if (A("blades")) S.blades = constrain(server.arg("blades").toInt(), 0, 200);
  if (A("radius")) S.radiusMm = constrain(server.arg("radius").toFloat(), 0.0f, 2000.0f);
  if (A("calib"))  S.calib = constrain(server.arg("calib").toFloat(), 0.1f, 10.0f);
  if (A("deb"))    S.debounce = constrain(server.arg("deb").toInt(), 20, 100000);
  if (A("stop"))   S.stopSec = constrain(server.arg("stop").toInt(), 1, 60);
  if (A("high"))   S.rpmHigh = constrain(server.arg("high").toInt(), 0, 1000000);
  if (A("low"))    S.rpmLow = constrain(server.arg("low").toInt(), 0, 1000000);
  if (A("buz"))    S.buzzer = server.arg("buz") == "1";
  if (A("ser"))    S.serialLog = server.arg("ser") == "1";
  if (A("stl"))    S.alStall = server.arg("stl") == "1";
  if (A("tz")) {
    String z = server.arg("tz");
    if (z.length() > 0 && z.length() < sizeof S.tz) { strlcpy(S.tz, z.c_str(), sizeof S.tz); setenv("TZ", S.tz, 1); tzset(); }
  }
  if (A("newpass")) {
    String p = server.arg("newpass");
    if (p == "-") S.pass[0] = 0;
    else if (p.length() > 0 && p.length() < sizeof S.pass) strlcpy(S.pass, p.c_str(), sizeof S.pass);
  }
  debounceUs = S.debounce;
  saveSettings();
  sendJson("{\"ok\":true}");
}

void apiTests() {
  String o = "[";
  for (int i = 0; i < recN; i++) {
    if (i) o += ',';
    double revs = rv(recs[i].pulses), sec = recs[i].durMs / 1000.0;
    JsonB j;
    j.u("ts", recs[i].ts); j.t("name", recs[i].name); j.u("mode", recs[i].mode);
    j.f("dur", sec, 2); j.f("revs", revs, 2);
    j.f("rpm", sec > 0 ? revs / sec * 60.0 : 0, 1); j.f("hz", sec > 0 ? revs / sec : 0, 2);
    o += j.done();
  }
  o += "]";
  sendJson(o);
}

void apiTestStart() {
  if (!authOk()) return;
  double v = server.arg("value").toFloat();
  String mode = server.arg("mode");
  if (v <= 0) { server.send(400, "application/json", "{\"ok\":false}"); return; }
  strlcpy(tName, server.arg("name").c_str(), sizeof tName); utf8Trim(tName);
  tStartTotal = totalCount; tStartMs = millis();
  if (mode == "revs") {
    tMode = 1; tDurMs = 0;
    tTargetPulses = (uint32_t)ceil(constrain(v, 1.0, 10000000.0) * S.ppr / S.calib);
  } else {
    tMode = 0; tTargetPulses = 0;
    tDurMs = (uint32_t)(constrain(v, 0.5, 86400.0) * 1000.0);
  }
  tActive = true;
  sendJson("{\"ok\":true}");
}
void apiTestStop() {
  if (!authOk()) return;
  if (tActive) finishTest(millis() - tStartMs);
  sendJson("{\"ok\":true}");
}

void apiReset() {
  if (!authOk()) return;
  String w = server.arg("what");
  if (w == "peaks") { peakAll = 0; peakSession = 0; minSession = 0; dirty = true; }
  else if (w == "tests") { recN = 0; memset(recs, 0, sizeof recs); saveTests(); }
  else {   // all
    memset(minTag, 0, sizeof minTag);  memset(minCnt, 0, sizeof minCnt);
    memset(hourTag, 0, sizeof hourTag); memset(hourCnt, 0, sizeof hourCnt);
    memset(ppsRing, 0, sizeof ppsRing);
    totalCount = 0; runtimeSec = 0; sessions = 0; peakAll = 0; peakSession = 0; minSession = 0;
    sessStartTotal = 0; lastSampleTotal = 0; lastSessRevs = 0; lastSessDur = 0; lastSessPeak = 0; tActive = false;
    saveData();
  }
  sendJson("{\"ok\":true}");
}
void apiAck() { silenced = true; stallLatched = false; sendJson("{\"ok\":true}"); }
void apiSave() { if (!authOk()) return; saveData(); saveTests(); sendJson("{\"ok\":true}"); }
void apiReboot() { if (!authOk()) return; sendJson("{\"ok\":true}"); delay(300); saveData(); ESP.restart(); }
void apiFactory() {
  if (!authOk()) return;
  prefs.begin("fan", false); prefs.clear(); prefs.end();
  LittleFS.remove("/d.bin"); LittleFS.remove("/t.bin");
  sendJson("{\"ok\":true}"); delay(300); ESP.restart();
}

void csvBegin(const char* name) {
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.sendHeader("Content-Disposition", String("attachment; filename=") + name);
  server.send(200, "text/csv; charset=utf-8", "");
}
void fmtTime(time_t t, char* buf, size_t n) { tm lt; localtime_r(&t, &lt); strftime(buf, n, "%Y-%m-%d %H:%M:%S", &lt); }

void apiExport() {
  String w = server.arg("what");
  char tb[24]; String c;
  if (w == "bin") {
    saveData();
    File f = LittleFS.open("/d.bin", "r");
    if (!f) { server.send(404, "text/plain", "no data"); return; }
    server.sendHeader("Content-Disposition", "attachment; filename=fan_backup.bin");
    server.streamFile(f, "application/octet-stream"); f.close(); return;
  }
  if (w == "json") {
    JsonB j;
    j.f("total_revs", rv(totalCount), 2); j.u("runtime_s", runtimeSec); j.u("sessions", sessions);
    j.f("peak_rpm", peakAll, 1); j.u("ppr", S.ppr); j.f("calib", S.calib, 3);
    String o = j.done(); o.remove(o.length() - 1);
    o += ",\"tests\":[";
    for (int i = 0; i < recN; i++) {
      if (i) o += ',';
      double revs = rv(recs[i].pulses), sec = recs[i].durMs / 1000.0;
      o += "{\"name\":\"" + jsonEsc(recs[i].name) + "\",\"ts\":" + String(recs[i].ts) + ",\"seconds\":" + String(sec, 2) +
           ",\"revs\":" + String(revs, 2) + ",\"rpm\":" + String(sec > 0 ? revs / sec * 60.0 : 0, 1) + "}";
    }
    o += "]}";
    server.sendHeader("Content-Disposition", "attachment; filename=fan_export.json");
    server.send(200, "application/json", o); return;
  }
  if (w == "tests") {
    csvBegin("fan_tests.csv");
    server.sendContent("time,name,mode,seconds,revolutions,rpm,rev_per_sec\n");
    for (int i = 0; i < recN; i++) {
      double revs = rv(recs[i].pulses), sec = recs[i].durMs / 1000.0;
      if (recs[i].ts) fmtTime(recs[i].ts, tb, sizeof tb); else strcpy(tb, "-");
      c = String(tb) + ",\"" + jsonEsc(recs[i].name) + "\"," + (recs[i].mode ? "revs" : "time") + "," + String(sec, 2) + "," +
          String(revs, 2) + "," + String(sec > 0 ? revs / sec * 60.0 : 0, 1) + "," + String(sec > 0 ? revs / sec : 0, 3) + "\n";
      server.sendContent(c);
    }
    server.sendContent(""); return;
  }
  if (w == "rpm") {
    csvBegin("fan_rpm_seconds.csv");
    server.sendContent("seconds_ago,pulses,rev_per_sec,rpm\n");
    uint32_t cnt = sampleN < RING_N ? sampleN : RING_N;
    c = "";
    for (int i = (int)cnt - 1; i >= 0; i--) {
      uint32_t p = ringBack(i);
      c += String(i) + "," + String(p) + "," + String(rv(p), 3) + "," + String(rpmFromPps(p), 1) + "\n";
      if (c.length() > 900) { server.sendContent(c); c = ""; }
    }
    server.sendContent(c); server.sendContent(""); return;
  }
  // minutes / hours
  bool mins = (w == "minutes");
  csvBegin(mins ? "fan_minutes.csv" : "fan_hours.csv");
  server.sendContent(mins ? "time,revolutions_per_minute\n" : "time,revolutions_per_hour\n");
  if (timeOk()) {
    uint32_t now = (uint32_t)time(nullptr);
    int span = mins ? MIN_N : HOUR_N;
    uint32_t key = mins ? now / 60 : now / 3600;
    c = "";
    for (int i = span - 1; i >= 0; i--) {
      uint32_t k = key - i;
      uint32_t v = mins ? minGet(k) : hourGet(k);
      if (!v) continue;
      fmtTime((time_t)k * (mins ? 60 : 3600), tb, sizeof tb);
      c += String(tb) + "," + String(rv(v), 2) + "\n";
      if (c.length() > 900) { server.sendContent(c); c = ""; }
    }
    server.sendContent(c);
  }
  server.sendContent("");
}

// ---------- صفحه داشبورد ----------
// صفحه‌ی داشبورد: رشته‌های معمولی (بدون raw string) در چند تکه
static const char HTML_0[] PROGMEM =
"<!DOCTYPE html>\n"
"<html lang=\"fa\" dir=\"rtl\"><head><meta charset=\"utf-8\">\n"
"<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">\n"
"<title>Fan</title>\n"
"<style>\n"
":root{--bg:#070b14;--card:rgba(255,255,255,.05);--bd:rgba(255,255,255,.09);--tx:#e8ecf6;--mut:#8b95ad;--a:#22d3ee;--b:#8b5cf6;--ok:#34d399;--bad:#f87171}\n"
"body.light{--bg:#eef1f8;--card:rgba(255,255,255,.85);--bd:rgba(20,30,60,.12);--tx:#172036;--mut:#5d6985}\n"
"*{box-sizing:border-box;margin:0}\n"
"body{font-family:Vazirmatn,Tahoma,\"Segoe UI\",system-ui,sans-serif;color:var(--tx);min-height:100vh;padding:20px;\n"
"background:radial-gradient(900px 500px at 85% -10%,rgba(139,92,246,.28),transparent),radial-gradient(800px 500px at 0% 0%,rgba(34,211,238,.2),transparent),var(--bg);background-attachment:fixed}\n"
".wrap{max-width:1150px;margin:auto}\n"
"header{display:flex;justify-content:space-between;align-items:center;flex-wrap:wrap;gap:12px;margin-bottom:18px}\n"
"h1{font-size:1.4rem;display:flex;gap:12px;align-items:center}\n"
".logo{width:42px;height:42px;border-radius:13px;background:linear-gradient(135deg,var(--a),var(--b));display:grid;place-items:center;font-size:21px;box-shadow:0 8px 24px rgba(139,92,246,.4)}\n"
".hr{display:flex;align-items:center;gap:8px;flex-wrap:wrap;font-size:.85rem;color:var(--mut)}\n"
".dot{width:10px;height:10px;border-radius:50%;background:var(--bad);display:inline-block;margin-inline-end:6px}\n"
".dot.on{background:var(--ok);animation:pulse 2s infinite}\n"
"@keyframes pulse{0%{box-shadow:0 0 0 0 rgba(52,211,153,.6)}100%{box-shadow:0 0 0 10px rgba(52,211,153,0)}}\n"
".card{background:var(--card);border:1px solid var(--bd);border-radius:20px;padding:18px;backdrop-filter:blur(14px);-webkit-backdrop-filter:blur(14px);transition:.35s;margin-bottom:14px}\n"
".hero{display:grid;grid-template-columns:minmax(260px,1.2fr) 1fr;gap:18px;align-items:center}\n"
".hero.hit{box-shadow:0 0 0 1px var(--a),0 0 32px rgba(34,211,238,.35)}\n"
".gw{position:relative}\n"
"#gauge{width:100%;height:210px;display:block}\n"
".gval{position:absolute;left:0;right:0;bottom:4px;text-align:center}\n"
".gval b{font-size:2.8rem;display:block;line-height:1}\n"
".gval span{color:var(--mut);font-size:.85rem}\n"
".badge{display:inline-block;padding:4px 14px;border-radius:99px;font-size:.82rem;margin-bottom:10px}\n"
".badge.run{background:rgba(52,211,153,.15);color:var(--ok)}\n"
".badge.stop{background:rgba(248,113,113,.15);color:var(--bad)}\n"
".hl{display:flex;justify-content:space-between;align-items:baseline;padding:8px 0;border-bottom:1px solid var(--bd)}\n"
".hl small{color:var(--mut)}.hl b{font-size:1.5rem}\n"
"#spark{width:100%;height:56px;display:block;margin-top:10px}\n"
".grid{display:grid;grid-template-columns:repeat(auto-fill,minmax(160px,1fr));gap:12px;margin-bottom:14px}\n"
".grid .card{margin:0;padding:14px}\n"
".kpi small{color:var(--mut);font-size:.76rem}\n"
".kpi b{display:block;font-size:1.55rem;margin-top:4px;background:linear-gradient(90deg,var(--tx),var(--a));-webkit-background-clip:text;background-clip:text;color:transparent}\n"
".bar{display:flex;justify-content:space-between;align-items:center;flex-wrap:wrap;gap:12px;margin-bottom:14px}\n"
".bar h2{font-size:1.05rem}.bar h2 span{color:var(--mut);font-weight:400;font-size:.85rem;margin-inline-start:8px}\n"
".tabs{display:flex;gap:4px;background:rgba(255,255,255,.05);padding:4px;border-radius:14px;flex-wrap:wrap}\n"
"button{font:inherit;color:var(--mut);background:none;border:0;padding:8px 14px;border-radius:10px;cursor:pointer;transition:.25s}\n"
"button:hover{color:var(--tx)}\n"
".tabs button.on{background:linear-gradient(135deg,var(--a),var(--b));color:#fff;box-shadow:0 4px 16px rgba(139,92,246,.4)}\n"
".ghost{border:1px solid var(--bd);padding:5px 10px;font-size:.8rem}\n"
".ghost.on{color:var(--a);border-color:var(--a)}\n"
".pri{background:linear-gradient(135deg,var(--a),var(--b));color:#fff;padding:9px 18px}\n"
".danger:hover{color:var(--bad);border-color:var(--bad)}\n"
".cb{position:relative}\n"
"#cv{width:100%;height:320px;display:block;direction:ltr}\n"
;
static const char HTML_1[] PROGMEM =
".tip{position:absolute;pointer-events:none;background:rgba(10,14,26,.95);color:#e8ecf6;border:1px solid var(--bd);border-radius:12px;padding:8px 12px;font-size:.8rem;white-space:nowrap;opacity:0;transition:opacity .15s;z-index:3}\n"
".sum{display:grid;grid-template-columns:repeat(auto-fit,minmax(110px,1fr));gap:10px;margin-top:14px}\n"
".sum div{background:rgba(127,127,127,.08);border-radius:14px;padding:10px;text-align:center}\n"
".sum small{color:var(--mut);font-size:.75rem;display:block}.sum b{font-size:1.1rem}\n"
".al{padding:10px 14px;border-radius:14px;margin-bottom:8px;font-size:.85rem;display:flex;justify-content:space-between;align-items:center;gap:10px}\n"
".al.w{background:rgba(251,191,36,.12);border:1px solid rgba(251,191,36,.4);color:#d99a06}\n"
".al.b{background:rgba(248,113,113,.14);border:1px solid rgba(248,113,113,.5);color:var(--bad)}\n"
"input,select{font:inherit;color:var(--tx);background:rgba(127,127,127,.12);border:1px solid var(--bd);border-radius:10px;padding:7px 10px;max-width:100%}\n"
"option{color:#111}\n"
".row{display:flex;gap:10px;flex-wrap:wrap;align-items:end}\n"
".row label,.sg label{display:flex;flex-direction:column;gap:4px;font-size:.8rem;color:var(--mut)}\n"
".pg{height:10px;border-radius:99px;background:rgba(127,127,127,.15);overflow:hidden;margin:12px 0 6px}\n"
".pg i{display:block;height:100%;width:0;background:linear-gradient(90deg,var(--a),var(--b));transition:width .3s}\n"
"table{width:100%;border-collapse:collapse;font-size:.82rem;margin-top:10px}\n"
"th,td{padding:6px 8px;text-align:start;border-bottom:1px solid var(--bd)}th{color:var(--mut);font-weight:400}\n"
".tw{overflow-x:auto}\n"
".sys{display:grid;grid-template-columns:repeat(auto-fill,minmax(190px,1fr));gap:8px;font-size:.82rem}\n"
".sys div{background:rgba(127,127,127,.08);border-radius:12px;padding:8px 10px}.sys small{color:var(--mut);display:block}\n"
"footer{display:flex;gap:14px;flex-wrap:wrap;justify-content:space-between;align-items:center;margin-top:10px;color:var(--mut);font-size:.8rem}\n"
"footer a{color:var(--a);text-decoration:none}\n"
"dialog{background:var(--bg);color:var(--tx);border:1px solid var(--bd);border-radius:20px;padding:20px;width:min(620px,94vw);max-height:90vh;overflow:auto;margin:auto}\n"
"dialog::backdrop{background:rgba(0,0,0,.6)}\n"
"dialog h2{margin-bottom:12px}\n"
".sg{display:grid;grid-template-columns:repeat(auto-fit,minmax(210px,1fr));gap:12px}\n"
".sg .ck{flex-direction:row;align-items:center;gap:8px;color:var(--tx)}\n"
".acts{display:flex;gap:8px;flex-wrap:wrap;margin-top:16px}\n"
".acts a{color:var(--mut);text-decoration:none}\n"
"body.big .grid,body.big .tcard,body.big .chartcard,body.big .sysc,body.big footer{display:none}\n"
"body.big .hero{grid-template-columns:1fr}body.big .gval b{font-size:5rem}body.big #gauge{height:340px}\n"
"@media(max-width:700px){body{padding:12px}.hero{grid-template-columns:1fr}#cv{height:260px}}\n"
"@media print{body{background:#fff;color:#000}.hr,button,dialog{display:none}}\n"
"</style></head><body><div class=\"wrap\">\n"
"<header>\n"
" <h1><span class=\"logo\">🌀</span><span data-i=\"title\"></span></h1>\n"
" <div class=\"hr\"><span id=\"clock\">--</span><span><i class=\"dot\" id=\"dot\"></i><span id=\"st\"></span></span>\n"
"  <button class=\"ghost\" id=\"bLang\">EN</button><button class=\"ghost\" id=\"bCal\"></button><button class=\"ghost\" id=\"bTheme\">◐</button>\n"
"  <button class=\"ghost\" id=\"bSnd\">🔔</button><button class=\"ghost\" id=\"bBig\">⛶</button><button class=\"ghost\" id=\"bSet\">⚙</button></div>\n"
"</header>\n"
"<div id=\"alerts\"></div>\n"
"<div class=\"card hero\" id=\"hero\">\n"
" <div class=\"gw\"><canvas id=\"gauge\"></canvas><div class=\"gval\"><b id=\"gV\">0</b><span id=\"gU\"></span></div></div>\n"
" <div>\n"
"  <span class=\"badge stop\" id=\"state\"></span>\n"
"  <select id=\"uSel\"><option value=\"rpm\" data-i=\"u_rpm\"></option><option value=\"hz\" data-i=\"u_hz\"></option><option value=\"rads\" data-i=\"u_rads\"></option><option value=\"degs\" data-i=\"u_degs\"></option></select>\n"
"  <div class=\"hl\"><small data-i=\"h_hz\"></small><b id=\"hHz\">0</b></div>\n"
"  <div class=\"hl\"><small data-i=\"h_rps\"></small><b id=\"hRps\">0</b></div>\n"
;
static const char HTML_2[] PROGMEM =
"  <div class=\"hl\"><small data-i=\"h_tot\"></small><b id=\"hTot\">0</b></div>\n"
"  <canvas id=\"spark\"></canvas>\n"
" </div>\n"
"</div>\n"
"<div class=\"grid\" id=\"kpis\"></div>\n"
"<div class=\"card tcard\">\n"
" <div class=\"bar\"><h2 data-i=\"te_title\"></h2></div>\n"
" <div class=\"row\">\n"
"  <label><span data-i=\"te_mode\"></span><select id=\"teMode\"><option value=\"time\" data-i=\"te_time\"></option><option value=\"revs\" data-i=\"te_revs\"></option></select></label>\n"
"  <label><span id=\"teValL\"></span><input id=\"teVal\" type=\"number\" min=\"1\" step=\"1\" value=\"10\" style=\"width:120px\"></label>\n"
"  <label><span data-i=\"te_name\"></span><input id=\"teName\" maxlength=\"20\" style=\"width:160px\"></label>\n"
"  <button class=\"pri\" id=\"teGo\" data-i=\"te_start\"></button><button class=\"ghost danger\" id=\"teStop\" data-i=\"te_stop\"></button>\n"
" </div>\n"
" <div class=\"row\" style=\"margin-top:10px\" id=\"presets\"></div>\n"
" <div class=\"pg\"><i id=\"teBar\"></i></div>\n"
" <div id=\"teLive\" style=\"font-size:.9rem\"></div>\n"
" <div class=\"bar\" style=\"margin-top:14px\"><h2 data-i=\"te_hist\"></h2><div><a class=\"ghost\" style=\"text-decoration:none;color:var(--mut);padding:5px 10px;border:1px solid var(--bd);border-radius:10px;font-size:.8rem\" href=\"/api/export?what=tests\" download data-i=\"csv\"></a> <button class=\"ghost danger\" id=\"teClr\" data-i=\"te_clear\"></button></div></div>\n"
" <div class=\"tw\"><table><thead><tr><th data-i=\"th_when\"></th><th data-i=\"th_name\"></th><th data-i=\"th_dur\"></th><th data-i=\"th_revs\"></th><th>RPM</th><th>rev/s</th></tr></thead><tbody id=\"teBody\"></tbody></table></div>\n"
"</div>\n"
"<div class=\"card chartcard\">\n"
" <div class=\"bar\"><h2><span data-i=\"ch_title\"></span><span id=\"rl\"></span></h2>\n"
"  <div class=\"tabs\" id=\"tabs\">\n"
"   <button data-r=\"rpm\" class=\"on\" data-i=\"t_rpm\"></button><button data-r=\"second\" data-i=\"t_second\"></button><button data-r=\"minute\" data-i=\"t_minute\"></button><button data-r=\"hour\" data-i=\"t_hour\"></button><button data-r=\"day\" data-i=\"t_day\"></button><button data-r=\"month\" data-i=\"t_month\"></button>\n"
"  </div></div>\n"
" <div class=\"row\" style=\"margin-bottom:10px\">\n"
"  <button class=\"ghost\" id=\"bType\" data-i=\"ct\"></button><button class=\"ghost\" id=\"bFreeze\"></button>\n"
"  <select id=\"winSel\"><option value=\"30\">30</option><option value=\"60\">60</option><option value=\"120\">120</option><option value=\"300\">300</option></select>\n"
"  <a class=\"ghost\" id=\"csvLink\" style=\"text-decoration:none;color:var(--mut);border:1px solid var(--bd);border-radius:10px;padding:5px 10px;font-size:.8rem\" href=\"/api/export?what=rpm\" download data-i=\"csv\"></a>\n"
" </div>\n"
" <div class=\"cb\"><canvas id=\"cv\"></canvas><div class=\"tip\" id=\"tip\"></div></div>\n"
" <div class=\"sum\"><div><small data-i=\"s_sum\"></small><b id=\"sSum\">0</b></div><div><small data-i=\"s_avg\"></small><b id=\"sAvg\">0</b></div><div><small data-i=\"s_max\"></small><b id=\"sMax\">0</b></div><div><small data-i=\"s_min\"></small><b id=\"sMin\">0</b></div></div>\n"
"</div>\n"
"<div class=\"card sysc\"><div class=\"bar\"><h2 data-i=\"sy_title\"></h2></div><div class=\"sys\" id=\"sysBox\"></div></div>\n"
"<footer><span id=\"info\"></span><span><a href=\"/api/live\" target=\"_blank\">/api/live</a> · <a href=\"/api/sys\" target=\"_blank\">/api/sys</a> · <a href=\"/api/settings\" target=\"_blank\">/api/settings</a></span></footer>\n"
"</div>\n"
"<dialog id=\"dlg\"></dialog>\n"
"<script>\n"
"const $=s=>document.querySelector(s),$$=s=>[...document.querySelectorAll(s)];\n"
"const LS=(k,d)=>{try{const v=localStorage.getItem(k);return v===null?d:v}catch(e){return d}},SV=(k,v)=>{try{localStorage.setItem(k,v)}catch(e){}};\n"
"const TX={\n"
"fa:{title:'تاکومتر فن',connecting:'در حال اتصال…',online:'متصل و زنده',offline:'قطع ارتباط',\n"
"unsynced:'ساعت دستگاه همگام نشده؛ آمار دقیقه/ساعت/روز فعلاً ثبت نمی‌شود. گیج، RPM و نمودار ثانیه‌ای کار می‌کنند.',\n"
"run:'در حال چرخش',stop:'ایستاده',u_rpm:'دور بر دقیقه (RPM)',u_hz:'دور بر ثانیه (Hz)',u_rads:'رادیان بر ثانیه',u_degs:'درجه بر ثانیه',\n"
;
static const char HTML_3[] PROGMEM =
"su_rpm:'RPM',su_hz:'دور/ثانیه',su_rads:'rad/s',su_degs:'°/s',\n"
"h_hz:'دور در ثانیه (لحظه‌ای)',h_rps:'دور در آخرین ثانیه',h_tot:'مجموع دورها',\n"
"k_rps:'دور در آخرین ثانیه',k_r2:'میانگین ۲ ثانیه (RPM)',k_r10:'میانگین ۱۰ ثانیه (RPM)',k_r60:'میانگین ۱ دقیقه (RPM)',\n"
"k_pkS:'بیشینه از روشن شدن',k_pkA:'بیشینه تاریخی',k_mnS:'کمینه در حال چرخش',k_avS:'میانگین این نوبت',\n"
"k_acc:'شتاب (RPM/s)',k_stab:'پایداری سرعت',k_per:'فاصله‌ی پالس‌ها',k_pps:'پالس در ثانیه',\n"
"k_tot:'مجموع کل دورها',k_tod:'دور امروز',k_hr:'دور این ساعت',k_mn60:'دور ۶۰ ثانیه اخیر',\n"
"k_rt:'زمان کارکرد کل',k_ses:'تعداد نوبت‌های چرخش',k_sRev:'دور نوبت (جاری/آخر)',k_sDur:'مدت نوبت (جاری/آخر)',\n"
"k_tipms:'سرعت نوک پره (m/s)',k_tipkmh:'سرعت نوک پره (km/h)',k_bpf:'فرکانس عبور پره',k_noise:'نویز سنسور (رد شده/ثانیه)',\n"
"te_title:'تست زمان‌دار',te_mode:'روش',te_time:'مدت مشخص',te_revs:'تا رسیدن به تعداد دور',te_vs:'مدت (ثانیه)',te_vr:'تعداد دور هدف',\n"
"te_name:'نام تست (اختیاری)',te_start:'شروع',te_stop:'توقف',te_el:'زمان',te_rev:'دور',te_avg:'میانگین',te_hist:'تاریخچه‌ی تست‌ها',\n"
"te_clear:'پاک کردن',te_none:'هنوز تستی ثبت نشده',te_last:'آخرین نتیجه',csv:'CSV',\n"
"th_when:'زمان',th_name:'نام',th_dur:'مدت (s)',th_revs:'دور',\n"
"ch_title:'نمودار',t_rpm:'RPM زنده',t_second:'ثانیه',t_minute:'دقیقه',t_hour:'ساعت',t_day:'روز',t_month:'ماه',\n"
"rl_rpm:'RPM در ثانیه‌های اخیر',rl_second:'دور در هر ثانیه',rl_minute:'۶۰ دقیقه اخیر (دور در دقیقه)',rl_hour:'۲۴ ساعت اخیر',rl_day:'۳۰ روز اخیر',rl_month:'۱۲ ماه اخیر',\n"
"ct:'ستونی/خطی',freeze:'ثابت کردن',resume:'ادامه',s_sum:'مجموع',s_avg:'میانگین',s_max:'بیشترین',s_min:'کمترین',\n"
"set_title:'تنظیمات',s_ppr:'پالس در هر دور (تعداد نوار)',s_blades:'تعداد پره‌ها',s_radius:'شعاع پره (mm)',s_deb:'دیبانس (µs)',s_calib:'ضریب کالیبراسیون',\n"
"s_stop:'تشخیص توقف (ثانیه)',s_high:'هشدار RPM بالا (۰=خاموش)',s_low:'هشدار RPM پایین (۰=خاموش)',s_buz:'بیزر دستگاه',s_serial:'لاگ سریال',s_stall:'هشدار توقف ناگهانی',\n"
"s_tz:'منطقه‌ی زمانی',s_pass:'رمز جدید (خالی=بدون تغییر، -=حذف)',s_poll:'نرخ به‌روزرسانی',save:'ذخیره',close:'بستن',saved:'ذخیره شد ✓',\n"
"a_peaks:'ریست رکوردها',a_reset:'پاک کردن همه‌ی آمار',a_save:'ذخیره در حافظه',a_backup:'پشتیبان',a_json:'JSON',a_reboot:'ری‌استارت',a_factory:'تنظیمات کارخانه',confirm:'مطمئنی؟',\n"
"al_high:'RPM بالاتر از حد مجاز است',al_low:'RPM پایین‌تر از حد مجاز است',al_stall:'فن ناگهان ایستاد',al_noise:'نویز شدید روی سنسور؛ وقفه موقتاً قطع شد',ack:'بی‌صدا',\n"
"brown:'آخرین ریست دستگاه به‌خاطر افت ولتاژ بوده؛ تغذیه را بررسی کن (فن را از ESP تغذیه نکن).',\n"
"sy_title:'وضعیت دستگاه',sy_heap:'حافظه‌ی آزاد',sy_fs:'فلش (استفاده‌شده)',sy_temp:'دمای چیپ',sy_rssi:'سیگنال وای‌فای',sy_rst:'علت آخرین ریست',sy_fw:'نسخه',sy_noise:'پالس ردشده (کل)',sy_ne:'دفعات قطع نویز',sy_mac:'MAC',up:'روشن از'},\n"
"en:{title:'Fan Tachometer',connecting:'Connecting…',online:'Live',offline:'Offline',\n"
;
static const char HTML_4[] PROGMEM =
"unsynced:'Clock not synced yet; minute/hour/day stats are paused. Gauge, RPM and per-second charts still work.',\n"
"run:'Spinning',stop:'Stopped',u_rpm:'RPM',u_hz:'rev/s (Hz)',u_rads:'rad/s',u_degs:'deg/s',\n"
"su_rpm:'RPM',su_hz:'rev/s',su_rads:'rad/s',su_degs:'°/s',\n"
"h_hz:'Revs per second (instant)',h_rps:'Revs in last second',h_tot:'Total revolutions',\n"
"k_rps:'Revs in last second',k_r2:'Avg 2 s (RPM)',k_r10:'Avg 10 s (RPM)',k_r60:'Avg 1 min (RPM)',\n"
"k_pkS:'Peak since boot',k_pkA:'All-time peak',k_mnS:'Min while running',k_avS:'Session average',\n"
"k_acc:'Acceleration (RPM/s)',k_stab:'Speed stability',k_per:'Pulse period',k_pps:'Pulses / s',\n"
"k_tot:'Total revolutions',k_tod:'Today',k_hr:'This hour',k_mn60:'Last 60 s',\n"
"k_rt:'Total run time',k_ses:'Spin sessions',k_sRev:'Session revs (cur/last)',k_sDur:'Session time (cur/last)',\n"
"k_tipms:'Tip speed (m/s)',k_tipkmh:'Tip speed (km/h)',k_bpf:'Blade pass freq',k_noise:'Sensor noise (rejected/s)',\n"
"te_title:'Timed test',te_mode:'Mode',te_time:'Fixed duration',te_revs:'Until N revolutions',te_vs:'Duration (s)',te_vr:'Target revolutions',\n"
"te_name:'Test name (optional)',te_start:'Start',te_stop:'Stop',te_el:'Time',te_rev:'Revs',te_avg:'Average',te_hist:'Test history',\n"
"te_clear:'Clear',te_none:'No tests yet',te_last:'Last result',csv:'CSV',\n"
"th_when:'When',th_name:'Name',th_dur:'Dur (s)',th_revs:'Revs',\n"
"ch_title:'Chart',t_rpm:'Live RPM',t_second:'Second',t_minute:'Minute',t_hour:'Hour',t_day:'Day',t_month:'Month',\n"
"rl_rpm:'RPM, recent seconds',rl_second:'Revolutions per second',rl_minute:'last 60 min (revs/min)',rl_hour:'last 24 hours',rl_day:'last 30 days',rl_month:'last 12 months',\n"
"ct:'Bar/Line',freeze:'Freeze',resume:'Resume',s_sum:'Total',s_avg:'Average',s_max:'Max',s_min:'Min',\n"
"set_title:'Settings',s_ppr:'Pulses per revolution (tapes)',s_blades:'Blade count',s_radius:'Blade radius (mm)',s_deb:'Debounce (µs)',s_calib:'Calibration factor',\n"
"s_stop:'Stop detection (s)',s_high:'High RPM alarm (0=off)',s_low:'Low RPM alarm (0=off)',s_buz:'Device buzzer',s_serial:'Serial log',s_stall:'Sudden-stop alarm',\n"
"s_tz:'Time zone',s_pass:'New password (empty=keep, -=remove)',s_poll:'Refresh rate',save:'Save',close:'Close',saved:'Saved ✓',\n"
"a_peaks:'Reset records',a_reset:'Erase all stats',a_save:'Save to flash',a_backup:'Backup',a_json:'JSON',a_reboot:'Reboot',a_factory:'Factory reset',confirm:'Are you sure?',\n"
"al_high:'RPM above limit',al_low:'RPM below limit',al_stall:'Fan stopped suddenly',al_noise:'Heavy sensor noise; interrupt paused briefly',ack:'Silence',\n"
"brown:'Last reset was caused by a brownout; check the power supply (never power the fan from the ESP).',\n"
"sy_title:'Device status',sy_heap:'Free heap',sy_fs:'Flash used',sy_temp:'Chip temp',sy_rssi:'Wi-Fi signal',sy_rst:'Last reset reason',sy_fw:'Firmware',sy_noise:'Rejected pulses (total)',sy_ne:'Noise cut-offs',sy_mac:'MAC',up:'Up'}};\n"
"let lang=LS('lang','fa'),theme=LS('theme','dark'),jal=LS('cal','j')=='j',unit=LS('unit','rpm'),poll=+LS('poll',1000),ctype=LS('ctype',''),win=+LS('win',120),snd=LS('snd','0')=='1';\n"
"let res='rpm',data=[],shown=[],ck='epoch',nowS=0,hover=-1,frozen=false,L={},ST={ppr:1,blades:0,radius:0,high:0},SY={},lastSeries=0,raf=0,lastTser=null,hist=[],gcur=0,gtgt=0,gmax=3000,graf=0,busy=false,lastTot=null,tests=[],pollT=0,fm={};\n"
"const t=k=>(TX[lang]&&TX[lang][k])||TX.en[k]||k;\n"
"const esc=s=>String(s).replace(/[&<>\"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','\"':'&quot;',\"'\":'&#39;'}[c]));\n"
"const nfc={};\n"
"function fx(v,d=0){if(v==null||isNaN(v))return'—';const k=lang+d;return(nfc[k]||(nfc[k]=new Intl.NumberFormat(lang=='fa'?'fa-IR':'en-US',{minimumFractionDigits:d,maximumFractionDigits:d}))).format(v)}\n"
"function fmtDur(s){s=Math.round(s||0);const h=Math.floor(s/3600),m=Math.floor(s%3600/60),x=s%60;return(h?h+'h ':'')+(h||m?m+'m ':'')+x+'s'}\n"
"function fmts(){const L2=(lang=='fa'?'fa-IR':'en-GB')+(jal?'-u-ca-persian':'-u-ca-gregory');\n"
" fm.tf=new Intl.DateTimeFormat(L2,{hour:'2-digit',minute:'2-digit',hour12:false});\n"
;
static const char HTML_5[] PROGMEM =
" fm.tsf=new Intl.DateTimeFormat(L2,{hour:'2-digit',minute:'2-digit',second:'2-digit',hour12:false});\n"
" fm.dmf=new Intl.DateTimeFormat(L2,{day:'numeric',month:'short'});\n"
" fm.mf=new Intl.DateTimeFormat(L2,{month:'long',year:'numeric'});\n"
" fm.mshort=new Intl.DateTimeFormat(L2,{month:'short'});\n"
" fm.dfull=new Intl.DateTimeFormat(L2,{weekday:'long',year:'numeric',month:'long',day:'numeric'});\n"
" fm.full=new Intl.DateTimeFormat(L2,{year:'numeric',month:'short',day:'numeric',hour:'2-digit',minute:'2-digit',second:'2-digit',hour12:false});\n"
" $('#bCal').textContent=jal?'شمسی':'Gregorian'}\n"
"const toU=r=>unit=='hz'?r/60:unit=='rads'?r*Math.PI/30:unit=='degs'?r*6:r;\n"
"const UD={rpm:0,hz:2,rads:1,degs:0};\n"
"const rv=ST2=>ST.ppr>1?1:0;\n"
"const KP=[\n"
"['rps',r=>fx(r.rps,2)],['r2',r=>fx(r.r2,0)],['r10',r=>fx(r.r10,0)],['r60',r=>fx(r.r60,0)],\n"
"['pkS',r=>fx(r.pkS,0)],['pkA',r=>fx(r.pkA,0)],['mnS',r=>fx(r.mnS,0)],['avS',r=>fx(r.avS,0)],\n"
"['acc',r=>(r.acc>0?'+':'')+fx(r.acc,1)],['stab',r=>fx(r.stab,0)+'%'],['per',r=>r.per>0?fx(r.per,2)+' ms':'—'],['pps',r=>fx(r.pps,0)],\n"
"['tot',r=>fx(r.tot,rv())],['tod',r=>fx(r.tod,rv())],['hr',r=>fx(r.hr,rv())],['mn60',r=>fx(r.mn60,rv())],\n"
"['rt',r=>fmtDur(r.rt)],['ses',r=>fx(r.ses)],['sRev',r=>fx(r.sRev,rv())],['sDur',r=>fmtDur(r.sDur)],\n"
"['tipms',r=>ST.radius>0?fx(r.r2*Math.PI/30*ST.radius/1000,1):'—'],['tipkmh',r=>ST.radius>0?fx(r.r2*Math.PI/30*ST.radius/1000*3.6,1):'—'],\n"
"['bpf',r=>ST.blades>0?fx(r.r2/60*ST.blades,1)+' Hz':'—'],['noise',r=>fx(r.rej)]];\n"
"function buildKpis(){$('#kpis').innerHTML=KP.map(k=>`<div class=\"card kpi\"><small data-i=\"k_${k[0]}\"></small><b id=\"kv_${k[0]}\">—</b></div>`).join('')}\n"
"const SF=[['ppr','s_ppr',1,64,1],['blades','s_blades',0,200,1],['radius','s_radius',0,2000,.1],['deb','s_deb',20,100000,10],['calib','s_calib',.1,10,.001],['stop','s_stop',1,60,1],['high','s_high',0,1000000,10],['low','s_low',0,1000000,10]];\n"
"const SB=[['buz','s_buz'],['ser','s_serial'],['stl','s_stall']];\n"
"const TZS=[['Berlin / CET','CET-1CEST,M3.5.0,M10.5.0/3'],['Tehran','<+0330>-3:30'],['UTC','UTC0'],['London','GMT0BST,M3.5.0/1,M10.5.0'],['Istanbul','<+03>-3'],['Dubai','<+04>-4'],['New York','EST5EDT,M3.2.0,M11.1.0']];\n"
"function buildSet(){\n"
" let h='<h2 data-i=\"set_title\"></h2><div class=\"sg\">';\n"
" SF.forEach(f=>h+=`<label><span data-i=\"${f[1]}\"></span><input id=\"s_${f[0]}\" type=\"number\" min=\"${f[2]}\" max=\"${f[3]}\" step=\"${f[4]}\"></label>`);\n"
" SB.forEach(f=>h+=`<label class=\"ck\"><input id=\"s_${f[0]}\" type=\"checkbox\"><span data-i=\"${f[1]}\"></span></label>`);\n"
" h+='<label><span data-i=\"s_tz\"></span><select id=\"s_tz\"></select></label><label><span data-i=\"s_pass\"></span><input id=\"s_pass\" type=\"password\" autocomplete=\"new-password\"></label>';\n"
" h+='<label><span data-i=\"s_poll\"></span><select id=\"s_poll\"><option value=\"500\">0.5 s</option><option value=\"1000\">1 s</option><option value=\"2000\">2 s</option><option value=\"5000\">5 s</option></select></label></div>';\n"
" h+='<div class=\"acts\"><button class=\"pri\" id=\"sSave\" data-i=\"save\"></button><button class=\"ghost\" id=\"sClose\" data-i=\"close\"></button><button class=\"ghost\" id=\"aSave\" data-i=\"a_save\"></button><button class=\"ghost\" id=\"aPeaks\" data-i=\"a_peaks\"></button><a class=\"ghost\" href=\"/api/export?what=bin\" download style=\"padding:5px 10px;border:1px solid var(--bd);border-radius:10px;font-size:.8rem\" data-i=\"a_backup\"></a><a class=\"ghost\" href=\"/api/export?what=json\" download style=\"padding:5px 10px;border:1px solid var(--bd);border-radius:10px;font-size:.8rem\" data-i=\"a_json\"></a><a class=\"ghost\" href=\"/api/export?what=hours\" download style=\"padding:5px 10px;border:1px solid var(--bd);border-radius:10px;font-size:.8rem\">CSV h</a><a class=\"ghost\" href=\"/api/export?what=minutes\" download style=\"padding:5px 10px;border:1px solid var(--bd);border-radius:10px;font-size:.8rem\">CSV m</a></div>';\n"
;
static const char HTML_6[] PROGMEM =
" h+='<div class=\"acts\"><button class=\"ghost danger\" id=\"aReset\" data-i=\"a_reset\"></button><button class=\"ghost danger\" id=\"aReboot\" data-i=\"a_reboot\"></button><button class=\"ghost danger\" id=\"aFactory\" data-i=\"a_factory\"></button></div><div id=\"sMsg\" style=\"margin-top:10px;color:var(--ok)\"></div>';\n"
" $('#dlg').innerHTML=h;\n"
" const sel=$('#s_tz');TZS.forEach(z=>{const o=document.createElement('option');o.value=z[1];o.textContent=z[0];sel.appendChild(o)});\n"
" $('#sClose').onclick=()=>$('#dlg').close();\n"
" $('#sSave').onclick=saveSet;\n"
" $('#aSave').onclick=async()=>{await post('/api/save');msg(t('saved'))};\n"
" $('#aPeaks').onclick=async()=>{await post('/api/reset?what=peaks');msg(t('saved'))};\n"
" $('#aReset').onclick=async()=>{if(confirm(t('confirm'))){await post('/api/reset?what=all');lastTot=null;msg(t('saved'))}};\n"
" $('#aReboot').onclick=async()=>{if(confirm(t('confirm')))await post('/api/reboot')};\n"
" $('#aFactory').onclick=async()=>{if(confirm(t('confirm')))await post('/api/factory')};\n"
"}\n"
"const msg=m=>{$('#sMsg').textContent=m;setTimeout(()=>$('#sMsg').textContent='',2500)};\n"
"async function post(u,b){return fetch(u,{method:'POST',body:b})}\n"
"async function loadSet(){try{ST=await(await fetch('/api/settings')).json()}catch(e){}}\n"
"async function openSet(){await loadSet();SF.forEach(f=>$('#s_'+f[0]).value=ST[f[0]]);SB.forEach(f=>$('#s_'+f[0]).checked=!!ST[f[0]]);\n"
" $('#s_tz').value=ST.tz;if($('#s_tz').value!==ST.tz){const o=document.createElement('option');o.value=ST.tz;o.textContent=ST.tz;$('#s_tz').appendChild(o);$('#s_tz').value=ST.tz}\n"
" $('#s_poll').value=poll;$('#s_pass').value='';$('#dlg').showModal()}\n"
"async function saveSet(){const b=new URLSearchParams();SF.forEach(f=>b.set(f[0],$('#s_'+f[0]).value));SB.forEach(f=>b.set(f[0],$('#s_'+f[0]).checked?'1':'0'));\n"
" b.set('tz',$('#s_tz').value);if($('#s_pass').value)b.set('newpass',$('#s_pass').value);\n"
" poll=+$('#s_poll').value;SV('poll',poll);setPoll();\n"
" await post('/api/settings',b);await loadSet();msg(t('saved'))}\n"
"function applyLang(){document.documentElement.lang=lang;document.documentElement.dir=lang=='fa'?'rtl':'ltr';\n"
" $$('[data-i]').forEach(e=>e.textContent=t(e.dataset.i));\n"
" $('#bLang').textContent=lang=='fa'?'EN':'فا';document.title=t('title');fmts();\n"
" $('#teValL').textContent=t($('#teMode').value=='revs'?'te_vr':'te_vs');\n"
" $('#bFreeze').textContent=t(frozen?'resume':'freeze');$('#rl').textContent=t('rl_'+res);\n"
" $('#uSel').value=unit;$('#winSel').value=win;$('#st').textContent=t('connecting');\n"
" $('#bSnd').classList.toggle('on',snd);renderTests();drawGauge();draw()}\n"
"function applyTheme(){document.body.classList.toggle('light',theme=='light')}\n"
"const cvar=n=>getComputedStyle(document.body).getPropertyValue(n).trim()||'#888';\n"
"function label(x){const d=new Date(x*1000);\n"
" if(res=='rpm'||res=='second')return ck=='epoch'?fm.tsf.format(d):(x-nowS)+'s';\n"
" return res=='minute'||res=='hour'?fm.tf.format(d):res=='day'?fm.dmf.format(d):fm.mshort.format(d)}\n"
"function tipText(x){const d=new Date(x*1000);\n"
" if(res=='rpm'||res=='second')return ck=='epoch'?fm.full.format(d):(x-nowS)+' s';\n"
" return res=='day'?fm.dfull.format(d):res=='month'?fm.mf.format(d):fm.full.format(d)}\n"
"const unitOf=()=>res=='rpm'?'RPM':res=='second'?'rev/s':(lang=='fa'?'دور':'rev');\n"
"function nice(m){const v=m/4,p=Math.pow(10,Math.floor(Math.log10(v))),f=v/p;return 4*p*(f<=1?1:f<=2?2:f<=5?5:10)}\n"
"const cty=()=>ctype||(res=='rpm'?'line':'bar');\n"
"function draw(){\n"
" const cv=$('#cv'),x=cv.getContext('2d'),dpr=devicePixelRatio||1,W=cv.clientWidth,H=cv.clientHeight;if(!W)return;\n"
" if(cv.width!=Math.round(W*dpr)||cv.height!=Math.round(H*dpr)){cv.width=Math.round(W*dpr);cv.height=Math.round(H*dpr)}\n"
" x.setTransform(dpr,0,0,dpr,0,0);x.clearRect(0,0,W,H);\n"
" const mut=cvar('--mut'),Lm=54,R=8,T=12,B=30,pw=W-Lm-R,ph=H-T-B,n=data.length;\n"
" const mx=Math.max(3,...data.map(d=>d[1]),...shown),ym=nice(mx);\n"
" x.font='11px system-ui,Tahoma';x.textBaseline='middle';\n"
;
static const char HTML_7[] PROGMEM =
" for(let i=0;i<=4;i++){const y=T+ph-ph*i/4;x.strokeStyle='rgba(127,127,127,.18)';x.beginPath();x.moveTo(Lm,y);x.lineTo(W-R,y);x.stroke();\n"
"  x.fillStyle=mut;x.textAlign='right';x.fillText(fx(Math.round(ym*i/4)),Lm-8,y)}\n"
" if(!n)return;\n"
" const bw=pw/n,g=Math.max(1,bw*.22),gr=x.createLinearGradient(0,T,0,T+ph);gr.addColorStop(0,'#22d3ee');gr.addColorStop(1,'#8b5cf6');\n"
" const every=Math.ceil(72/bw);\n"
" if(cty()=='line'){\n"
"  const px=i=>Lm+(i+.5)*bw,py=i=>T+ph-ph*Math.min(shown[i]||0,ym)/ym;\n"
"  x.beginPath();x.moveTo(px(0),T+ph);for(let i=0;i<n;i++)x.lineTo(px(i),py(i));x.lineTo(px(n-1),T+ph);x.closePath();\n"
"  const ga=x.createLinearGradient(0,T,0,T+ph);ga.addColorStop(0,'rgba(34,211,238,.35)');ga.addColorStop(1,'rgba(139,92,246,0)');x.fillStyle=ga;x.fill();\n"
"  x.beginPath();for(let i=0;i<n;i++){i?x.lineTo(px(i),py(i)):x.moveTo(px(i),py(i))}x.strokeStyle='#22d3ee';x.lineWidth=2;x.stroke();x.lineWidth=1;\n"
"  if(hover>=0&&hover<n){x.fillStyle='#fff';x.beginPath();x.arc(px(hover),py(hover),4,0,7);x.fill()}\n"
"  for(let i=0;i<n;i++)if((n-1-i)%every==0){x.fillStyle=mut;x.textAlign='center';x.fillText(label(data[i][0]),px(i),H-12)}\n"
" }else for(let i=0;i<n;i++){const v=shown[i]||0,h=ph*v/ym,bx=Lm+i*bw+g/2,w=bw-g,by=T+ph-h;\n"
"  if(h>=.5){x.fillStyle=i==hover?'#fff':gr;x.beginPath();const r=Math.min(6,w/2);\n"
"   if(x.roundRect)x.roundRect(bx,by,w,h,[r,r,0,0]);else x.rect(bx,by,w,h);x.fill()}\n"
"  else{x.fillStyle=i==hover?'#fff':'rgba(127,127,127,.25)';x.fillRect(bx,T+ph-1.5,w,1.5)}\n"
"  if((n-1-i)%every==0){x.fillStyle=mut;x.textAlign='center';x.fillText(label(data[i][0]),bx+w/2,H-12)}}\n"
"}\n"
"function frame(){let more=false;for(let i=0;i<data.length;i++){const tg=data[i][1],s=shown[i]||0,d=tg-s;if(Math.abs(d)>.01){shown[i]=s+d*.25;more=true}else shown[i]=tg}\n"
" shown.length=data.length;draw();raf=more?requestAnimationFrame(frame):0}\n"
"function kick(){if(!raf)raf=requestAnimationFrame(frame)}\n"
"function stats(){const v=data.map(d=>d[1]),s=v.reduce((a,b)=>a+b,0);\n"
" $('#sSum').textContent=fx(s,1);$('#sAvg').textContent=fx(v.length?s/v.length:0,1);$('#sMax').textContent=fx(Math.max(0,...v),1);$('#sMin').textContent=fx(v.length?Math.min(...v):0,1);$('#rl').textContent=t('rl_'+res)}\n"
"const EVERY={rpm:1000,second:1000,minute:5000,hour:20000,day:60000,month:60000};\n"
"async function loadSeries(){lastSeries=Date.now();\n"
" const q='/api/series?res='+res+((res=='rpm'||res=='second')?'&n='+win:'');\n"
" const r=await(await fetch(q)).json();if(r.res!==res)return;data=r.data;ck=r.clock;nowS=r.now;stats();kick()}\n"
"function drawGauge(){\n"
" const cv=$('#gauge'),x=cv.getContext('2d'),dpr=devicePixelRatio||1,W=cv.clientWidth,H=cv.clientHeight;if(!W)return;\n"
" if(cv.width!=Math.round(W*dpr)||cv.height!=Math.round(H*dpr)){cv.width=Math.round(W*dpr);cv.height=Math.round(H*dpr)}\n"
" x.setTransform(dpr,0,0,dpr,0,0);x.clearRect(0,0,W,H);\n"
" const cx=W/2,cy=H-8,r=Math.min(W/2-18,H-30),mut=cvar('--mut');\n"
" x.lineCap='round';x.lineWidth=16;x.strokeStyle='rgba(127,127,127,.18)';x.beginPath();x.arc(cx,cy,r,Math.PI,2*Math.PI);x.stroke();\n"
" const fr=Math.max(0,Math.min(1,gcur/gmax)),hi=ST.high>0&&gcur>ST.high;\n"
" const gr=x.createLinearGradient(cx-r,0,cx+r,0);gr.addColorStop(0,'#22d3ee');gr.addColorStop(1,hi?'#f87171':'#8b5cf6');\n"
" x.strokeStyle=gr;x.beginPath();x.arc(cx,cy,r,Math.PI,Math.PI+Math.PI*fr);x.stroke();\n"
" x.font='11px system-ui';x.fillStyle=mut;x.textAlign='center';x.textBaseline='middle';\n"
" for(let i=0;i<=5;i++){const a=Math.PI+Math.PI*i/5,tx=cx+Math.cos(a)*(r+0),ty=cy+Math.sin(a)*(r+0);\n"
"  const lx=cx+Math.cos(a)*(r-26),ly=cy+Math.sin(a)*(r-26);x.fillText(fx(toU(gmax*i/5),UD[unit]>1?1:0),lx,ly)}\n"
" if(ST.high>0){const a=Math.PI+Math.PI*Math.min(1,ST.high/gmax);x.strokeStyle='#f87171';x.lineWidth=3;x.beginPath();x.moveTo(cx+Math.cos(a)*(r-12),cy+Math.sin(a)*(r-12));x.lineTo(cx+Math.cos(a)*(r+12),cy+Math.sin(a)*(r+12));x.stroke()}\n"
"}\n"
"function gloop(){const d=gtgt-gcur;gcur+=d*.14;drawGauge();graf=Math.abs(d)>.5?requestAnimationFrame(gloop):0}\n"
"function gkick(){if(!graf)graf=requestAnimationFrame(gloop)}\n"
;
static const char HTML_8[] PROGMEM =
"function spark(){const cv=$('#spark'),x=cv.getContext('2d'),dpr=devicePixelRatio||1,W=cv.clientWidth,H=cv.clientHeight;if(!W)return;\n"
" if(cv.width!=Math.round(W*dpr)||cv.height!=Math.round(H*dpr)){cv.width=Math.round(W*dpr);cv.height=Math.round(H*dpr)}\n"
" x.setTransform(dpr,0,0,dpr,0,0);x.clearRect(0,0,W,H);if(hist.length<2)return;\n"
" const mx=Math.max(10,...hist);x.strokeStyle='#22d3ee';x.lineWidth=2;x.beginPath();\n"
" hist.forEach((v,i)=>{const px=i/(hist.length-1)*W,py=H-3-(H-6)*v/mx;i?x.lineTo(px,py):x.moveTo(px,py)});x.stroke()}\n"
"let ac;function beep(){if(!snd)return;try{ac=ac||new(window.AudioContext||window.webkitAudioContext)();const o=ac.createOscillator(),g=ac.createGain();o.frequency.value=880;g.gain.value=.08;o.connect(g);g.connect(ac.destination);o.start();o.stop(ac.currentTime+.18)}catch(e){}}\n"
"function online(o){$('#dot').className='dot'+(o?' on':'');$('#st').textContent=t(o?'online':'offline')}\n"
"function renderAlerts(){const a=[];if(!L.sync)a.push(['w',t('unsynced')]);\n"
" if(L.alH)a.push(['b',t('al_high')]);if(L.alL)a.push(['b',t('al_low')]);if(L.alS)a.push(['b',t('al_stall')]);if(L.alN)a.push(['w',t('al_noise')]);\n"
" if(SY.rr==9)a.push(['w',t('brown')]);\n"
" const any=L.alH||L.alL||L.alS||L.alN;\n"
" $('#alerts').innerHTML=a.map((x,i)=>`<div class=\"al ${x[0]}\"><span>${esc(x[1])}</span>${i==a.length-1&&any&&!L.sil?`<button class=\"ghost\" id=\"ack\">${esc(t('ack'))}</button>`:''}</div>`).join('')}\n"
"function renderTest(){\n"
" const p=$('#presets');if(!p.dataset.b){p.dataset.b=1;[5,10,30,60,120].forEach(s=>{const b=document.createElement('button');b.className='ghost';b.textContent=s+'s';b.onclick=()=>{$('#teMode').value='time';$('#teVal').value=s;$('#teValL').textContent=t('te_vs')};p.appendChild(b)})}\n"
" let pr=0,txt='';\n"
" if(L.ta){const rv2=L.tp,el=L.tel/1000;pr=L.tmode==0?L.tel/L.tdur:L.tp/L.tT;\n"
"  txt=`${esc(L.tname||'')} — ${t('te_el')}: ${fx(el,1)} s • ${t('te_rev')}: ${fx(rv2,1)} • ${t('te_avg')}: ${fx(el>0?rv2/el*60:0,0)} RPM (${fx(el>0?rv2/el:0,2)} rev/s)`}\n"
" else if(tests.length){const r=tests[0];pr=1;txt=`${t('te_last')}: ${esc(r.name||'')} — ${fx(r.revs,1)} ${t('te_rev')} / ${fx(r.dur,2)} s = ${fx(r.rpm,0)} RPM (${fx(r.hz,2)} rev/s)`}\n"
" $('#teBar').style.width=Math.max(0,Math.min(100,pr*100))+'%';$('#teLive').innerHTML=txt}\n"
"function renderTests(){const tb=$('#teBody');if(!tb)return;\n"
" tb.innerHTML=tests.length?tests.map(r=>`<tr><td>${r.ts?fm.full.format(new Date(r.ts*1000)):'—'}</td><td>${esc(r.name||'')}</td><td>${fx(r.dur,2)}</td><td>${fx(r.revs,1)}</td><td>${fx(r.rpm,0)}</td><td>${fx(r.hz,2)}</td></tr>`).join(''):`<tr><td colspan=\"6\" style=\"color:var(--mut)\">${esc(t('te_none'))}</td></tr>`;renderTest()}\n"
"async function loadTests(){try{tests=await(await fetch('/api/tests')).json();renderTests()}catch(e){}}\n"
"async function live(){if(busy)return;busy=true;\n"
" try{const r=await(await fetch('/api/live')).json();L=r;online(true);\n"
"  const rp=r.rpm;gtgt=rp;gmax=Math.max(1000,Math.ceil(Math.max(ST.high||0,r.pkA||0,rp)*1.1/500)*500);gkick();\n"
"  $('#gV').textContent=fx(toU(rp),UD[unit]);$('#gU').textContent=t('su_'+unit);\n"
"  const sb=$('#state');sb.className='badge '+(r.run?'run':'stop');sb.textContent=t(r.run?'run':'stop');\n"
"  $('#hHz').textContent=fx(r.hz,2);$('#hRps').textContent=fx(r.rps,2);$('#hTot').textContent=fx(r.tot,rv());\n"
"  KP.forEach(k=>{const e=$('#kv_'+k[0]);if(e)e.textContent=k[1](r)});\n"
"  hist.push(rp);if(hist.length>90)hist.shift();spark();\n"
"  $('#clock').textContent=r.sync?fm.full.format(new Date(r.now*1000)):'—';\n"
"  document.title=(r.run?fx(rp,0)+' RPM · ':'')+t('title');\n"
"  $('#info').textContent=(r.ap?'Hotspot':'Wi-Fi '+(SY.rssiV!=null?SY.rssiV+' dBm':''))+' • IP '+r.ip+' • '+t('up')+' '+fmtDur(r.up);\n"
"  if(lastTot!==null&&r.tot!==lastTot){const h=$('#hero');h.classList.add('hit');setTimeout(()=>h.classList.remove('hit'),350)}lastTot=r.tot;\n"
"  if((r.alH||r.alL||r.alS||r.alN)&&!r.sil)beep();\n"
"  renderAlerts();renderTest();\n"
"  if(r.tser!==lastTser){lastTser=r.tser;loadTests()}\n"
;
static const char HTML_9[] PROGMEM =
"  if(!frozen&&Date.now()-lastSeries>EVERY[res])await loadSeries();\n"
" }catch(e){online(false)}busy=false}\n"
"function setPoll(){clearInterval(pollT);pollT=setInterval(live,poll)}\n"
"async function sys(){try{SY=await(await fetch('/api/sys')).json();\n"
" const RR={1:'Power-on',3:'Software reset',4:'Crash (panic)',5:'Interrupt WDT',6:'Task WDT',7:'Other WDT',8:'Deep sleep',9:'Brownout'};\n"
" const row=(k,v)=>`<div><small>${esc(t(k))}</small>${esc(v)}</div>`;\n"
" $('#sysBox').innerHTML=row('sy_heap',Math.round(SY.heap/1024)+' / '+Math.round(SY.heapT/1024)+' KB')+row('sy_fs',Math.round(SY.fsU/1024)+' / '+Math.round(SY.fsT/1024)+' KB')+\n"
" row('sy_temp',fx(SY.temp,1)+' °C')+row('sy_rssi',SY.ssid+' · '+SY.rssiV+' dBm')+row('sy_rst',RR[SY.rr]||SY.rr)+row('sy_fw',SY.fw+' · '+SY.chip+' @'+SY.cpu+' MHz')+\n"
" row('sy_noise',fx(SY.rejT))+row('sy_ne',fx(SY.ne))+row('sy_mac',SY.mac)}catch(e){}}\n"
"$('#tabs').onclick=e=>{const b=e.target.closest('button');if(!b)return;res=b.dataset.r;\n"
" $$('#tabs button').forEach(x=>x.classList.toggle('on',x==b));data=[];shown=[];hover=-1;\n"
" $('#csvLink').href='/api/export?what='+(res=='minute'?'minutes':(res=='rpm'||res=='second')?'rpm':'hours');\n"
" $('#winSel').style.display=(res=='rpm'||res=='second')?'':'none';draw();loadSeries()};\n"
"$('#winSel').onchange=e=>{win=+e.target.value;SV('win',win);loadSeries()};\n"
"$('#uSel').onchange=e=>{unit=e.target.value;SV('unit',unit);live();drawGauge()};\n"
"$('#bType').onclick=()=>{ctype=cty()=='bar'?'line':'bar';SV('ctype',ctype);draw()};\n"
"const toggleFreeze=()=>{frozen=!frozen;$('#bFreeze').textContent=t(frozen?'resume':'freeze');$('#bFreeze').classList.toggle('on',frozen)};\n"
"$('#bFreeze').onclick=toggleFreeze;\n"
"const toggleLang=()=>{lang=lang=='fa'?'en':'fa';SV('lang',lang);applyLang();live()};\n"
"$('#bLang').onclick=toggleLang;\n"
"$('#bCal').onclick=()=>{jal=!jal;SV('cal',jal?'j':'g');fmts();stats();draw();live()};\n"
"const toggleTheme=()=>{theme=theme=='dark'?'light':'dark';SV('theme',theme);applyTheme();draw();drawGauge()};\n"
"$('#bTheme').onclick=toggleTheme;\n"
"$('#bSnd').onclick=()=>{snd=!snd;SV('snd',snd?'1':'0');$('#bSnd').classList.toggle('on',snd);if(snd)beep()};\n"
"const toggleBig=()=>{document.body.classList.toggle('big');if(document.body.classList.contains('big')){try{document.documentElement.requestFullscreen()}catch(e){}}else{try{document.exitFullscreen()}catch(e){}}setTimeout(()=>{drawGauge();draw()},100)};\n"
"$('#bBig').onclick=toggleBig;\n"
"$('#bSet').onclick=openSet;\n"
"$('#alerts').onclick=async e=>{if(e.target.id=='ack'){await post('/api/ack');live()}};\n"
"$('#teMode').onchange=()=>{$('#teValL').textContent=t($('#teMode').value=='revs'?'te_vr':'te_vs')};\n"
"$('#teGo').onclick=async()=>{const v=+$('#teVal').value;if(!(v>0))return;await post('/api/test/start',new URLSearchParams({mode:$('#teMode').value,value:v,name:$('#teName').value}));live()};\n"
"$('#teStop').onclick=async()=>{await post('/api/test/stop');live()};\n"
"$('#teClr').onclick=async()=>{if(confirm(t('confirm'))){await post('/api/reset?what=tests');loadTests()}};\n"
"const cv=$('#cv'),tip=$('#tip');\n"
"function move(e){const r=cv.getBoundingClientRect(),cx=(e.touches?e.touches[0].clientX:e.clientX)-r.left,Lm=54,R=8;\n"
" if(!data.length)return;const i=Math.floor((cx-Lm)/((r.width-Lm-R)/data.length));\n"
" if(i<0||i>=data.length){leave();return}hover=i;\n"
" tip.innerHTML='<b>'+fx(data[i][1],res=='rpm'?0:2)+' '+unitOf()+'</b><br><span style=\"color:#8b95ad\">'+esc(tipText(data[i][0]))+'</span>';\n"
" tip.style.opacity=1;const w=tip.offsetWidth;tip.style.left=Math.max(0,Math.min(r.width-w,cx-w/2))+'px';tip.style.top='6px';draw()}\n"
"function leave(){hover=-1;tip.style.opacity=0;draw()}\n"
"cv.addEventListener('mousemove',move);cv.addEventListener('touchmove',move,{passive:true});cv.addEventListener('touchstart',move,{passive:true});\n"
"cv.addEventListener('mouseleave',leave);cv.addEventListener('touchend',()=>setTimeout(leave,1200));\n"
"addEventListener('resize',()=>{draw();drawGauge();spark()});\n"
"addEventListener('keydown',e=>{if(/INPUT|SELECT|TEXTAREA/.test((e.target.tagName||'')))return;\n"
;
static const char HTML_10[] PROGMEM =
" const k=e.key.toLowerCase();if(k=='f')toggleFreeze();else if(k=='b')toggleBig();else if(k=='l')toggleLang();else if(k=='t')toggleTheme();else if(k=='s')openSet()});\n"
"(async()=>{buildKpis();buildSet();applyTheme();applyLang();$('#winSel').value=win;await loadSet();await sys();live();setPoll();setInterval(sys,5000);loadTests();loadSeries()})();\n"
"</script></body></html>"
;
static const char* const HTML_PARTS[] = {HTML_0,HTML_1,HTML_2,HTML_3,HTML_4,HTML_5,HTML_6,HTML_7,HTML_8,HTML_9,HTML_10};
static const size_t HTML_N = 11;

void sendIndex() {
  server.setContentLength(CONTENT_LENGTH_UNKNOWN);
  server.send(200, "text/html; charset=utf-8", "");
  for (size_t i = 0; i < HTML_N; i++) server.sendContent_P(HTML_PARTS[i]);
  server.sendContent("");
}

// ---------- اتصال شبکه ----------
void connectWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(HOSTNAME);
  WiFi.setAutoReconnect(true);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  Serial.print("Connecting to WiFi");
  uint32_t t0 = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - t0 < 20000) { delay(400); Serial.print('.'); }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.printf("\nConnected! Open: http://%s  or  http://%s.local\n", WiFi.localIP().toString().c_str(), HOSTNAME);
  } else {
    Serial.println("\nWiFi failed -> hotspot mode");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Fan-Counter");
    Serial.printf("Hotspot: Fan-Counter  ->  http://%s\n", WiFi.softAPIP().toString().c_str());
  }
}

// ---------- نمونه‌برداری ۱ هرتز ----------
void tick1Hz() {
  uint32_t d = totalCount >= lastSampleTotal ? totalCount - lastSampleTotal : 0;
  lastSampleTotal = totalCount;
  ppsRing[sampleN % RING_N] = d; sampleN++;

  bool run = isRunning();
  float rpm = rpmFromPps(d);
  if (run) {
    runtimeSec++;
    if (rpm > peakSession) peakSession = rpm;
    if (rpm > sessPeak) sessPeak = rpm;
    if (rpm > peakAll) { peakAll = rpm; dirty = true; }
    if (d > 0 && (minSession == 0 || rpm < minSession)) minSession = rpm;
  }
  if (run && !wasRunning) {
    sessions++; sessStartMs = millis() - 1000; sessStartTotal = totalCount - d; sessPeak = rpm;
    stallLatched = false; dirty = true;
  }
  if (!run && wasRunning) {
    lastSessRevs = totalCount >= sessStartTotal ? rv(totalCount - sessStartTotal) : 0;
    uint32_t endMs = lastPulseMs > sessStartMs ? lastPulseMs : millis();
    lastSessDur = (endMs - sessStartMs) / 1000.0; lastSessPeak = sessPeak;
    if (S.alStall) { stallLatched = true; silenced = false; }
  }
  wasRunning = run;

  // نگهبان نویز
  uint32_t rj = rejected; rejPerSec = (float)(rj - prevRej); prevRej = rj;
  if (isrAttached && rejPerSec > NOISE_LIMIT) {
    detachInterrupt(digitalPinToInterrupt(SENSOR_PIN)); isrAttached = false;
    noiseUntil = millis() + 3000; noiseEvents++; lastNoiseMs = millis();
  }
  alNoise = noiseEvents > 0 && (millis() - lastNoiseMs) < 10000;

  // هشدارهای سرعت
  float r2 = avgRpm(2);
  alHigh = S.rpmHigh > 0 && r2 > (float)S.rpmHigh;
  alLow  = S.rpmLow > 0 && run && (millis() - sessStartMs) > 5000 && r2 > 0 && r2 < (float)S.rpmLow;
  if (!(alHigh || alLow || stallLatched || alNoise)) silenced = false;

  if (S.serialLog)
    Serial.printf("RPM inst=%.0f avg2=%.0f avg10=%.0f rev/s=%.2f pps=%lu rej/s=%.0f %s\n",
                  instRpm(), r2, avgRpm(10), rv(d), (unsigned long)d, rejPerSec, run ? "RUN" : "STOP");
}

void setup() {
  Serial.begin(115200);
  pinMode(SENSOR_PIN, INPUT_PULLUP);
  if (LED_PIN >= 0) { pinMode(LED_PIN, OUTPUT); digitalWrite(LED_PIN, LOW); }
  if (BUZZER_PIN >= 0) { pinMode(BUZZER_PIN, OUTPUT); digitalWrite(BUZZER_PIN, LOW); }
  if (!LittleFS.begin(true)) Serial.println("LittleFS mount failed");
  loadSettings();
  loadData();
  loadTests();
  lastSampleTotal = totalCount;
  nextTick = millis() + 1000;

  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), onPass, FALLING);
  isrAttached = true;

  connectWiFi();
  configTzTime(S.tz, "pool.ntp.org", "time.google.com", "time.cloudflare.com");
  MDNS.begin(HOSTNAME);
  MDNS.addService("http", "tcp", 80);

  ArduinoOTA.setHostname(HOSTNAME);
  if (S.pass[0]) ArduinoOTA.setPassword(S.pass);
  ArduinoOTA.begin();

  server.on("/", sendIndex);
  server.on("/api/live", apiLive);
  server.on("/api/series", apiSeries);
  server.on("/api/sys", apiSys);
  server.on("/api/settings", HTTP_GET, apiSettingsGet);
  server.on("/api/settings", HTTP_POST, apiSettingsPost);
  server.on("/api/tests", apiTests);
  server.on("/api/test/start", HTTP_POST, apiTestStart);
  server.on("/api/test/stop", HTTP_POST, apiTestStop);
  server.on("/api/reset", HTTP_POST, apiReset);
  server.on("/api/ack", HTTP_POST, apiAck);
  server.on("/api/save", HTTP_POST, apiSave);
  server.on("/api/reboot", HTTP_POST, apiReboot);
  server.on("/api/factory", HTTP_POST, apiFactory);
  server.on("/api/export", apiExport);
  server.onNotFound([]() { server.send(404, "text/plain", "Not found"); });
  server.begin();
  lastSave = millis();
}

void loop() {
  server.handleClient();
  ArduinoOTA.handle();

  uint32_t n;
  portENTER_CRITICAL(&mux);
  n = pending; pending = 0;
  portEXIT_CRITICAL(&mux);
  if (n) { recordPasses(n); everPulsed = true; lastPulseMs = millis(); }

  // LED چشمک با هر پالس
  if (LED_PIN >= 0) {
    if (n) { digitalWrite(LED_PIN, HIGH); ledOffMs = millis() + 25; }
    else if (ledOffMs && millis() > ledOffMs) { digitalWrite(LED_PIN, LOW); ledOffMs = 0; }
  }

  testTick();

  if ((int32_t)(millis() - nextTick) >= 0) {
    nextTick += 1000;
    if ((int32_t)(millis() - nextTick) > 2000) nextTick = millis() + 1000;
    tick1Hz();
  }

  // وصل مجدد وقفه بعد از طوفان نویز
  if (!isrAttached && millis() > noiseUntil) {
    attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), onPass, FALLING);
    isrAttached = true; prevRej = rejected;
  }

  // بیزر
  if (BUZZER_PIN >= 0) {
    bool any = (alHigh || alLow || stallLatched || alNoise) && S.buzzer && !silenced;
    digitalWrite(BUZZER_PIN, any && (millis() % 1000) < 200 ? HIGH : LOW);
  }

  if (dirty && millis() - lastSave >= SAVE_EVERY_MS) { saveData(); lastSave = millis(); }
  delay(1);
}
