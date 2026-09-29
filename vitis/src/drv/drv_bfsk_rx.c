#include "drv_bfsk_rx.h"
#include "../hal/hal_gpio.h"

#define READY_MASK   UINT32_C(0x80000000)
#define ERROR_MASK   UINT32_C(0x40000000)
#define OVERRUN_MASK UINT32_C(0x20000000)

int drv_bfsk_rx_init(void) { return hal_gpio_init(); }

int drv_bfsk_rx_poll(bfsk_packet_t *packet)
{
    uint32_t word = hal_gpio_read();
    if ((word & READY_MASK) == 0U) return 0;
    packet->raw = word;
    packet->frame_id = (uint8_t)(word >> 16);
    packet->data = (uint8_t)(word >> 8);
    packet->received_crc = (uint8_t)word;
    packet->error = (uint8_t)((word & ERROR_MASK) != 0U);
    packet->overrun = (uint8_t)((word & OVERRUN_MASK) != 0U);

    hal_gpio_set_clear(1);
    while ((hal_gpio_read() & READY_MASK) != 0U) {
        /* Hold clear high until rx_latch drops ready. */
    }
    hal_gpio_set_clear(0);
    return 1;
}
