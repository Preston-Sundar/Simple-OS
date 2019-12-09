# Simple-Operating System
Creating a simple OS from scratch. My primary resource for this project are the articles on https://wiki.osdev.org. 


## Goal
Learn how operating systems work by implementing one. The end result should support TCP connections, Support graphics and visualizations, and have memory and thread management.

## Implementation

### Bootloader
I have not implemented a bootloader, and instead utilize GNU GRUB to load my kernel. 

### Global Descriptor Table
Created a simple Global Descriptor table that models the following segment:
![alt text](https://github.com/Preston-Sundar/Poop-OS/blob/master/readmeimages/segment-descriptor.png)

Implemented in global_desc_table.cpp with functions to create new segments, retrieve the pointer to a block, check limits, and set flags.

### Interrupt Descriptor Table and the PIC
The diagram below illustrates the role of the Interrupt Descriptor Table and the PIC. It acts as a mediator to allow the CPU to complete execution before servicing an interrupt, and allows for the CPU to receive interrupts from several devices in one place.
![alt text](https://github.com/Preston-Sundar/Poop-OS/blob/master/readmeimages/PIC.png)
 
high-level descriptions for the processes occurring at each marked stage:
1. When a key on the keyboard is pressed, the Programmable Interrupt Controller is notified and will create an interrupt. The PIC then decides if the CPU should be involved, and if so, an interrupt vector is generated.
2. CPU then acknowledges the interrupt. Within the interrupt vector sent from the PIC lies the interrupt number. The CPU then maps this number to its respective interrupt handler.
3. From the CPU's perspective, after every instruction has been executed, it checks to see if the PIC's pin has notified an interrupt. It then saves the current process onto the stack and passes control to the OS.
4. From the OS's perspective, an Interrupt Descriptor Table is set up in advance to execution and is used to jump to the correct interrupt handler. Once complete, an 'iret' instruction is issued to the CPU to resume original state.
### How to use?
To boot into the OS for testing, I use VirtualBox for a VM and grub-mkrescue to generate a bootable disk image from a given file structure.

Prior to booting, initialize an emty VM within VirtualBox setting all options to 'other' and 64MB of RAM.
Boot into the OS by running the following commands within the kernel direcory:
```console
foo@bar:~/$ git clone https://github.com/Preston-Sundar/Simple-OS.git
foo@bar:~/$ cd Simple-OS/kernel/
foo@bar:~/$ make run
```
