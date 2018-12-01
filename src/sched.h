#include <inttypes.h>

void sched_init();
void sys_yieldto();
void do_sys_yieldto();



typedef struct pcb_s{
    int all_reg[14];
    int * next_instr;
}pcb_s;