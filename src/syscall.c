#include <inttypes.h>
#include "hw.h"

#include "syscall.h"
#include "sched.h"

#include <string.h>






void
sys_reboot()
{
    __asm("mov r0, #1");
    __asm("SWI #0");   
}

void
sys_nop()
{
    __asm("mov r0, #2");
    __asm("SWI #0");   
}

void
sys_settime(uint64_t date_ms)
{
    
    uint32_t lowbytes = date_ms;
    uint32_t highbytes = (date_ms >> 32); 

    __asm("mov r1, %0" : "=r"(lowbytes): :"r1", "r2");
    __asm("mov r2, %0" : "=r"(highbytes): :"r1", "r2");

    __asm("mov r0, #3");
    __asm("SWI #0");   
}
   


void
do_sys_reboot(){
    __asm("cps 0b11111"); //system
    __asm("b 0x8000");
}

void
do_sys_nop(){
}

void
do_sys_settime(){
    __asm("ldmfd sp!, {r0-r12}");
    uint32_t lowbytes = *(sp_svc + 2);
    uint32_t highbytes =  *(sp_svc + 1);; 
    
    uint64_t date = ((uint64_t) highbytes << 32) | lowbytes;
    set_date_ms(date);
}





void
__attribute__((naked)) 
C_swi_handler(void)
{
    __asm("stmfd sp!, {r0-r12,lr}");

    __asm("mov %0, sp" : "=r"(sp_svc));
    
    int call_number;
    __asm("mov %0, r0" : "=r"(call_number));

    switch(call_number){
        case 1:
            do_sys_reboot();
            break;
        case 2:
            do_sys_nop();
            break;
        case 3:
            do_sys_settime();
            break;
        case 4:
            do_sys_yieldto();
            break;

        default:
            break;
    }
    __asm("ldmfd sp!, {r0-r12,pc}^");

}