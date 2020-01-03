/**
 * isr.h
 * refines the structure present in the stack when an interrupt 
 * is executed. Allows the kernel to acces those registers
 */

#ifndef __ISR_H
#define __ISR_H

#include "types.h"

// struct to define the structure present on the stack
// contains all the pushed registers, including the
// interrupt number and error code.
typedef struct regs
{
    
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, edx, ecx, eax;
    uint32_t i_num, e_code;
    uint32_t eip, cs, eflags, useresp, ss;

} registers_t;

#endif /* isr.h */