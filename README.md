# Scale FikaRobot

ESP32-C6 firmware (ESP32-C6-DevKitC-1 board, ESP32-C6-WROOM-1 module) for the FikaRobot project.

## Requirements

```bash
pip install platformio
```

(or `brew install platformio` on a machine with prebuilt Homebrew bottles).

## Usage

```bash
pio run                 # build
pio run -t upload       # build + upload (plug the board in via USB-C)
pio device monitor      # serial monitor (115200)
```

If the upload fails: hold **BOOT**, press **RESET**, release BOOT, then retry.

## Project structure

- `src/` main code
- `include/` headers
- `lib/` local libraries
- `test/` tests
- `platformio.ini` board configuration

## Scale (HX711 + 5 kg load cell)

| HX711 | ESP32-C6 |
|---|---|
| VCC | 3V3 |
| GND | GND |
| DT | GPIO 18 |
| SCK | GPIO 19 |

Load cell to HX711: red E+, black E-, white A-, green A+.

### Calibration

Open the serial monitor (only one monitor can use the port at a time):

```bash
pio device monitor -p /dev/cu.usbmodem142401 --echo
```

Type each command, then press **Enter**:

1. With the platform **empty**: `t` (tare). Wait for `Tare OK`.
2. Place a known weight on the platform, then `c<grams>`, e.g. `c500` for 500 g.
3. The scale now reports grams. The calibration factor is saved to flash and survives reboots.

Other commands: `r` prints the raw value.

If the reading decreases when you press on the load cell, swap the A+ and A- wires on the HX711, then recalibrate.
