#include <stdint.h>
#include "stdio.h"
#include "memory.h"
#include <hal/hal.h>
#include <arch/i686/irq.h>
#include <debug.h>
#include <boot/bootparams.h>
#include<stdbool.h>

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
    
    log_debug("Main", "Boot device: %x", bootParams->BootDevice);
    log_debug("Main", "Memory region count: %d", bootParams->Memory.RegionCount);
    for (int i = 0; i < bootParams->Memory.RegionCount; i++) 
    {
        log_debug("Main", "MEM: start=0x%llx length=0x%llx type=%x", 
            bootParams->Memory.Regions[i].Begin,
            bootParams->Memory.Regions[i].Length,
            bootParams->Memory.Regions[i].Type);
            printf("Main,MEM: start=0x%llx length=0x%llx type=%x \n", 
            bootParams->Memory.Regions[i].Begin,
            bootParams->Memory.Regions[i].Length,
            bootParams->Memory.Regions[i].Type);  
            memcap=memcap+(long long int)bootParams->Memory.Regions[i].Length; 
            }


    

    log_info("Main", "This is an info msg!");
    log_warn("Main", "This is a warning msg!");
    log_err("Main", "This is an error msg!");
    log_crit("Main", "This is a critical msg!");
    printf("Nanite\n");
    printf("This operating system is under construction.\n");
    //i686_IRQ_RegisterHandler(0, timer);
    uint32_t LoMem=bootParams->Memory.MemSizeLo;
    uint32_t HiMem=bootParams->Memory.MemSizeHi;
    uint32_t NetMem=1024+HiMem*64+LoMem;
    printf("\nSummem=%d MB\nLoMem Size received from bootloader= %ld KB\nHiMem Size Received from bootloader= %ld KB\nNet Memory Detected= %ld MB",memcap/1000000,LoMem,HiMem*64,NetMem/1000);
    /*unsigned long long int i=0;
    while(true){

        printf("\n%d",i);
        i++;
    }*/
    //crash_me();

end:
    for (;;);
}
