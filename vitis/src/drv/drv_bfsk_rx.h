#ifndef DRV_BFSK_RX_H
#define DRV_BFSK_RX_H
#include <stdint.h>
typedef struct {
    uint32_t raw;
    uint8_t frame_id;
    uint8_t data;
    uint8_t received_crc;
    uint8_t error;
    uint8_t overrun;
} bfsk_packet_t;
int drv_bfsk_rx_init(void);
/* Returns 1 after copying and acknowledging a packet, 0 if not ready.
 * packet must be non-null; call only after successful initialization.
 * Acknowledgement waits indefinitely, matching the original hardware protocol.
 * Single caller only; not interrupt/thread safe.
 */
int drv_bfsk_rx_poll(bfsk_packet_t *packet);
#endif
