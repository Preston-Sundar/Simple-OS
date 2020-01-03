
/* Main kernel code that is called once the stack space has been setup
 * Used to set upt the GDT, IDT, hardwre and being launching the OS
 *
 *NOTES: 
 * when compiling this code, tell compiler that there isnt any os to make calls to
 * and that ther is no glibc. this is done in makefile.
 * 
 * Use the datatypes universalized in types.h
 * 
 * 
 * 
 * 
 */

#include "include/types.h"
#include "include/io.h"
#include "kernel/include/kernel_misc.h"
#include "include/descriptor_table.h"


/* get the pointers to the contructors, filled in by linker 
 * between the pointers start_ctors and end_ctors lies function pointers 
 * placed there by the linker, execute these functions. 
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

/*   main function of our kernal that is called from loader.s
 *   accepts the pointer to multiboot and the magic code (no particular reason to take the magic number)
 * 
 *   use extern C to prevent gcc from changing the name
 *   @param void* multiboot_struct
 *   @param uint32_t magic_num
 */
extern "C" void kernel_main(void *multiboot_struct, uint32_t magic_num)
{

    // init the screen
    k_init_screen();

    // print some stuff
    for (uint8_t i = 0; i < 3; i++)
    {
        k_printf_skeleton_message("Hi there!", i);
    }

    k_printf_skeleton_message("setting GDT", PRINT_STATE);
    
    // create the DT
    DescTable d;

    k_printf_skeleton_message("Done with GDT", PRINT_STATE);


    k_printf_skeleton_message("forcing INT 3", PRINT_STATE);

    
    
    asm volatile ("int $0x3");
    asm volatile ("int $0x4");


    // infinite loop
    while (1)
        ;
}