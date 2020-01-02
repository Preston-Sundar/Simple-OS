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
    //set_table((uint32_t) &gdt_ptr);
    gdt_flush((uint32_t)&gdt_ptr);
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
 * Default destructor
 */
DescTable::~DescTable()
{
    // do nothing
}
