/**
 * Implementations of the interrupt handling routines in sys_interrupts.h
 */

#include "sys_interrupts.h"
#include "misc.h"



//handle() is used to take the interrupt number, 
//i_number, and the address to the current CPU stack frame.
extern "C" uint32_t InterruptHandler::handle(uint8_t i_number, uint32_t crnt_stkptr)
{


    // call the non-static interrupt handler
    if (crnt_interrupt_handler != nullptr)
    {
        return crnt_interrupt_handler->handle_dynamic(i_number, crnt_stkptr);
    }
    

    // after the interrupt code has been executed,
    // return the stack pointer so that the CPU can resume
    // where it left off.

    // this works for now as we do not have multiple
    // concurrent processes running, so there is no issue
    // of handling the threat number.
    return crnt_stkptr;
}



//handle() is used to take the interrupt number, 
//i_number, and the address to the current CPU stack frame.
uint32_t InterruptHandler::handle_dynamic(uint8_t i_number, uint32_t crnt_stkptr)
{


    // debug for now
    printf("                Inpt::handle()\n");





    // after the interrupt code has been executed,
    // return the stack pointer so that the CPU can resume
    // where it left off.

    // this works for now as we do not have multiple
    // concurrent processes running, so there is no issue
    // of handling the threat number.
    return crnt_stkptr;
}





// define the global descriptor table
InterruptHandler::_gate_descriptor InterruptHandler::interrupt_desc_table[N_ENTRIES];




// define the constructor. Takes a pointer to the global 
// descriptor table
InterruptHandler::InterruptHandler(GlobalDescriptorTable* global_desc_table)
{

    // grab the offset of the usable memory within our global segment
    uint16_t seg = global_desc_table->CodeSegmentSelector();

    // set all the entries in the IDT to block request initially
    for (uint16_t i = 0; i < N_ENTRIES; i++)
    {
        // create an a gate for a system level interrupt, calling the block function (does nothing) using seg as its memory.
        create_entry(i, seg, &block_request, PRIV_LVL_KERNEL, GATE_INTERRUPT);
    }



    // create a couple interrupts for 0x00 and 0x01, really 0x20 and 0x21, in IDT
    create_entry(BASE_I_NUM + 0x00, seg, &isr0x00, PRIV_LVL_KERNEL, GATE_INTERRUPT);
    create_entry(BASE_I_NUM + 0x01, seg, &isr0x01, PRIV_LVL_KERNEL, GATE_INTERRUPT);



    // init the PICs
    pic_controller.send_master_cmd(PIC_INIT);
    pic_controller.send_slave_cmd(PIC_INIT);

    // tell master pic to add 0x20 to any interrupt number it sends to CPU, while slave pic sends 0x28 + i_number
    pic_controller.send_master_data(PIC_OFFSET_MASTER);
    pic_controller.send_slave_data(PIC_OFFSET_SLAVE);


    // set the interrupt vectoring to cascade and tell master that there is a slave PIC at IRQ2
    pic_controller.send_master_data(ICW1_INTERVAL4);
    pic_controller.send_slave_data(ICW1_SINGLE);


    // set the PICs to work in 8086 mode
    pic_controller.send_master_data(ICW1_8086);
    pic_controller.send_slave_data(ICW1_8086);

    // send 0s
    pic_controller.send_master_data(DEFAULT_MASK);
    pic_controller.send_slave_data(DEFAULT_MASK);


    // tell the cpu to use the table
    interrupt_desc_table_pointerdata idt_ptr;

    //set the size
    idt_ptr.table_size = N_ENTRIES * sizeof(_gate_descriptor) - 1;

    // set the base address
    idt_ptr.base_addr = (uint32_t)interrupt_desc_table;

    // use lidt instruction to load the table 
    // the cpu will map interrupts to the table
    asm volatile("lidt %0" : : "m" (idt_ptr));

    // init the pointer to the active interrupt handler
    // point to null until this handler is set to active
    crnt_interrupt_handler = nullptr;
    
}

// define the destructor of the class
InterruptHandler::~InterruptHandler()
{
}





// function to make entries in the IDT
// takes the interrupt number as an index, the segment offset it used to specify which memory segment to use
// a pointer to the function to call, the flags and access level.
void InterruptHandler::create_entry(uint8_t i_number, uint16_t segment_desc_offset, func_t isr, uint8_t priv_lvl, uint8_t desc_type)
{

    // set the i_number'th entry to the given params

    // take the lower bits of the pointer
    interrupt_desc_table[i_number].handler_lower_bits = ((uint32_t)isr) & 0xFFFF;
    
    // take the upper bits
    interrupt_desc_table[i_number].handler_upper_bits = (((uint32_t)isr) >> 16) & 0xFFFF;

    // calculate the privilage byte, setting the correct bits
    interrupt_desc_table[i_number].priv_lvl = PRESENT_FLAG | desc_type | ((priv_lvl & 3) << 5);


    interrupt_desc_table[i_number].segment_desc_offset = segment_desc_offset;


    // reserved byte is always 0
    interrupt_desc_table[i_number].reserved_byte = 0;

}



// need a function to block or ignore any requests
// that we dont want to service. Requests could be caused
// by devices we haven't yet configured when testing the os.
void InterruptHandler::block_request()
{
    // do nothing
}


// function to tell the CPU to send interrupts
// to this table
void InterruptHandler::set_active()
{


    // check if there is an existing active handler
    if (crnt_interrupt_handler != nullptr)
    {
        // make the old handler inactive
        crnt_interrupt_handler->set_inactive();
    }
    

    // set this interrupt handler as the active handler
    crnt_interrupt_handler = this;


    // call sti assembly to start interrup poling at the CPU level
    //asm volatile("cli");
    __asm__("sti");
    
}

// store a pointer to an object of this class
// at any one time there can only be one interrupt management objects
// that is active and in use (its IDT is loaded on the CPU)
// store the pointer to that interrupt handling object
InterruptHandler* InterruptHandler::crnt_interrupt_handler = nullptr;

void InterruptHandler::set_inactive()
{



    // check if calling on an active handler
    if (crnt_interrupt_handler == this)
    {
        // deactivate
        crnt_interrupt_handler = nullptr;
        __asm__("cli");
    }
    
}
