#include <inttypes.h>

void sys_reboot();
void sys_nop();
void sys_settime(uint64_t date_ms);
void sys_yieldto();

int* sp_svc;
