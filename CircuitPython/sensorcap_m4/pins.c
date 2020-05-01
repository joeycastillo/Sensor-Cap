#include "shared-bindings/board/__init__.h"

#include "boards/board.h"

STATIC const mp_rom_map_elem_t board_global_dict_table[] = {
    // 9-pin connector
    { MP_OBJ_NEW_QSTR(MP_QSTR_A0),  MP_ROM_PTR(&pin_PA05) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_A1),  MP_ROM_PTR(&pin_PA07) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_A2),  MP_ROM_PTR(&pin_PA06) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_A3),  MP_ROM_PTR(&pin_PB09) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_A4),  MP_ROM_PTR(&pin_PA04) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_D0),  MP_ROM_PTR(&pin_PB09) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_D1),  MP_ROM_PTR(&pin_PA04) },
    
    // I2C
    { MP_OBJ_NEW_QSTR(MP_QSTR_SDA),  MP_ROM_PTR(&pin_PA12) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_SCL),  MP_ROM_PTR(&pin_PA13) },

    // Blinkenlights
    { MP_OBJ_NEW_QSTR(MP_QSTR_LED),  MP_ROM_PTR(&pin_PA31) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_NEOPIXEL),  MP_ROM_PTR(&pin_PB22) },

    // On-board audio
    { MP_ROM_QSTR(MP_QSTR_SPEAKER), MP_ROM_PTR(&pin_PA02) },
    { MP_ROM_QSTR(MP_QSTR_SPEAKER_ENABLE), MP_ROM_PTR(&pin_PB23) },
    
    // On-board sensors
    { MP_ROM_QSTR(MP_QSTR_TEMPERATURE), MP_ROM_PTR(&pin_PB02) },
    { MP_ROM_QSTR(MP_QSTR_VOLTAGE_MONITOR), MP_ROM_PTR(&pin_PB08) },
    { MP_ROM_QSTR(MP_QSTR_BATTERY), MP_ROM_PTR(&pin_PB08) },
    { MP_ROM_QSTR(MP_QSTR_RTC_INTERRUPT), MP_ROM_PTR(&pin_PA15) },

    // On-board Buttons
    { MP_OBJ_NEW_QSTR(MP_QSTR_BUTTON_0),  MP_ROM_PTR(&pin_PA27) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_BUTTON_1),  MP_ROM_PTR(&pin_PA30) },

    // Ports and accessories
    { MP_ROM_QSTR(MP_QSTR_STEMMA), MP_ROM_PTR(&pin_PA14) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ACCESSORY_IO_0),  MP_ROM_PTR(&pin_PA20) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ACCESSORY_IO_1),  MP_ROM_PTR(&pin_PA19) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ACCESSORY_ENABLE),  MP_ROM_PTR(&pin_PA18) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_ACCESSORY_RESET),  MP_ROM_PTR(&pin_PA21) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_USBID),  MP_ROM_PTR(&pin_PA23) },

    // SPI — this is on the 2x4 pin header as an alternative to the UART. 
    // No hardware SPI on the 9-pin!
    { MP_OBJ_NEW_QSTR(MP_QSTR_SCK),  MP_ROM_PTR(&pin_PA17) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_MISO),  MP_ROM_PTR(&pin_PA18) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_MOSI),  MP_ROM_PTR(&pin_PA19) },

    // UART
    { MP_OBJ_NEW_QSTR(MP_QSTR_RX),  MP_ROM_PTR(&pin_PA19) },
    { MP_OBJ_NEW_QSTR(MP_QSTR_TX),  MP_ROM_PTR(&pin_PA18) },

    { MP_ROM_QSTR(MP_QSTR_I2C), MP_ROM_PTR(&board_i2c_obj) },
    { MP_ROM_QSTR(MP_QSTR_SPI), MP_ROM_PTR(&board_spi_obj) },
    { MP_ROM_QSTR(MP_QSTR_UART), MP_ROM_PTR(&board_uart_obj) },
};
MP_DEFINE_CONST_DICT(board_module_globals, board_global_dict_table);
