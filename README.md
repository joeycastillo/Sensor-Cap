# Sensor Cap 9-Pin Spec

A 9-pin JST-SH connector for sensors, inspired by the [Adafruit Monster M4SK](https://www.adafruit.com/product/4343).

This started as a project to mount a temperature sensor on my forehead for continuous temperature monitoring. It's ended up being something broader in nature. Call it a general platform for wearable tech and citizen science, maybe? Also as a side note, I'm hunting for a new name for this project since it's more than a hat now.

![image](/images/board.jpg)

You might ask: why another board? Why not just use a Feather? The answer is that while Feathers are AWESOME, tiny and portable and battery-operated, the main method for attaching wings (board to board pin headers) makes the solution a little more bulky than I would like for something like a hat or a watch. Standards like STEMMA and STEMMA-QT address that somewhat, but STEMMA ports only break out one signal, and STEMMA-QT only supports I²C devices.

This standard breaks out three to five analog signals and I²C. It's far fewer than a Feather header offers, but still, I sense, enough to do some useful stuff! In addition, the connector is small enough that you can keep your sensor boards very small, which is great for wearables, and makes it really cheap to prototype a tiny board at OSH Park.

## Scope

This document describes a connector with a baseline of functionality for designing small PCB's with sensors. Before diving in, some nomenclature: a **main board** hosts whatever microcontroller or processor is driving gadgets on a **sensor board**.

The intent is for different main boards with different goals (i.e low power, machine learning, compact form factor, IOT) to implement this baseline level of functionality on a standard pinout, so that sensor boards know where to expect which functions.

It is not designed for daisy-chaining like STEMMA or Qwiic. When you design your sensor board, you can make use of all of the available pins, secure in the knowledge that you don't need to plan on sharing (except in the case of the I²C pins but, y'know, you can play nice with others there).

Main boards can offer additional functionality on some pins, and this document includes guidelines about what that pinout should look like. This should maximize the amount of compatibility across boards. Still, fundamentally, I imagine the user will either be able to make their sensor package work with the baseline of the spec, or they will choose a main board that works for their project and design their sensor package to match its abilities and constraints.

## Main Board

If possible, all pins should be analog inputs; if not, make sure pins 5, 6 and 9 (A2, A1 and A0) are analog capable. If you have a DAC available, put it on pin 9, A0. All IO pins are 3.3 volt logic.

### Main Board Pinout

![image](/images/pins.png)

1. Power to the sensor board, nominally 3.3 volts, can be lower but no higher.
2. Ground. 
3. Digital input or output D1. (Optional: analog input, or SPI master in/slave out)
4. Digital input or output D0. (Optional: analog input)
5. Analog input A2 or digital in/out. (Optional: SPI master out/slave in)
6. Analog input A1 or digital in/out. (Optional: SPI clock)
7. I²C data.
8. I²C clock.
9. Analog input A0 or digital in/out. (Optional: Analog output)

Why are some pins designated as analog and some pins designated as either digital or analog? Because if you’re in a situation where you have a limited number of pins available, this lets you know to prioritize putting your analog inputs on pins 5, 6 and 9, and your analog output (if available) on pin 9.

The main board **must** provide I²C pull-up resistors on the SCL and SDA lines; there should be no need to include them on a sensor board. The main board may (and probably should) have its own I²C devices share this bus.

The main board should try to offer interrupt capability on all pins except SCL and SDA.

If you're in a severely GPIO constrained situation and cannot offer all 7 GPIO pins, prioritize the I²C, A0, A1 and A2 pins.

## Sensor Boards

