# 🌀 Fan RPM Tachometer (ESP32-S3 + TCRT5000)

[![Compile sketch](https://github.com/YOUR_USERNAME/fan-rpm-tachometer/actions/workflows/compile.yml/badge.svg)](https://github.com/YOUR_USERNAME/fan-rpm-tachometer/actions/workflows/compile.yml)
[![License: MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)
![Platform](https://img.shields.io/badge/platform-ESP32--S3-informational)
![Arduino](https://img.shields.io/badge/framework-Arduino-00979D)

🇮🇷 [نسخه فارسی (README.fa.md)](README.fa.md)

A self-contained **fan tachometer** with a live web dashboard. An ESP32-S3 reads a cheap
TCRT5000 reflective IR sensor, counts every revolution of a fan, and serves a responsive
dashboard from the board itself — no cloud, no extra libraries, no app to install.

Use it to answer questions like *"how many revolutions does this fan make in 10 seconds?"*,
*"what RPM does it reach at 9 V vs 12 V?"* or *"how long did it spin today?"*.

<p align="center">
  <img src="docs/dashboard-dark.png" alt="Dashboard (dark theme)" width="46%">
  <img src="docs/dashboard-light.png" alt="Dashboard (light theme)" width="46%">
</p>

> The screenshots above were rendered from the real dashboard page using simulated data.

## ✨ Features

**Measurement**
- Instantaneous RPM from the time between pulses, plus 2 s / 10 s / 60 s averages
- Revolutions per second (Hz), pulses per second, acceleration (RPM/s), speed stability %
- Peak since boot, all-time peak (persistent), minimum while running, session average
- Spin-session detection (spinning / stopped), per-session revolutions and duration
- Totals for the last 60 s, this hour, today, and all-time (persistent across reboots)
- Optional blade-tip speed (m/s, km/h) and blade-pass frequency
- Display units: RPM, rev/s, rad/s, deg/s
- Calibration factor and configurable pulses per revolution

**Timed tests**
- *Fixed duration* ("count revolutions in 10 s") or *until N revolutions* ("how long for 500 turns?")
- Live progress bar, optional test name, history of the last 20 tests (persistent)
- Export tests as CSV

**Charts and history**
- Live RPM chart (last 30–300 s, works without internet)
- Per-second, per-minute (60 min), per-hour (24 h), per-day (30 days), per-month (12 months)
- Bar/line toggle, freeze, hover/touch tooltip, summary (sum / avg / max / min)
- Jalali (Persian) or Gregorian calendar

**Alerts and protection**
- High RPM, low RPM, sudden stop, and sensor-noise alerts (banner + optional browser beep + optional buzzer)
- Noise guard: if the sensor floods the interrupt, it is detached for 3 s so the ESP32 never hangs
- Brown-out detection: tells you when the last reset was caused by a power dip
- Optional status LED that blinks on every pulse

**Data and system**
- CSV export (seconds / minutes / hours / tests), JSON export, binary backup
- Persistent settings (NVS) and data (LittleFS)
- Full REST API, mDNS (`http://fan-counter.local`), OTA updates, optional password for sensitive actions
- Fallback Wi-Fi hotspot if the router can't be reached
- Device status: free heap, flash usage, chip temperature, RSSI, reset reason, firmware version

**Interface**
- Persian (RTL) and English, dark and light theme, mobile-friendly
- Big-display mode (full screen), keyboard shortcuts, RPM shown in the browser tab title
- Print-friendly layout

## 🧰 Hardware

| Part | Notes |
|---|---|
| ESP32-S3 dev board | Any ESP32 should work; developed on ESP32-S3 |
| TCRT5000 module (with LM393 comparator, `D0` output) | The `A0` pin is not used |
| Reflective tape | A small piece of aluminium / white tape on one blade or on the hub |
| Fan + its **own** power supply | Do **not** power the fan from the ESP32 |
| 100 nF capacitor (optional) | Between VCC and GND of the sensor to reduce noise |

### Wiring

![Wiring diagram](docs/wiring.svg)

| Sensor module | ESP32-S3 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| D0 | GPIO 4 |

The fan's power supply ground **must be common** with the ESP32 ground (only GND, never the supply's +V).
Optional: an LED on `LED_PIN` and a buzzer on `BUZZER_PIN` (both disabled by default, set in the sketch).

### Mechanical setup (this matters more than the code)
1. Stick **one** strip of reflective tape on a blade or on the hub, so one revolution = one pulse.
   If you use several strips, set *Pulses per revolution* in the settings.
2. Place the sensor 3–10 mm from the tape.
3. Turn the module's potentiometer until its on-board LED switches **exactly once** per pass of the tape.
4. Keep wires away from the blades.

## 🚀 Getting started

1. Install the [Arduino IDE](https://www.arduino.cc/en/software) and the **esp32 by Espressif Systems** board package.
   No extra libraries are required (everything used ships with the ESP32 core).
2. Open `fan_rpm_pro/fan_rpm_pro.ino`.
3. Edit the settings at the top of the sketch:
   ```cpp
   const char* WIFI_SSID = "YOUR_WIFI_NAME";
   const char* WIFI_PASS = "YOUR_WIFI_PASSWORD";
   const char* DEFAULT_TZ = "CET-1CEST,M3.5.0,M10.5.0/3";   // Iran: "<+0330>-3:30"
   ```
4. Select **Tools → Board → ESP32S3 Dev Module** and upload.
5. Open the Serial Monitor (115200). It prints the address, e.g. `http://fan-counter.local`
   or the board's IP. Open it in a browser on the same network.

If the board can't join your Wi-Fi within 20 s, it starts an open hotspot named **`Fan-Counter`**;
connect to it and browse to `http://192.168.4.1`.

> The time zone and most other options can be changed later from the dashboard (⚙ Settings).
> Minute/hour/day statistics need the clock to be synced via NTP (internet access). The gauge, live RPM chart, per-second data and timed tests work without it.

## 🛠 Configuration

Compile-time constants (top of the sketch):

| Constant | Default | Meaning |
|---|---|---|
| `SENSOR_PIN` | `4` | GPIO connected to `D0` |
| `LED_PIN` / `BUZZER_PIN` | `-1` | Optional pins (`-1` = disabled) |
| `HOSTNAME` | `fan-counter` | mDNS name / OTA hostname |
| `SAVE_EVERY_MS` | 5 min | How often totals are written to flash |
| `NOISE_LIMIT` | `20000` | Rejected pulses per second that trigger the noise guard |

Runtime settings (dashboard → ⚙, stored in flash):

| Setting | Meaning |
|---|---|
| Pulses per revolution | Number of reflective strips |
| Blade count / radius | For blade-pass frequency and tip speed |
| Debounce (µs) | Minimum time between two pulses (default 300 µs) |
| Calibration factor | Multiplies all results |
| Stop detection (s) | How long without pulses counts as "stopped" |
| High / low RPM alarms | `0` = off |
| Buzzer, serial log, stall alarm | Toggles |
| Time zone, password, refresh rate | — |

**Maximum measurable speed** ≈ `60 000 000 / (debounce_µs × pulses_per_rev)` RPM.
With the defaults that's 200 000 RPM, far above any normal fan; the real limit is the sensor itself
(TCRT5000 modules are reliable up to a few kHz).

## 🔌 REST API

All responses are JSON unless noted. CORS is open (`*`).

| Method | Endpoint | Description |
|---|---|---|
| GET | `/api/live` | Everything shown on the live panel (RPM, averages, totals, alarms, test state…) |
| GET | `/api/series?res=rpm\|second\|minute\|hour\|day\|month&n=120` | Chart data as `[[timestamp, value], …]` (`n` only for `rpm`/`second`) |
| GET | `/api/sys` | Heap, flash, temperature, RSSI, MAC, firmware, reset reason |
| GET / POST | `/api/settings` | Read / change settings (form parameters: `ppr`, `blades`, `radius`, `calib`, `deb`, `stop`, `high`, `low`, `buz`, `ser`, `stl`, `tz`, `newpass`) |
| GET | `/api/tests` | Test history |
| POST | `/api/test/start` | `mode=time\|revs`, `value=<seconds or revolutions>`, `name=<optional>` |
| POST | `/api/test/stop` | Stop the running test and store the result |
| POST | `/api/reset?what=peaks\|tests\|all` | Reset records / tests / everything |
| POST | `/api/ack` | Silence the current alarm |
| POST | `/api/save` · `/api/reboot` · `/api/factory` | Save now · reboot · factory reset |
| GET | `/api/export?what=bin\|json\|tests\|rpm\|minutes\|hours` | Downloads (CSV / JSON / binary) |

Example:
```bash
# Count revolutions for 10 seconds, then read the result
curl -X POST -d "mode=time&value=10&name=12V" http://fan-counter.local/api/test/start
sleep 11
curl http://fan-counter.local/api/tests
```

If a password is set, the endpoints that change something use HTTP Basic auth with user **`admin`**.
OTA uses the same password (it is read at boot, so reboot after changing it).

## 🧠 How it works

- A **falling-edge interrupt** on the sensor pin increments a counter. It measures the time since the
  previous pulse with `esp_timer_get_time()` (µs) and ignores pulses closer than the debounce time, so an
  RPM of tens of thousands can be handled without losing pulses, and noise is filtered.
- The main loop moves pulses into per-second (300 s ring), per-minute (24 h) and per-hour (1 year) buckets.
  All counters are 32-bit, so fast fans can't overflow them.
- Instant RPM is `60 / (period × pulses_per_rev)`; the averages come from the per-second ring.
- The dashboard is a single HTML page stored in flash (split into small string chunks for compiler
  compatibility) and drawn with plain Canvas — no external JS libraries, it works offline on the LAN.
- Totals and history are written to LittleFS every 5 minutes (only when something changed) to spare the flash.
  Test history is saved right after each test.

## 🩺 Troubleshooting

| Problem | What to check |
|---|---|
| Fan or ESP32 "dies" at high speed | Power the fan from its own supply; share only GND. Add a 100 nF capacitor on the sensor. The dashboard warns when the last reset was a brown-out. |
| RPM is double / half / wrong | Check the pulses-per-revolution setting and that the module LED toggles once per revolution. Adjust the potentiometer and the distance. |
| RPM jumps around | Noise or multiple triggers per pass: tune the potentiometer, use a clean strip, increase debounce (µs). |
| Dashboard doesn't load | Use the IP from the Serial Monitor instead of `.local`; or join the `Fan-Counter` hotspot. |
| No minute/hour/day charts | The clock isn't synced (no internet). Everything else still works. |
| Compile error about `function ... does not name a type` | Look at the **first** error in the log; make sure the ESP32 core is up to date. |
| Upload works but Wi-Fi never connects | The ESP32 only supports 2.4 GHz networks. |

## 🗂 Repository layout

```
fan_rpm_pro/fan_rpm_pro.ino   the whole firmware (sketch folder name must match the .ino name)
docs/                         screenshots and wiring diagram
.github/workflows/            CI that compiles the sketch
CHANGELOG.md · CONTRIBUTING.md · LICENSE
```

## 🤝 Contributing

Issues and pull requests are welcome — see [CONTRIBUTING.md](CONTRIBUTING.md).

## 📄 License

[MIT](LICENSE)
