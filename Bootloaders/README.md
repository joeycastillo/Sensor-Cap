# Bootloaders

You can flash the BIN files using a Feather and the Adafruit DAP library. Use pogo pins to connect to the pads on the back side of the board.

Building these requires working with two very different repos, so the instructions are a bit different for each.

## SAMD51 Sensor Cap

1. Clone the [adafruit/uf2-samdx1](https://github.com/adafruit/uf2-samdx1) repository
2. Copy the `sensorcap_m4` directory to the `boards` directory
3. In Terminal, navigate to the uf2-samdx1 root and `make BOARD=sensorcap_m4`

## SAMD11 Sensor Cap

1. Clone the [mattairtech/ArduinoCore-samd](https://github.com/mattairtech/ArduinoCore-samd) repository
2. Copy the `board_definitions_SensorCap_D11D14AS.h` file to the `bootloaders/zero/board_definitions` directory
3. Add a `BOARD_ID_SensorCap_D11D14AS` entry to the `bootloaders/zero/board_definitions.h` file, pointing to the header file
4. In Terminal, navigate to the `bootloaders/zero` folder in ArduinoCore-samd and `make BOARD_ID=SensorCap_D11D14AS`

I'll get these into a forked repo eventually.
