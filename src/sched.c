#include <inttypes.h>
#include "hw.h"

#include "syscall.h"
#include "sched.h"

#include <string.h>

struct pcb_s* current_process;
struct pcb_s kmain_process;

void 
sched_init(){
    current_process=&kmain_process;
}
void
sys_yieldto(struct pcb_s* dest){
    


    __asm("mov r1, %0" : "=r"(dest): :"r1");
    
    __asm("mov r0, #4");
    __asm("SWI #0");     
}

void
do_sys_yieldto(){

    struct pcb_s* dest = (struct pcb_s*) *(sp_svc+1);

    for(int i=0;i<13;i++){
        current_process->all_reg[i]=*(sp_svc+i);
    }   
    current_process->next_instr=(int *) *(sp_svc+13);

    current_process=dest;

    for(int i=0;i<13;i++){
        *(sp_svc+i)=current_process->all_reg[i];
    }  

    *(sp_svc+13)=(int)current_process->next_instr;


};