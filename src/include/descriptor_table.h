/**
 * Global Descriptor table implementation
 * Used to specify the system wide resource. Tells us the access privilages and sizes of blocks of memory
 * each entry stores the pointer to its block along with flags indicating its properties.
 * contains entries for the IDT as well.
 * 
 *  */

#ifndef __DESCRIPTOR_TABLE_H
#define __DESCRIPTOR_TABLE_H

#include "types.h"

// 5 entries: 1 null seg, code seg, data seg, user code seg, user data seg
#define GDT_NUM_ENTRIES 5
#define IDT_NUM_ENTRIES 256

class DescTable
{

protected:

    // the entry into the IDT
    struct interrupt_table_entry
    {

        uint16_t base_lo;   // lower word of the address to jump to when interrupt occurs
        uint16_t segment;   // the segment used to exectue the interrupt routine when called
        uint8_t zero_byte;  // always zero
        uint8_t flags;      // Present | priv level | S: 0 | interrupt: gate 0110
        uint16_t base_high; // the upper 16 bits of the address to jump to

    } __attribute__((packed));

    // define its type
    typedef struct interrupt_table_entry inter_entry_t; 


    // pointer to the struct
    struct interrupt_ptr
    {

        uint16_t limit;  // length of the IDT
        uint32_t base;   // starting address of the IDT

    } __attribute__((packed));

    // define its type
    typedef struct interrupt_ptr inter_ptr_t;

    // create the table and its pointer
    inter_entry_t idt_table[IDT_NUM_ENTRIES];
    inter_ptr_t idt_ptr;


    // the entry into the GDT
    struct desc_table_entry
    {

        uint16_t limit_low;  // lower bits of the limit word
        uint16_t base_low;   // the base address low component
        uint8_t base_middle; // next 8 bits of base
        uint8_t access;      // access flags    | Present | ring (0 or 3) | Desc type | Segment type (code vs data)
        uint8_t granuality;  // granuality byte |1b vs 1kb| Op size (16 or 32) | 0 bit | unused bit | seg length |
        uint8_t base_high;   // last 8 bits of base address in physical memory

    } __attribute__((packed));

    // define its type
    typedef struct desc_table_entry dt_entry_t;

    // pointer struct to pass to ldgt
    struct dt_ptr
    {

        uint16_t limit; // size - 1 (last valid address in table)
        uint32_t base;  // address of first dt entry

    } __attribute__((packed));

    // define its type
    typedef struct dt_ptr dt_ptr_t;

    // define gdt table
    dt_entry_t gdt_table[GDT_NUM_ENTRIES];

    // define the pointer to the gdt
    dt_ptr_t gdt_ptr;

public:
    // contructor and destructor
    DescTable();
    ~DescTable();

    // function to set a given index in the GDT to certain values
    void set_segment(uint32_t e_num, uint32_t base_addr, uint32_t limit_addr, uint8_t access_byte, uint8_t granuality_byte);

    // function to set a given index in the IDT to certain valies
    void set_gate(uint32_t i_num, uint32_t base_addr, uint16_t selector_word, uint8_t flags);

};

#endif /* desc_table.h */