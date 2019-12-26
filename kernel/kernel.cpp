/*NOTES: 
 * when compiling this code, tell compiler that there isnt any os to make calls to
 * and that ther is no glibc. this is done in makefile.
 * 
 * Use the datatypes universalized in types.h
 * 
 * 
 * 
 * 
 */

#include "types.h"
#include "global_desc_table.h"
#include "sys_interrupts.h"
#include "misc.h"


/* get the pointers to the contructors, filled in by linker 
 * between the pointers start_ctors and end_ctors lies function pointers 
 * placed there by the linker, execute these functions. 
 *
 */
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
    {
        // call the function
        (*i)();
    }
}


void delay(){
    for (uint64_t i = 0; i < 99999999; i++)
    {
        __asm__("nop");
    }
    
}

 
//  //make it shutup
//  static void nosound() {
//  	uint8_t tmp = inb(0x61) & 0xFC;
 
//  	outb(0x61, tmp);
//  }

/*   main function of our kernal 
 *   accepts the pointer to multiboot and the magic code (no particular reason to take the magic number)
 * 
 *      use extern C to prevent gcc from changing the name
 */

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number)
{

    // can't use the standard printf as we're outside an OS currently
    // we don't have access to glibc so we write our own printf
    //printf_boot_message("kernel.....\n");

    // create the global descriptor table
    GlobalDescriptorTable gdt;

    // create the interrupt descriptor table
    InterruptHandler interrupt_handler(&gdt);


    // tell the cpu to use it
    interrupt_handler.set_active();


    // clear and set up skeleton
    init_screen();

    // random rebug print
    // /printf_boot_message("sti called\n");

    printf_skeleton_message("kernel ready", PRINT_STATE);


    // kernal never really stops, inf loop
    //uint64_t i = 0;

    uint8_t flag = 0;

    printf_skeleton_message("Kernel Loop ", PRINT_STATE);

    while (1)
    {
        
        // flag = ~flag;

        // if (flag == 0)
        // {
        //     printf_skeleton_message("Inside Inf Loop", PRINT_ERROR);        
        //     printf_skeleton_message("Waiting........", PRINT_MESSAGE);     
        // } else {
        //     printf_skeleton_message("Waiting........", PRINT_ERROR);
        //     printf_skeleton_message("Inside Inf Loop", PRINT_MESSAGE);   
        // }
        
    
        // delay();
    }



}

