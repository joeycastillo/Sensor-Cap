# Sensor Cap CircuitPython Support

This really couldn't be simpler: 

1. Follow [Adafruit's instructions](https://learn.adafruit.com/building-circuitpython/build-circuitpython) to fetch the code and build mpy-cross.
2. Copy the `sensorcap_m4` directory to the `ports/atmel-samd` directory
3. In Terminal, navigate to the `ports/atmel-samd` directory and `make BOARD=sensorcap_m4`

Double tap reset to go into UF2 bootloader mode, then drag the uf2 file over!