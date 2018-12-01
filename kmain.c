#include "syscall.h"
#include "sched.h"

#include <stdlib.h>

#include "util.h"


struct pcb_s thisProcessPCB1;
struct pcb_s* p1;

struct pcb_s thisProcessPCB2;
struct pcb_s* p2;

void
user_process_1()
{
	int v1 = 5;
	while (1)
	{
		v1++;
		sys_yieldto(p2);
	}
}
void
user_process_2()
{
	int v2 = -12;
	while (1)
	{
		v2 -= 2;
		sys_yieldto(p1);
	}
}

int
kmain()
{
	p1 = &thisProcessPCB1;
	p2 = &thisProcessPCB2;

	
	
	sched_init();
	

	
	__asm("cps 0b10000"); //user
	//sys_settime(0x000000100000002);
	
	
    p1->next_instr=(int*) user_process_1;
    p2->next_instr=(int*) user_process_2;
	
	sys_yieldto(p1);


	PANIC();

	return 0;	
}
