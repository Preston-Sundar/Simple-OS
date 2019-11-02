.set MAGIC, 0x1badb002
.set FLAGS, (1 << 0 | 1 << 1)
.set CHECKSUM, -(MAGIC + FLAGS)


/* the multiboot structure, tells the bootloader that this is a valid kernal */
.section .multiboot 
    .long MAGIC
    .long FLAGS
    .long CHECKSUM



/* Cpp program requires stack pointer to point to a valid code point to begin execution
 * fix this manually
 */

/* linker finds kernal_main */
.section .text
.extern kernel_main
.extern call_constructors
.global loader

loader:
    /* set the stack ptr to the location of our kernal stack */
    mov $kernel_stack, %esp

    /* call the constructor functions to set up memory, placed by linker */
    call call_constructors

    /* push ebx and eax as they store the magic number and pointer to multiboot structure 
     * Also tells us other stuff like the amount of RAM in machine, useful to us.
     */
    push %eax
    push %ebx

    call kernel_main

/* in case we complete kernal stack for some reason, have an inf loop to prevent 
   complete exit */
_stop:
    cli
    hlt
    jmp _stop

/* create a bss section as kernal_stack isn't explicitly initialized */
.section .bss
/* to avoid the risk of running stack pointer into memory of bootloader, 
   set an offset of some space before the kernal stack begins using 2MB */
.space 2*1024*1024; 

kernel_stack: 
    /* set the esp register to point here */
