#include "../include/isr.h"
#include "../kernel/include/kernel_misc.h"



/**
 * Implement the isr_handler. 
 * This takes the structure define in the header
 * that has been placed on the stack by the cpu
 * and can call sub routines from here
 */
extern "C" void isr_handler(registers_t reg_struct)
{
    // test print
    k_printf("\nInterrupt!");

    

}