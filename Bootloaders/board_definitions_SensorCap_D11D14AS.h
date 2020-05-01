/*
  Copyright (c) 2017 MattairTech LLC. All right reserved.
  Copyright (c) 2015 Arduino LLC.  All right reserved.
  Copyright (c) 2015 Atmel Corporation/Thibaut VIARD.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _BOARD_DEFINITIONS_H_
#define _BOARD_DEFINITIONS_H_

#include <sam.h>

/* The SAM-BA interface, which is used with both USB CDC and UART (TTL
 * serial), can operate in either binary (default) or terminal mode. If
 * TERMINAL_MODE_ENABLED is defined, additional terminal handling code
 * (add prompt, add \n\r to EOL, number formatting, etc.) will be compiled
 * in. To switch to terminal mode, type 'T#' (you should then see a prompt).
 * Then, type 'V#' to show version information. See README.md for more commands.
 * Size: ~228B. Enabled by default. Disable with 4KB bootloader.
 */
//#define TERMINAL_MODE_ENABLED

#define SAM_BA_INTERFACE              SAM_BA_USBCDC_ONLY

/* If SAM_BA_INTERFACE_USE_PIN is defined, then the associated pin controls which
 * SAM-BA interface is used (if SAM_BA_BOTH_INTERFACES is defined). If only one
 * interface is used, then the pin acts as an enable. In both cases, the value of
 * SAM_BA_INTERFACE_PIN_POLARITY controls the polarity, with values of
 * PIN_POLARITY_ACTIVE_LOW or PIN_POLARITY_ACTIVE_HIGH for a single interface, and
 * PIN_POLARITY_USBCDC_LOW or PIN_POLARITY_USBCDC_HIGH when both interfaces are
 * enabled. PORT can be 0 (Port A) or 1 (Port B). Config can be INPUT, INPUT_PULLUP,
 * or INPUT_PULLDOWN.The USB/UART peripheral and pins will not be setup if the
 * device is not selected/enabled. If no interface is selected by the pin, the LED
 * will blink with status code LED_STATUS_NO_SAM_BA_INTERFACE.
 * Size: ~100B. By default, SAM_BA_INTERFACE_USE_PIN is not defined.
 */
//#define SAM_BA_INTERFACE_USE_PIN
#define SAM_BA_INTERFACE_PIN_POLARITY      PIN_POLARITY_ACTIVE_LOW
#define SAM_BA_INTERFACE_PIN_PORT          (0)
#define SAM_BA_INTERFACE_PIN_PIN           (5)
#define SAM_BA_INTERFACE_PIN_CONFIG        INPUT_PULLUP

/* If ARDUINO_EXTENDED_CAPABILITIES is defined and set to 1, 3 additional commands
 * will become available which will speed up programming when using the Arduino
 * IDE or the bossac tool standalone. Set to 0 with 4KB bootloaders.
 * Size: ~904B. This is defined and set to 1 by default (except with 4KB).
 */
#define ARDUINO_EXTENDED_CAPABILITIES   0

/* The clock source must be chosen by setting CLOCKCONFIG_CLOCK_SOURCE to
 * CLOCKCONFIG_32768HZ_CRYSTAL, CLOCKCONFIG_HS_CRYSTAL, CLOCKCONFIG_INTERNAL,
 * or CLOCKCONFIG_INTERNAL_USB. If CLOCKCONFIG_32768HZ_CRYSTAL or
 * CLOCKCONFIG_HS_CRYSTAL is defined, then the PLL will be used. If
 * CLOCKCONFIG_HS_CRYSTAL is defined, then HS_CRYSTAL_FREQUENCY_HERTZ must
 * also be defined with the crystal frequency in Hertz. CLOCKCONFIG_INTERNAL
 * uses the DFLL in open-loop mode, except with the C21 which lacks a DFLL, so
 * the internal 48MHz RC oscillator is used instead. CLOCKCONFIG_INTERNAL_USB
 * can be defined for the D21, D11, L21, or D51. It will also use the DFLL in
 * open-loop mode, except when connected to a USB port with data lines (and
 * not suspended), where it will calibrate against the USB SOF signal.
 */
#ifndef CLOCKCONFIG_CLOCK_SOURCE
#define CLOCKCONFIG_CLOCK_SOURCE	CLOCKCONFIG_32768HZ_CRYSTAL
#endif

/* If CLOCKCONFIG_HS_CRYSTAL is defined, then HS_CRYSTAL_FREQUENCY_HERTZ
 * must also be defined with the external crystal frequency in Hertz.
 */
#define HS_CRYSTAL_FREQUENCY_HERTZ	16000000UL

/* If the PLL is used (CLOCKCONFIG_32768HZ_CRYSTAL, or CLOCKCONFIG_HS_CRYSTAL
 * defined), then PLL_FRACTIONAL_ENABLED can be defined, which will result in
 * a more accurate 48MHz output frequency at the expense of increased jitter.
 */
//#define PLL_FRACTIONAL_ENABLED

