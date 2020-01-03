/**
 * Global Descriptor table implementation
 *  Used to specify the system wide resource. Tells us the access privilages and sizes of blocks of memory
 *  each entry stores the pointer to its block along with flags indicating its properties.
 * 
 *  */

#include "../include/descriptor_table.h"

/**
 * Extern function to flush out the old gdt
 * and load in the new one. Defined in
 * set_table.s
 */
extern "C" void gdt_flush(uint32_t ptr);





/**
 * These are the asm-defined interrupt handlers for the CPU
 * Defined in interrupts.s
 */
extern "C" void isr0();
extern "C" void isr1();
extern "C" void isr2();
extern "C" void isr3();
extern "C" void isr4();
extern "C" void isr5();
extern "C" void isr6();
extern "C" void isr7();
extern "C" void isr8();
extern "C" void isr9();
extern "C" void isr10();
extern "C" void isr11();
extern "C" void isr12();
extern "C" void isr13();
extern "C" void isr14();
extern "C" void isr15();
extern "C" void isr16();
extern "C" void isr17();
extern "C" void isr18();
extern "C" void isr19();
extern "C" void isr20();
extern "C" void isr21();
extern "C" void isr22();
extern "C" void isr23();
extern "C" void isr24();
extern "C" void isr25();
extern "C" void isr26();
extern "C" void isr27();
extern "C" void isr28();
extern "C" void isr29();
extern "C" void isr30();
extern "C" void isr31();



/**
 * Define the function to set the new IDT
 * and replace the existing one provided by grub.
 * defined in set_table.s
 */
extern "C" void idt_flush(uint32_t ptr);



/**
 * 
 * DescTable()
 * Inits all the descriptor table entries. Inits the IDT entries
 * @param none
 */
