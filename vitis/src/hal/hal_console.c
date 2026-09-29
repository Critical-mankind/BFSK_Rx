#include "hal_console.h"
#include "xil_printf.h"
void hal_console_write(const char *text)
{
    xil_printf("%s", text);
}
