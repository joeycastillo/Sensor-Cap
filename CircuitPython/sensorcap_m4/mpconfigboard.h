#define MICROPY_HW_BOARD_NAME "The Sensor Cap"
#define MICROPY_HW_MCU_NAME "samd51g19"

#define CIRCUITPY_MCU_FAMILY samd51

#define MICROPY_HW_LED_STATUS   (&pin_PA31)
#define MICROPY_HW_NEOPIXEL (&pin_PB22)

// These are pins not to reset.
// QSPI Data pins
#define MICROPY_PORT_A (PORT_PA08 | PORT_PA09 | PORT_PA10 | PORT_PA11)
// VBAT, QSPI CS, QSPI SCK and NeoPixel pin
#define MICROPY_PORT_B (PORT_PB03 | PORT_PB10 | PORT_PB11 | PORT_PB22)
#define MICROPY_PORT_C (0)
#define MICROPY_PORT_D (0)

#define DEFAULT_I2C_BUS_SCL (&pin_PA13)
#define DEFAULT_I2C_BUS_SDA (&pin_PA12)

#define DEFAULT_SPI_BUS_SCK (&pin_PA17)
#define DEFAULT_SPI_BUS_MOSI (&pin_PA19)
#define DEFAULT_SPI_BUS_MISO (&pin_PA18)

#define DEFAULT_UART_BUS_RX (&pin_PA19)
#define DEFAULT_UART_BUS_TX (&pin_PA18)

// USB is always used internally so skip the pin objects for it.
#define IGNORE_PIN_PA24     1
#define IGNORE_PIN_PA25     1
