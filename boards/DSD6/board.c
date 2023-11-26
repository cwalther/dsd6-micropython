#include "nrf.h"
#include "py/obj.h"

#define DFU_MAGIC_SERIAL_ONLY_RESET   0x4e
#define DFU_MAGIC_OTA_RESET           0xA8

void DSD6_enter_bootloader(size_t n_args, const mp_obj_t *args) {
    __disable_irq();
    NRF_POWER->GPREGRET = (n_args == 0 || !mp_obj_is_true(args[0])) ? DFU_MAGIC_SERIAL_ONLY_RESET : DFU_MAGIC_OTA_RESET;
    NVIC_SystemReset();
}