/* If both PLL_FAST_STARTUP and CLOCKCONFIG_HS_CRYSTAL are defined, the crystal
 * will be divided down to 1MHz - 2MHz, rather than 32KHz - 64KHz, before being
 * multiplied by the PLL. This will result in a faster lock time for the PLL,
 * however, it will also result in a less accurate PLL output frequency if the
 * crystal is not divisible (without remainder) by 1MHz. In this case, define
 * PLL_FRACTIONAL_ENABLED as well.
 */
//#define PLL_FAST_STARTUP

/* Master clock frequency (also Fcpu frequency). With the D51,
 * this can be either 120000000ul or 48000000ul. See README.md.
 */
#define VARIANT_MCK                       (48000000ul)

/* The fine calibration value for DFLL open-loop mode is defined here.
 * The coarse calibration value is loaded from NVM OTP (factory calibration values).
 */
#define NVM_SW_CALIB_DFLL48M_FINE_VAL     (512)

/* If USB_VENDOR_STRINGS_ENABLED is defined, then STRING_MANUFACTURER and
 * STRING_PRODUCT will be sent to the host.
 * Size: ~228B. By default, USB_VENDOR_STRINGS_ENABLED is defined (including 4KB).
 */
#define USB_VENDOR_STRINGS_ENABLED
#define STRING_MANUFACTURER "Oddly Specific Objects"
#define STRING_PRODUCT "Sensor Cap B1-01"

/* If USB CDC is used, then the USB vendor ID (VID) and product ID (PID) must be set. */
#define USB_VID_HIGH   0x23
#define USB_VID_LOW    0x9A
#define USB_PID_HIGH   0x80
#define USB_PID_LOW    0x0B

/* BOOT_USART_SERCOM_INSTANCE must be a single digit representing the SERCOM number.
 * See board_driver_serial.h for BOOT_USART_PAD_SETTINGS values. When setting
 * BOOT_USART_PADx defines, consult the appropriate header file from CMSIS-Atmel (ie:
 * ~/arduino15/packages/MattairTech_Arduino/tools/CMSIS-Atmel/1.0.0-mattairtech-2/
 * CMSIS/Device/ATMEL/sam<d21|d51|c21|l21|d11>/include/<YOUR_CHIP>.h). Use PINMUX_UNUSED
 * if not used. By default, this interface is not enabled (except with the C21).
 */
#define BOOT_USART_SERCOM_INSTANCE        0
#define BOOT_USART_PAD_SETTINGS           UART_RX_PAD3_TX_PAD2
#define BOOT_USART_PAD3                   PINMUX_PA05C_SERCOM0_PAD3
#define BOOT_USART_PAD2                   PINMUX_PA04C_SERCOM0_PAD2
#define BOOT_USART_PAD1                   PINMUX_UNUSED
#define BOOT_USART_PAD0                   PINMUX_UNUSED

/*
 * If BOOT_DOUBLE_TAP_ENABLED is defined the bootloader is started by quickly
 * tapping two times on the reset button (within 1/2 second).
 * Size: ~96B. Enabled by default.
 */
#define BOOT_DOUBLE_TAP_ENABLED

/*
 * If BOOT_LOAD_PIN_ENABLED is defined, the bootloader is started if the selected
 * pin is active after reset. There is a 10ms delay before testing the pin to
 * allow time for debouncing capacitors to charge (ie: button use). PORT can be 0
 * (Port A) or 1 (Port B). Polarity can be PIN_POLARITY_ACTIVE_LOW or
 * PIN_POLARITY_ACTIVE_HIGH. Config can be INPUT, INPUT_PULLUP, or INPUT_PULLDOWN.
 * Size: ~84B. Disabled by default.
 */
//#define BOOT_LOAD_PIN_ENABLED
#define BOOT_LOAD_PIN_POLARITY            PIN_POLARITY_ACTIVE_LOW
#define BOOT_LOAD_PIN_PORT                (0)
#define BOOT_LOAD_PIN                     (15)
#define BOOT_LOAD_PIN_CONFIG              INPUT_PULLUP

/*
 * If BOARD_LED_FADE_ENABLED is defined, then the main LED produces a PWM fade in an
 * "M-wave" pattern, otherwise, it simply turns on (if enabled). When the SD bootloader
 * is running, the fading will be twice as fast as the SAM-BA interface (USB CDC or UART).
 * Size: ~160B. Enabled by default.
 */
#define BOARD_LED_FADE_ENABLED

/*
 * If the LED PORT is defined, then the LED on the associated pin is enabled.
 * Polarity can be either LED_POLARITY_HIGH_ON or LED_POLARITY_LOW_ON.
 * By default, only BOARD_LED is enabled.
 */
#define BOARD_LED_PORT                    (0)
#define BOARD_LED_PIN                     (31)
#define BOARD_LED_POLARITY    LED_POLARITY_HIGH_ON

//#define BOARD_LEDRX_PORT                  (0)
//#define BOARD_LEDRX_PIN                   (16)
//#define BOARD_LEDRX_POLARITY	LED_POLARITY_HIGH_ON

//#define BOARD_LEDTX_PORT                  (0)
//#define BOARD_LEDTX_PIN                   (16)
//#define BOARD_LEDTX_POLARITY	LED_POLARITY_HIGH_ON

#endif // _BOARD_DEFINITIONS_H_
