/** pic controller code to send commands to the PICs upon initilaizations
 *  Stores functions here for readability. Also helps separate all the data codes.
 *  All specified data codes are bsed on the x86's 8259 PIC.
 */


#include "pic_controller.h"


/**
 * Use default destructor.
 * In constructor, initialize the HW ports to communicate with the PICs
 */

PIC::PIC() : pic_master_cmd(PIC_MASTER_PORT_CMD), 
             pic_master_data(PIC_MASTER_DATA),
             pic_slave_cmd(PIC_SLAVE_PORT_CMD),
             pic_slave_data(PIC_SLAVE_DATA)
{

    // do nothing

}

PIC::~PIC()
{
    // do nothing
    
}


