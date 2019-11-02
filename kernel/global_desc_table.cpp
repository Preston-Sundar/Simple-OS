#include "global_desc_table.h"

/**
 * A code segment is identified by flag 0x9A, cannot write to a code segment
 * while a data segment is identified by flag 0x92
 * 
 */


GlobalDescriptorTable::GlobalDescriptorTable() : nullSegmentSelector(0, 0, 0),
                                                 unusedSegmentSelector(0, 0, 0),
                                                 codeSegmentSelector(0, 64*1024*1024, 0x9A),
                                                 dataSegmentSelector(0, 64*1024*1024, 0x92)
{
    
    //8 bytes defined, but processor expects 6 bytes only 
    uint32_t i[2];

    //first 4 bytes is address of table
    i[0] = (uint32_t)this;

    //second 4 bytes, the high bytes,  are size of global desc table
    i[1] = sizeof(GlobalDescriptorTable) << 16;


    // tell processor to use this table using its ldgt function
    asm volatile("lgdt (%0)" : : "p"  (((uint8_t *) i) + 2));
}

// function to get the offset of the datasegment selector
uint16_t GlobalDescriptorTable::DataSegmentSelector()
{
    // calculate the offset by subtracting the table's address from the datasegment's address
    return (uint8_t *) &dataSegmentSelector - (uint8_t*)this;
}

// function to get the offset of the code segment 
uint16_t GlobalDescriptorTable::CodeSegmentSelector()
{
    // calculate the offset by subtracting the table's address from the code segment's address
    return (uint8_t *) &codeSegmentSelector - (uint8_t*)this;
}

// default destructor
GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

/**
 * The constructor to create a new entry segment, set the flags, determine the formatting for the limit, and set the base
 */
GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t flags)
{
    uint8_t* target = (uint8_t*)this;

    //if 16 bit limit
    if (limit <= 65536)
    { 
        // tell processor that this is a 16bit entry
        target[6] = 0x40;
    
    } else {
        
        // if the last 12 bits of limit are not 1s
        if ((limit & 0xFFF) != 0xFFF)
        {
            limit = (limit >> 12) - 1;
            
        } else {
            limit >>= 12;
        }
        
        // indicate that there was a shift of 12 done
        target[6] = 0xC0;

    }

    // set the lower and upper 2 lowest bytes of limit
    target[0] = limit & 0xFF;
    target[1] = (limit >> 8) & 0xFF;

    //the rest of limit must go in lower 4 bit of byte 6, and byte 5
    target[6] |= (limit >> 16) & 0xF;

    //encode the pointer
    target[2] =  base & 0xFF;
    target[3] = (base >> 8) & 0xFF;
    target[4] = (base >> 16) & 0xFF;
    target[7] = (base >> 24) & 0xFF;

    // set the flags 
    target[5] = flags;
    
}


/**
 * Define the methods to get the base pointer from an segment and 
 * the limit for a segment
 */

uint32_t GlobalDescriptorTable::SegmentDescriptor::Base()
{
    // simply do the reverse of wht was done to place the pointer in
    
    uint8_t* target = (uint8_t*) this;
    uint32_t result = target[7];
    result = (result << 8) + target[4];
    result = (result << 8) + target[3];
    result = (result << 8) + target[2];

    return result;
}

uint32_t GlobalDescriptorTable::SegmentDescriptor::Limit()
{
    uint8_t* target = (uint8_t *)this;
    uint32_t result = target[6] & 0xF;
    result = (result << 8) + target[1];
    result = (result << 8) + target[0];
    
    //check if there was a shift of 12
    if (target[6] & 0xC0 == 0xC0)
    {
        result = (result << 12) & 0xFFF;
    }
    
    return result;
}
