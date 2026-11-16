# Scale FikaRobot

Firmware ESP32-C6 (carte ESP32-C6-DevKitC-1, module ESP32-C6-WROOM-1) pour le projet FikaRobot.

## Prerequis

```bash
brew install platformio
```

## Utilisation

```bash
pio run                 # compiler
pio run -t upload       # compiler + televerser (branche la carte en USB-C)
pio device monitor      # moniteur serie (115200)
```

Le programme actuel (`src/main.cpp`) est un test : la LED RGB integree (GPIO8)
alterne rouge, vert, bleu, blanc, eteint.

Si le televersement echoue : maintenir **BOOT**, appuyer sur **RESET**, relacher BOOT, puis relancer.

## Structure

- `src/` code principal
- `include/` en-tetes
- `lib/` bibliotheques locales
- `test/` tests
- `platformio.ini` configuration de la carte
