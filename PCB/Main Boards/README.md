# EAGLE PCB Files

There are two variants of this project. You probably came for variant A1, the SAMD51-based board. A1-02 is marked "WIP" because I'm probably going to tweak the LED's a bit; tried to get clever with a bidirectional 1206 LED, and it works, but it's friendlier with two basic green and amber 0805's. Still totally buildable as-is.

Variant B1 is an experimental low power, low cost version of the cap; it's totally functional, but still I don't recommend building it just yet.

![image](/images/preview.png)

## Sensor Candle

This is a little experiment in making a small passive device for indicating things based on sensor data. It uses a SAMD11, which is a very smol chip with only 16 kilobytes of memory! I'm still hacking on the Arduino core for it, but for now you can use the [MattairTech SAMD/L/C board support package](https://www.mattairtech.com/software/arduino/package_MattairTech_index.json). The core I'm hacking on replaces the 4kB CDC bootloader with a [1kB DFU bootloader](https://github.com/majbthrd/SAMDx1-USB-DFU-Bootloader), which frees up a lot of space for user code.

Sensor candle is simple, but there are also a lot of different options for how to build and power it:

* You can omit `J2`, the 9-pin connector, if you don't plan to use external sensor boards (you still get the on-board accelerometer and RTC).
* Of course you can also omit accelerometer U3 (as well as C9 and C10) to skip that bit of functionality too.
* You can omit `U4`, `R5`, `C7` and `C8` if you don't care about the 1.8 volt power supply (either because you skipped J2, or because you plan to power your sensor boards with VCC via the POWER_OUT solder jumper).
* While this board includes a 3.3 volt regulator (U1) for powering the device over USB or with some battery options, you can omit it completely if you plan to supply the board with a coin cell or a pair of alkaline batteries. In this case you can also omit `R5`, `C1`, `C7`, `D1` and `D2`. In this configuration, when you plug in to USB, you'll get USB data but no USB power.
* Finally, `R12`and `R13` are a voltage divider on the coin cell to monitor battery level. If you aren't using a coin cell (or don't want to lose one channel from the sensor board), you can omit R12 and R13.

In addition, you can choose what LEDs you want to use! Standard 0805 LED's with ~ 2V forward voltage will always work. You can use blue or white LED's as well, but only if you are powering your board with USB or the 4.5V pin (coin cells or a pair of AA's don't quite have the required oomph).

### Power

You can power the board one of three ways. You should ONLY choose one.

* Connect a LiPo battery pack or 3x AA cells to the 4.5V pin. This powers 3.3 volt regulator U1 for a steady 3.3 volts to your project for most of the battery's life. Note that there is no LiPo charging on board so you probably want to solder a [JST-PH cable](https://www.adafruit.com/product/3814) to these pins, so that you can unplug your battery and recharge elsewhere.
* OR connect 2x AA cells to the 3V pin. This provides 3 volts to your project when the batteries are fresh, but that will decline steadily as the batteries discharge.
* OR insert a coin cell into the coin cell holder. This will provide ~ 2.9 volts to your project when the battery is full, but that too will decline as the battery dies. It will hang above 2.7 volts for most of its usable life, but once it declines to 2.6 volts, the end is nigh.

Note that if you are using the 1.8 volt regulator as a reference and power to your sensor board, the SAMD11's ADC really wants the external reference voltage to be no more than the supply voltage minus 0.6 volts. So you really should replace your battery once it gets down to 2.4 volts.

### Peripherals and Possibilities

The 1.8 volt voltage regulator is there so that you can hang out in low power sleep mode most of the time, and only power up the sensor board for an occasional reading (say, an alarm from the RTC or an interrupt from the accelerometer). PA27 is the regulator control pin; it's pulled down by default, so you will have to set it high to power your sensor board.

The real-time clock "Just Works" with [RTCZero](https://github.com/arduino-libraries/RTCZero). Hooray!

For the LIS2DH accelerometer, you can look to most any LIS3DH library for guidance — they're compatible — but most libraries tend to include floating point math that doesn't fit in the SAMD11's program memory. I ended up using [this one](https://github.com/ldab/lis3dh-motion-detection) and replacing all references to `float` with `int`. ¯\\\_(ツ)_/¯

I'm trying to get the [Arduino FlashStorage library](https://github.com/cmaglie/FlashStorage) working with the DFU bootloader. It works with the Mattairtech CDC bootloader, but I think the checksumming of the DFU bootloader fails once I start logging data to the Flash. To be continued.