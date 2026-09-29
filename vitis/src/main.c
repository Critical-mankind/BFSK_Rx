#include "hal/hal_board.h"
#include "drv/drv_bfsk_rx.h"
#include "app/app_csv.h"

int main(void)
{
    bfsk_packet_t packet;
    uint32_t sequence = 0U;
    int status;
    hal_board_init();
    status = drv_bfsk_rx_init();
    if (status != 0) {
        app_csv_init_error(status);
        hal_board_cleanup();
        return 1;
    }
    app_csv_header();
    for (;;) {
        if (drv_bfsk_rx_poll(&packet)) {
            app_csv_packet(sequence, &packet);
            ++sequence;
        }
    }
}
