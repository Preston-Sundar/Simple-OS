/**
 * Global Descriptor table implementation
 *  Used to specify the system wide resource. Tells us the access privilages and sizes of blocks of memory
 *  each entry stores the pointer to its block along with flags indicating its properties.
 * 
 *  */ 





#ifndef __GLOBAL_DESC_TABLE_H
#define __GLOBAL_DESC_TABLE_H

#include "types.h"

class GlobalDescriptorTable
{
    public: 

        /**
         * Each segment descriptor has an associated segment selector. 
         * A segment selector provides the software that uses it with an 
         * index into the GDT or LDT (the offset of its associated segment descriptor),
         * a global/local flag (determines whether the selector points to the GDT or the LDT), and access rights information
         */
        class SegmentDescriptor
        {
            private:
                uint16_t limit_low;
                uint16_t baseptr_low;
                uint8_t baseptr_high_byte;
                uint8_t type;
                uint8_t flag_limit_hi;
                uint8_t base_vhi;

            public:
                

                /**
                 * constructor to create a descriptor for a segment
                 *  pass is the base address, a limit size, and a type of memory block to create.
                 * */
                SegmentDescriptor(uint32_t base, uint32_t limit, uint8_t type);

                //getters to get the pointer to a segmentdesc and their limit
                uint32_t Base();
                uint32_t Limit();


        } __attribute__((packed));  // tell compiler to retain the structure of objects of this class in memory, needs to be byte perfect


    // create an empty global descriptor
    // testing for now
    SegmentDescriptor nullSegmentSelector;
    SegmentDescriptor unusedSegmentSelector;

    // have one code segment and one data segment
    // to span acorss entire memory
    SegmentDescriptor codeSegmentSelector;
    SegmentDescriptor dataSegmentSelector;

    public:
        GlobalDescriptorTable();
        ~GlobalDescriptorTable();

    // returns the offset of the code segment and data segment descriptors
    uint16_t CodeSegmentSelector();
    uint16_t DataSegmentSelector();

};

#endif
