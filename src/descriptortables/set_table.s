.section .text

.global gdt_flush
.global idt_flush


# function to load the IDT
idt_flush:
    # get the pointer to idt
    mov 4(%esp), %eax
    # load idt
    lidt (%eax)
    ret

# function to load GDT
gdt_flush:
    # get the pointer to gdt
    mov 4(%esp), %eax
    # load the GDT
    lgdt (%eax)

    # load a fixed offset into the GDT (points to code segment)
    mov $0x10, %eax

    # ensure all segment regs point to the same segment
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    

    # this guy right here, caused me great pain
    # its an AT&T style FAR jump, nothing special
    # however, it took 3 days of debugging to figure
    # out the correct syntax for it. 
    jmp $0x08, $flush

# return back to C++ code
flush:
    ret
