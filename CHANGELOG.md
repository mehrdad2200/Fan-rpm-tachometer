# Changelog

## 2.0
- Instant RPM from pulse period, 2 s / 10 s / 60 s averages, rev/s, pulses/s, acceleration, stability
- Live RPM gauge and per-second charts that work without NTP/internet
- Timed tests (fixed duration or N revolutions) with persistent history and CSV export
- High/low RPM, sudden-stop and noise alerts, optional buzzer and LED
- Noise guard that detaches the interrupt during sensor noise storms; brown-out reset detection
- Settings page (pulses per revolution, blades, radius, calibration, debounce, time zone, password…)
- Full REST API, OTA updates, JSON/CSV/binary export, device status panel
- Persian/English UI, dark/light theme, big-display mode, keyboard shortcuts
- Dashboard HTML stored as plain string chunks for better compiler compatibility

## 1.0
- Simple counter: debounce in microseconds, 32-bit counters, RPM card and charts
