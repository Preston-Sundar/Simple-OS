/* entry symbol for ELF structure */
.global loader

.set MAGIC, 0x1badb002
.set FLAGS, 0x0
.set CHECKSUM, -(MAGIC + FLAGS)

/* set the size of the stack in bytes */
.set K_STACK_SIZE, 4096


/* the multiboot structure, tells the bootloader that this is a valid kernal */
.section .multiboot
.align 4 
    .long MAGIC
    .long FLAGS
    .long CHECKSUM



/* linker finds kernal_main */
.section .text
.extern kernel_main
.extern call_constructors



loader:
    /* set the stack ptr to the location of our kernal stack */
    mov $kernel_stack + K_STACK_SIZE, %esp

    /* call the constructor functions to set up memory, placed by linker */
    call call_constructors

    /* push ebx and eax as they store the magic number and pointer to multiboot structure 
     * Also tells us other stuff like the amount of RAM in machine, useful to us. */
    
    push %eax
    push %ebx

    call kernel_main

/* not reached, there is an infinite loop in kernel_main */
loop:
    jmp loop



/* tell GRUB to load the stack in the bss section */
.section .bss   
.align 4
/* reserve 4MB of stack space */
.space K_STACK_SIZE
kernel_stack:
    /* point esp here so that in can grow down */
    