# Simple-Operating System
Creating a simple OS from scratch. My primary resource for this project are the articles on https://wiki.osdev.org. 


## Goal
Learn how operating systems work by implementing one. The end result should support TCP connections, Support graphics and visualizations, and have memory and thread management.

## Implementation

### Bootloader
I have not implemented a bootloader, and instead utilize GNU GRUB to load my kernel. This ensures that I can boot from multiple sources and quickly check hard drive and optical disk boot options.

### Global Descriptor Table
Created a simple Global Descriptor table that models the following segment:
![alt text](https://github.com/Preston-Sundar/Poop-OS/blob/master/readmeimages/segment-descriptor.png)

Implemented in `descriptor_table.cpp` with functions to create new segments, retrieve the pointer to a block, check limits, and set flags.

Below is the debugger output from Bochs showing the 5 segments that were created:
![alt text](https://github.com/Preston-Sundar/Simple-OS/blob/master/readmeimages/bochs_gdt.png)


### Interrupt Descriptor Table and the PIC
The diagram below illustrates the role of the Interrupt Descriptor Table and the PIC. It acts as a mediator to allow the CPU to complete execution before servicing an interrupt, and allows for the CPU to receive interrupts from several devices in one place.
![alt text](https://github.com/Preston-Sundar/Poop-OS/blob/master/readmeimages/PIC.png)
 
high-level descriptions for the processes occurring at each marked stage:
1. When a key on the keyboard is pressed, the Programmable Interrupt Controller is notified and will create an interrupt. The PIC then decides if the CPU should be involved, and if so, an interrupt vector is generated.
2. CPU then acknowledges the interrupt. Within the interrupt vector sent from the PIC lies the interrupt number. The CPU then maps this number to its respective interrupt handler.
3. From the CPU's perspective, after every instruction has been executed, it checks to see if the PIC's pin has notified an interrupt. It then saves the current process onto the stack and passes control to the OS.
4. From the OS's perspective, an Interrupt Descriptor Table is set up in advance to execution and is used to jump to the correct interrupt handler. Once complete, an 'iret' instruction is issued to the CPU to resume original state.

Shown below is assembly that models the behaviour stated above, taken from `interrupts.s`:
```asm
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

    # restore interrupt polling
    sti

    # return from interrupt routine
    iret
```



### How to use?
To boot into the OS for testing, I use VirtualBox for a VM and grub-mkrescue to generate a bootable disk image from a given file structure.

Prior to booting, initialize an empty VM within VirtualBox setting all options to 'other' and 64MB of RAM, use the same name as shown below:
![alt text](https://github.com/Preston-Sundar/Simple-OS/blob/master/readmeimages/instruction_addvm.png)
Boot into the OS by running the following commands within the kernel direcory:
```console
foo@bar:~/$ git clone https://github.com/Preston-Sundar/Simple-OS.git
foo@bar:~/$ cd Simple-OS/kernel/
foo@bar:~/$ make runvb
```
