#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <arch/i686/irq.h>
#include <debug.h>
#include <boot/bootparams.h>
#include<stdbool.h>
#include"mmngr_phys.h"

extern void _init();



void crash_me();

void timer(Registers* regs)
{
    printf(".");
}

void start(BootParams* bootParams)
{   
    // call global constructors
    _init();
    

    uint32_t memcap=0;

    HAL_Initialize();
  

    extern long phys;
    extern long end;
    uint32_t LoMem=bootParams->Memory.MemSizeLo;
    uint32_t HiMem=bootParams->Memory.MemSizeHi;
    uint32_t NetMem=1024+HiMem*64+LoMem;

    bootParams->kernStart=(uint32_t)&phys;
    bootParams->kernEnd=(uint32_t)&end;

    log_info("Main","\nKernel start: 0x%x \nKernel End: 0x%x \n",bootParams->kernStart,bootParams->kernEnd);

    pmmngr_init (NetMem, bootParams->kernEnd);


    log_debug("Main", "Boot device: %x", bootParams->BootDevice);
    log_debug("Main", "Memory region count: %d", bootParams->Memory.RegionCount);

    printf("Kernel Entry:0x%x \nExit: 0x%x\n In uint8_t: 0x%x\n",bootParams->kernStart,bootParams->kernEnd,(uint8_t)bootParams->kernEnd);

    for (int i = 0; i < bootParams->Memory.RegionCount; i++) 
    {
        log_debug("Main", "MEM: start=0x%llx length=0x%llx type=%x", 
            bootParams->Memory.Regions[i].Begin,
            bootParams->Memory.Regions[i].Length,
            bootParams->Memory.Regions[i].Type);
            printf("Main,MEM: start=0x%llx length=0x%llx type=%x ,End: 0x%llx\n", 
            bootParams->Memory.Regions[i].Begin,
            bootParams->Memory.Regions[i].Length,
            bootParams->Memory.Regions[i].Type,
            bootParams->Memory.Regions[i].Begin + bootParams->Memory.Regions[i].Length);  

            memcap=memcap+(long int)bootParams->Memory.Regions[i].Length; 
            if (bootParams->Memory.Regions[i].Type==1){
			pmmngr_init_region (bootParams->Memory.Regions[i].Begin, bootParams->Memory.Regions[i].Length);}
    }
    pmmngr_deinit_region(0x100000, bootParams->kernEnd - bootParams->kernStart);
    printf ("\npmm regions initialized: %i allocation blocks; used or reserved blocks: %i\nfree blocks: %i\n",
	pmmngr_get_block_count (),  pmmngr_get_use_block_count (), pmmngr_get_free_block_count () );


    uint32_t* p = (uint32_t*)pmmngr_alloc_block();
	printf ("\np allocated at 0x%x", p);

    uint32_t* p2=(uint32_t*)pmmngr_alloc_blocks(2);
    printf("\np2 allocated at 0x%x",p2);

    pmmngr_free_block(p);
    p=(uint32_t*)pmmngr_alloc_block();
    printf ("\np re-allocated at 0x%x", p);

    printf("\nNanite\n");
    printf("This operating system is under construction.\n");
    //i686_IRQ_RegisterHandler(0, timer);

   

end:
    for (;;);
}
