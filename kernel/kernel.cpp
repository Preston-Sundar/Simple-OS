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

/*   main function of our kernal 
 *   accepts the pointer to multiboot and the magic code (no particular reason to take the magic number)
 * 
 *      use extern C to prevent gcc from changing the name
 */

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number)
{

    // can't use the standard printf as we're outside an OS currently
    // we don't have access to glibc so we write our own printf
    printf_boot_message("Hello, WELCOME TO PoopOS's kernel.....so what now?\n");

    GlobalDescriptorTable gdt;

    asm("sti");

    printf_boot_message("sti called\n");

    /* kernal never really stops, inf loop */
    while (1)
        ;
}