DescTable::DescTable()
{

    // set the limit pointer of the gdt
    // must be the address of the last accesible address in table
    gdt_ptr.limit = (sizeof(dt_entry_t) * GDT_NUM_ENTRIES) - 1u;

    // calculate the base addr, the address of the table
    gdt_ptr.base = (uint32_t)&gdt_table;

    /**init the gates
     *Using flat memory model: one strip of memory, hence all segments start at 0 and end 
     *at the end of memory. */
    // null segment
    set_segment(0, 0, 0, 0, 0);

    // code seg
    set_segment(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    // data seg
    set_segment(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    // user level code and data seg
    set_segment(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    set_segment(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

    // set the CPU to use GDT
    gdt_flush((uint32_t)&gdt_ptr);


    // Now set the entries in the IDT

    // set the pointer
    idt_ptr.limit = (sizeof(inter_entry_t) * IDT_NUM_ENTRIES) - 1u;
    idt_ptr.base = (uint32_t) &(idt_table);


    // set all of the 32 interrupts up
    set_gate(0, (uint32_t)isr0, 0x08, 0x8E);
    set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    set_gate(1, (uint32_t)isr1, 0x08, 0x8E);
    set_gate(2, (uint32_t)isr2, 0x08, 0x8E);
    set_gate(3, (uint32_t)isr3, 0x08, 0x8E);
    set_gate(4, (uint32_t)isr4, 0x08, 0x8E);
    set_gate(5, (uint32_t)isr5, 0x08, 0x8E);
    set_gate(6, (uint32_t)isr6, 0x08, 0x8E);
    set_gate(7, (uint32_t)isr7, 0x08, 0x8E);
    set_gate(8, (uint32_t)isr8, 0x08, 0x8E);
    set_gate(9, (uint32_t)isr9, 0x08, 0x8E);
    set_gate(10, (uint32_t)isr10, 0x08, 0x8E);
    set_gate(11, (uint32_t)isr11, 0x08, 0x8E);
    set_gate(12, (uint32_t)isr12, 0x08, 0x8E);
    set_gate(13, (uint32_t)isr13, 0x08, 0x8E);
    set_gate(14, (uint32_t)isr14, 0x08, 0x8E);
    set_gate(15, (uint32_t)isr15, 0x08, 0x8E);
    set_gate(16, (uint32_t)isr16, 0x08, 0x8E);
    set_gate(17, (uint32_t)isr17, 0x08, 0x8E);
    set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    set_gate(31, (uint32_t)isr31, 0x08, 0x8E);
    set_gate(18, (uint32_t)isr18, 0x08, 0x8E);
    set_gate(19, (uint32_t)isr19, 0x08, 0x8E);
    set_gate(20, (uint32_t)isr20, 0x08, 0x8E);
    set_gate(21, (uint32_t)isr21, 0x08, 0x8E);
    set_gate(22, (uint32_t)isr22, 0x08, 0x8E);
    set_gate(23, (uint32_t)isr23, 0x08, 0x8E);
    set_gate(24, (uint32_t)isr24, 0x08, 0x8E);
    set_gate(25, (uint32_t)isr25, 0x08, 0x8E);
    set_gate(26, (uint32_t)isr26, 0x08, 0x8E);
    set_gate(27, (uint32_t)isr27, 0x08, 0x8E);
    set_gate(28, (uint32_t)isr28, 0x08, 0x8E);
    set_gate(29, (uint32_t)isr29, 0x08, 0x8E);
    set_gate(30, (uint32_t)isr30, 0x08, 0x8E);
    set_gate(31, (uint32_t)isr31, 0x08, 0x8E);

    // set the new IDT
    idt_flush((uint32_t) &idt_ptr);


}

/**
 * set_segment(int32_t e_num, uint32_t base_addr, uint32_t limit_addr, uint8_t access_byte, uint8_t granuality_byte)
 * Initializes an entry in the descriptor table.
 * @param e_num entry number to change
 * @param base_addr the base address in memory for the segment
 * @param limit_addr the end of the memory segment 
 * @param access_byte  | Present | ring (0 or 3) | Desc type | Segment type (code vs data)
 * @param granuality_byte |1b vs 1kb| Op size (16 or 32) | 0 bit | unused bit | seg length |
 */
void DescTable::set_segment(uint32_t e_num, uint32_t base_addr, uint32_t limit_addr, uint8_t access_byte, uint8_t granuality_byte)
{

    // set the corresponding values
    gdt_table[e_num].base_low = (base_addr & 0xFFFF);
    gdt_table[e_num].base_middle = (base_addr >> 16) & 0xFF;
    gdt_table[e_num].base_high = (base_addr >> 24) & 0xFF;

    // set the limit and the first nibble of the gran byte
    gdt_table[e_num].limit_low = (limit_addr & 0xFFFF);
    gdt_table[e_num].granuality = (limit_addr >> 16) & 0x0F;

    // set up the rest of the gran byte and set access byte
    gdt_table[e_num].granuality |= granuality_byte & 0xF0;
    gdt_table[e_num].access = access_byte;
}





/**
 * set_gate(uint32_t i_num, uint32_t base_addr, uint16_t selector_word, uint8_t flags)
 * Initializes an entry in the descriptor table.
 * @param i_num entry number to change
 * @param base_addr the base address in memory for the interrupt entry
 * @param limit_addr the end of the memory segment 
 * @param selector_word which segment to use
 * @param flags P | DPL | interrup gate: 0110
 */
void DescTable::set_gate(uint32_t i_num, uint32_t base_addr, uint16_t selector_word, uint8_t flags)
{
    // set the address
    idt_table[i_num].base_lo = base_addr & 0xFFFF;
    idt_table[i_num].base_high = (base_addr >> 16) & 0xFFFF;

    // set the segment selector and zero byte
    idt_table[i_num].segment = selector_word;
    idt_table[i_num].zero_byte = 0;

    // set the flag byte
    idt_table[i_num].flags = flags;
}






/**
 * Default destructor
 */
DescTable::~DescTable()
{
    // do nothing
}
