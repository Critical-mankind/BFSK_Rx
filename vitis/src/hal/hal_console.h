#ifndef HAL_CONSOLE_H
#define HAL_CONSOLE_H
/* The BSP selects the physical stdout UART. */
void hal_console_write(const char *text);
#endif
