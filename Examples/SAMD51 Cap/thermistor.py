import time
import adafruit_thermistor
import board

# Simple script demonstrating the use of the on-board thermistor.
# Source: https://learn.adafruit.com/adafruit-circuit-playground-express/playground-temperature

thermistor = adafruit_thermistor.Thermistor(board.TEMPERATURE, 10000, 10000, 25, 3435)

while True:
    temp_c = thermistor.temperature
    temp_f = thermistor.temperature * 9 / 5 + 32
    print("Temperature is: %f C and %f F" % (temp_c, temp_f))

    time.sleep(0.25)