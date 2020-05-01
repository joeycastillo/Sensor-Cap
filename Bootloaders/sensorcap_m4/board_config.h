#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define CRYSTALLESS    0

#define VENDOR_NAME "Oddly Specific Objects"
#define PRODUCT_NAME "The Sensor Cap"
#define VOLUME_LABEL "CAPBOOT"
#define INDEX_URL "https://github.com/joeycastillo/"
#define BOARD_ID "OSO-SCAP-A1-01"

#define USB_VID 0x239A
#define USB_PID 0x007D

#define LED_PIN PIN_PA31

#define BOARD_NEOPIXEL_PIN PIN_PB22
#define BOARD_NEOPIXEL_COUNT 1


#define BOOT_USART_MODULE                 SERCOM3
#define BOOT_USART_MASK                   APBBMASK
#define BOOT_USART_BUS_CLOCK_INDEX        MCLK_APBBMASK_SERCOM3
#define BOOT_USART_PAD_SETTINGS           UART_RX_PAD3_TX_PAD2
#define BOOT_USART_PAD3                   PINMUX_PA19D_SERCOM3_PAD3
#define BOOT_USART_PAD2                   PINMUX_PA18D_SERCOM3_PAD2
#define BOOT_USART_PAD1                   PINMUX_UNUSED
#define BOOT_USART_PAD0                   PINMUX_UNUSED
#define BOOT_GCLK_ID_CORE                 SERCOM3_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW                 SERCOM3_GCLK_ID_SLOW

#endif
