# define the interrupts here. Use macros to generate all the isrs
# This file is used to push the interrupt functions onto the stack. 
# This is needed if we're going to call these functions later and we need them on 
# the stack and ready to go.

.section .text

# the main isr handler is extern
.extern isr_handler

# need to place the jump points to where our interrupt functions are in memory
.macro ISR_NO_EXCEPTION_CODE i_num
    .global isr\i_num
    
    isr\i_num:
        cli              # disable interrupts
        push $0         # push dummy error code
        push $\i_num    # push the interrupt number
        jmp isr_common   # jump to common isr

.endm



# need to place the jump points to where our interrupt functions are in memory
.macro ISR_EXCEPTION_CODE i_num
    .global isr\i_num
    
    isr\i_num:
        cli             # disable interrupts
        push $\i_num    # push the interrupt number
        jmp isr_common  # jump to common isr

.endm


# create the 32 isr functions we need as
# specifed in the intel manual
ISR_NO_EXCEPTION_CODE 0
ISR_NO_EXCEPTION_CODE 1
ISR_NO_EXCEPTION_CODE 2
ISR_NO_EXCEPTION_CODE 3
ISR_NO_EXCEPTION_CODE 4
ISR_NO_EXCEPTION_CODE 5
ISR_NO_EXCEPTION_CODE 6
ISR_NO_EXCEPTION_CODE 7
ISR_EXCEPTION_CODE 8
ISR_NO_EXCEPTION_CODE 9
ISR_EXCEPTION_CODE 10
ISR_EXCEPTION_CODE 11
ISR_EXCEPTION_CODE 12
ISR_EXCEPTION_CODE 13
ISR_EXCEPTION_CODE 14
ISR_NO_EXCEPTION_CODE 15
ISR_NO_EXCEPTION_CODE 16
ISR_NO_EXCEPTION_CODE 17
ISR_NO_EXCEPTION_CODE 18
ISR_NO_EXCEPTION_CODE 19
ISR_NO_EXCEPTION_CODE 20
ISR_NO_EXCEPTION_CODE 21
ISR_NO_EXCEPTION_CODE 22
ISR_NO_EXCEPTION_CODE 23
ISR_NO_EXCEPTION_CODE 24
ISR_NO_EXCEPTION_CODE 25
ISR_NO_EXCEPTION_CODE 26
ISR_NO_EXCEPTION_CODE 27
ISR_NO_EXCEPTION_CODE 28
ISR_NO_EXCEPTION_CODE 29
ISR_NO_EXCEPTION_CODE 30
ISR_NO_EXCEPTION_CODE 31

# create a common interrupt handler
# saves the processor state, sets the kernel mode segments,
# calls the C++ function, then restored the CPU state
isr_common:
    # first, we must store all the current registers
    # onto the stack so that we can pass control to the
    # ISR. We do this as some of the registers are callee-saved
    # and the CPU will certainly need these values to continue
    # again.
    
    # pushes all general purpose registers.
    pusha

    # save the data seg register
    mov $0, %eax
    mov %ds, %ax
    push %eax

    # load the kernel data segment's address (0x10)
    mov $0x10, %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    
    # call the C++ level main ISR
    call isr_handler

    # restore the original registers
    pop %eax
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs

    # restore the general purpose registers
    popa

    # clean up pushed error code and ISR number
    add $8, %esp

    # restore interrup polling
    sti

    # return from interrupt routine
    iret