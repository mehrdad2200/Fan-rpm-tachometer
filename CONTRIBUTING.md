# Contributing

Thanks for helping! This is a single-sketch Arduino project, so contributing is simple.

## Bugs and ideas
Open an issue and include:
- Board and ESP32 Arduino core version
- Sensor module and how it is mounted (strips on the fan, distance)
- What you expected and what happened (Serial Monitor output helps; enable *Serial log* in settings)
- The **first** compiler error, if it is a build problem

## Pull requests
1. Fork the repository and create a branch.
2. Keep the sketch dependency-free (only libraries bundled with the ESP32 core).
3. The sketch folder name must stay equal to the `.ino` name (`fan_rpm_pro`).
4. Never commit real Wi-Fi credentials; keep the `YOUR_WIFI_NAME` / `YOUR_WIFI_PASSWORD` placeholders.
5. If you touch the dashboard, check it in both languages and both themes, and on a phone-width screen.
6. Update `README.md`, `README.fa.md` and `CHANGELOG.md` when behaviour changes.
7. CI compiles the sketch for `esp32:esp32:esp32s3`; make sure it passes.

## Style
- Interrupt handlers stay tiny and use `IRAM_ATTR`; do heavy work in `loop()`.
- Counters are 32-bit; avoid anything that can overflow with a fast fan.
