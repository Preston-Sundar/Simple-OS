
#ifndef __SYS__INTERRUPTS_H
#define __SYS__INTERRUPTS_H

#include "types.h"
#include "hw_port.h"
#include "global_desc_table.h"
#include "pic_controller.h"
#include "misc.h"


// define the number of entries in the IDT
#define N_ENTRIES           256

// define the base interrupt number
#define BASE_I_NUM          0x20

// defines used to create the gate type
#define PRESENT_FLAG        0x80

// define the interrupt gate types as well as the system level codes
#define PRIV_LVL_KERNEL     0
#define GATE_INTERRUPT      0xE

// define the ports for master and slave PICs
#define PIC_MASTER_PORT_CMD 0x20
#define PIC_MASTER_DATA     0x21
#define PIC_SLAVE_PORT_CMD  0xA0
#define PIC_SLAVE_DATA      0xA1


// typdedef to handle function pointers
typedef void (*func_t)();

/**
 * Class to handle interrupts.
 */

class InterruptHandler
{

protected:
    
    // each entry in the interrupt descriptor table is called a gate descriptor
    // needs to be byte aligned in memory
    struct _gate_descriptor
    {

        // address of the service routine is split into upper and lower
        uint16_t handler_lower_bits;

        // store the offset of the segment in the global desc table
        uint16_t segment_desc_offset;

        // a byte of reserved space for the reserved byte
        uint8_t reserved_byte;

        // access privilage level
        uint8_t priv_lvl;

        // upper bits
        uint16_t handler_upper_bits;

    } __attribute__((packed));


    // create an array of gate descriptors to form the table
    static _gate_descriptor interrupt_desc_table[N_ENTRIES];


    // function to make entries in the IDT
    // takes the interrupt number as an index, the segment offset it used to specify which memory segment to use
    // a pointer to the function to call, the flags and access level.
    static void create_entry(uint8_t i_number, uint16_t segment_desc_offset, func_t isr, uint8_t priv_lvl, uint8_t flags);


    struct interrupt_desc_table_pointerdata
    {

        // store the size of the table to calculate the end of the table within the segment
        uint16_t table_size;

        // store the base address for the table within the segment
        uint32_t base_addr;

    } __attribute__((packed));


    // create the PIC controller
    PIC pic_controller;


    static void isr0x00(){

        printf_skeleton_message("isr0x00", PRINT_STATE);

    };
    static void isr0x01(){

        printf("CALLED isr0x01");

    };

public:


    // define the constructor. Takes a pointer to the global 
    // descriptor table
    InterruptHandler(GlobalDescriptorTable* global_desc_table);
    ~InterruptHandler();

    //handle() is used to take the interrupt number, 
    //i_number, and the address to the current CPU stack frame.
    static uint32_t handle(uint8_t i_number, uint32_t crnt_stkptr);
    
    // same as handle(), but must be called from a non static context
    // called by the current active interrupt handler object
    // called from the handle() method to enter the non-static context
    uint32_t handle_dynamic(uint8_t i_number, uint32_t crnt_stkptr);


    // function to ignore a request
    static void block_request();    
    
    // function to tell the CPU to send the interrupts to the table
    void set_active();

    // sets the current interrupt handler to none
    // calls cli to remove the current interrupt table in CPU
    void set_inactive();

protected: 


    // store a pointer to an object of this class
    // at any one time there can only be one interrupt management objects
    // that is active and in use (its IDT is loaded on the CPU)
    // store the pointer to that interrupt handling object
    static InterruptHandler* crnt_interrupt_handler;


};

#endif