The sensor board's 9-pin connector is rotated 180° from the main board's, which means that the numbering on the sensor board is reversed. To connect the sensor board to the main board, use a 9-pin socket-to-socket JST-SH cable like the [the one Adafruit sells](https://www.adafruit.com/product/4350), or one of the following part numbers: [A09SR09SR30K51B](https://www.digikey.com/product-detail/en/jst-sales-america-inc/A09SR09SR30K51B/455-3726-ND/6708500) (2 inch), [A09SR09SR30K102B](https://www.digikey.com/product-detail/en/jst-sales-america-inc/A09SR09SR30K102B/455-3662-ND/9922212) (4 inch), [A09SR09SR30K152B](https://www.digikey.com/product-detail/en/jst-sales-america-inc/A09SR09SR30K152B/455-3722-ND/6708509) (6 inch), [A09SR09SR30K203B](https://www.digikey.com/product-detail/en/jst-sales-america-inc/A09SR09SR30K203B/455-3664-ND/9922214) (8 inch), [A09SR09SR30K254B](https://www.digikey.com/product-detail/en/jst-sales-america-inc/A09SR09SR30K254B/455-3666-ND/9922216) (10 inch) or [A09SR09SR30K305B](https://www.digikey.com/product-detail/en/jst-sales-america-inc/A09SR09SR30K305B/455-3724-ND/6708518) (12-inch).

### Baseline Sensor Board

1. Analog signal A0
2. I²C clock SCL
3. I²C data SDA
4. Analog signal A1
5. Analog signal A2
6. Digital signal D0
7. Digital signal D1
8. Ground
9. Power

Not all main boards need to support all kinds of sensor boards, but this baseline sensor board should basically always work. When designing your sensor board, a few guidelines: 

* If you’re designing a sensor board with both digital and analog signals, prioritize putting your analog signals to the main board on pins 4 and 5, A1 and A2.
* If you require an analog signal from the main board, it will be on pin 9 (A0) if available. Otherwise, you can output a third analog signal to the main board on pin 9.
* Know that pins 6 and 7 (D0 and D1) may be either digital or analog; if you have more analog signals, you can put them there, but you should double check the capabilities of the board you are pairing with.
* If you have some signals that are nice-to-have (like interrupt pins) and others that are absolutely necessary for the board to function (like a chip select line), put your most important signals on A0, A1 and A2 (see above note re: severely constrained main boards).

Those are guidelines, but there's one constraint: your sensor board **must not** treat the SCL and SDA lines as free GPIO pins, since the I²C bus may be shared with devices on the main board.

Beyond the baseline, I can imagine a few kinds of sensor boards: 

### I²C and SPI sensor board

1. SPI Chip Select 1 (CS1)
2. I²C clock (SCL)
3. I²C data (SDA)
4. SPI Clock (SCK)
5. SPI Master Out (MOSI)
6. SPI Chip Select 2 (CS2)
7. SPI Master In (MISO)
8. Ground
9. Power

### I²C sensor board with a TFT or e-paper display

1. Free Pin A0
2. I²C clock (SCL)
3. I²C data (SDA)
4. SPI Clock (SCK)
5. SPI Master Out (MOSI)
6. TFT Chip Select (CS)
7. TFT Data/Command (DC)
8. Ground
9. Power

Side note: this is already basically the MONSTER M4SK left eye! Note though that the MONSTER M4SK uses a Seesaw chip on the I²C bus to manage the TFT’s reset and backlight pins, which is to say you might need to add a GPIO expander on the I²C bus to fully realize this design.

### Fully analog sensor board

1. Analog signal (A0)
2. NC
3. NC
4. Analog signal (A1)
5. Analog signal (A2)
6. Analog signal (A3)
7. Analog signal (A4)
8. Ground
9. Power

## Existing Main Boards

I've designed two of these so far, at two very different ends of the spectrum.

![image](/images/boards.jpg)

### The SAMD51 Sensor Cap Mainboard

This is a zippy ARM Cortex M4 board using the SAMD51G19A. While it is not a Feather, it retains the size and shape of a Feather and the same mounting hole arrangement, so it should be broadly compatible with Feather enclosures. It even has the battery connector in the same spot. 

The board works with CircuitPython! An Arduino core is on its way, I just haven't gotten to it yet.

You might wonder, why use a whole M4 microcontroller for just a handful of signals? It does other things! And has other ports to output things based on your sensor inputs.

#### Connectivity

* One STEMMA port with current and voltage protection (I imagine using this for an external Neopixel strip)
* One STEMMA-QT port for I²C stuff (ideal for adding, say, an OLED display)
* Six pins (a spare SERCOM + two GPIO) broken out with 3.3v power and ground on a 2x4 socket header. The pins are configured as a UART and arranged to match an ESP-01 module for wifi, but I haven't tested this yet.
* Micro-USB port, of course!

#### Features

* 4 MB QSPI Flash for CircuitPython and data logging
* On-board side-view Neopixel for status and color
* Two buttons for pressing, both on interrupt pins
* A small speaker with amplifier on one of the DAC lines, for beeping and speaking
* An on-board thermistor for general temperature sensing
* Battery charging

It also has two options for a real-time clock: 

* You can add a DS3231 Extremely Accurate RTC to get extremely good timekeeping (and a programmable alarm on an interrupt pin)
* But there's also a 32768 Hz crystal for ZeroRTC, and a solder jumper to bring the battery backup power to the SAMD51's VBAT power pin. (need to check on software support for this)

The 9-pin connector supports analog signals on all pins, and the second DAC is on pin A0. Unfortunately due to pin muxing constraints, it does not support hardware SPI on pins A1, A2 and D1; you'll have to bitbang it.

Anyway! Wearable tech is an obvious use case for this board, and the SAMD51 is powerful enough to run, like, TensorFlow Lite models on the sensor data you bring in. It's a thinking cap!

### The SAMD11 Minimalist Sensor Cap

This one I'm still iterating on. The idea was to make something *incredibly* cheap and low-power for data acquisition, and the SAMD11D14AS fit the bill. Unfortunately, on initial testing, I think the coin cell I chose is too small to last more than a day or two, even with low power modes.

I think this can still work for intermittent data logging; if the device spends most of its time in shutdown mode, and only wakes up for measurement when the user hits the reset button, it might work! I need to do more testing. Either way, I might redesign this with either a bigger coin cell or contacts for an alkaline battery pack.

You can play with this board using the [MattairTech SAMD11 Core](https://github.com/mattairtech/ArduinoCore-samd), but truth be told the Arduino core is so big, it's hard to keep even a kilobyte free at the end for data logging. There's a demo sketch in the repository that does work, but I expect to have to learn to write firmware from scratch to help this board reach its full potential.

#### Connectivity

* USB-A port on the PCB. Depending on the PCB thickness you may have to add a shim underneath for good contact. 

#### Features

* On-board thermistor for temperature sensing
* LIS2DH ultra low power accelerometer with two interrupt pins broken out
* 32768 Hz crystal for the real-time clock

There is no SPI Flash chip here, but you can log data to the EEPROM emulation area of the SAMD11, which should give you from one to several kilobytes of space for data.

The use case for this board is low-cost, low-power data acquisition. I'd love to get the power consumption down to the point where it can sleep most of the time, and then wake up once an hour to gather, like, environmental conditions or soil measurements. Or it could be a DIY contact thermometer; when woken up it could get ambient temperature, then flash the LED to indicate it's ready for a forehead measurement, then log the timestamped data (and blink if fever was detected).

## Existing Sensor Boards

I've thrown a lot of things at the wall so far, but the most useful ones are: 

* Temperature, Accelerometer and Speaker
* Pulse Oximetry Test Board
* Sensor Board Breakout (useful for prototyping new sensor boards!)

Future Plans? Who knows! I'm stoked at the possibilities though.
