#   This file is used to push the interrupt functions onto the stack. 
#   This is needed if we're going to call these functions later and we need them on 
#   the stack and ready to go.

# define the base address for the interrupt methods
# .global IRQ_BASE_OFFSET 0x20


.section .text


# We cannot simply write a function in C++ to accept an interrupt code
# and run away to process it. This is because 
# the compiler will place the service handlers at seemingly random locations in memory.
# To overcome this, we write some assembly to manually 
# place various interrupt handlers 
# into memory (onto the stack). We then use pointers to these 
# locations within the C++ to call those handlers.

# hook up the external funtion of our master handle routine.
# we can now execute this funtion from this asm.
.extern _ZN16InterruptHandler6handleEhj

.global _ZN16InterruptHandler22block_requestEv


# need to place the jump points to where our interrupt functions are in memory
.macro isr i_num

# forward implementation of the function in sys_interrupts
# calls the corresponding isr
.global _ZN16InterruptHandler26handle\i_num\()Ev
_ZN16InterruptHandler26handle\i_num\()Ev:
    movb $\i_num + 0x20, (i_number)
    jmp handle_interrupt



.endm




# need to place the jump points to where our interrupt functions are in memory
# this method is for interrupt excetptions
.macro isr_exception i_num

# forward implementation of the function in sys_interrupts
# calls the corresponding isr
.global _ZN16InterruptHandler26handleException\i_num\()Ev
_ZN16InterruptHandler26handleException\i_num\()Ev:
    movb $\i_num, (i_number)
    jmp handle_interrupt



.endm






# add these interrupts for now
isr 0x00
isr 0x01

# define the function to handle the interrupt
handle_interrupt:

    # first, we must store all the current registers
    # onto the stack so that we can pass control to the
    # ISR. We do this as some of the registers are callee-saved
    # and the CPU will certainly need these values to continue
    # again.
    
    # pushes all general purpose registers.
    pusha


    # pushes the data seg register.
    pushl %ds

    # pushes the stack segment
    pushl %es

    # the remaining general purpose segment registers
    pushl %fs
    pushl %gs


    # now make the call
    # save the current stack ptr
    pushl %esp

    # also push the interrupt number for the method to handle
    push (i_number)

    # call the function
    call _ZN16InterruptHandler6handleEhj
    
    # copy the result, and reset the stack pointer
    movl %eax, %esp


    # restore all the pushed processor registers
    popl %gs
    popl %fs
    popl %es
    popl %ds
    popa

_ZN16InterruptHandler22block_requestEv:

    # call iret to tell CPU that interrupt is complete
    iret

# specify the data used
.data
    i_number: .byte 0
