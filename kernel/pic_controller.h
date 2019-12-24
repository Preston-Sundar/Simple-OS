#ifndef __PIC_CONTROLLER_H
#define __PIC_CONTROLLER_H

/** pic controller code to send commands to the PICs upon initilaizations
 *  Stores functions here for readability. Also helps separate all the data codes.
 *  All specified data codes are bsed on the x86's 8259 PIC.
 */




#include "hw_port.h"

// Define all the control codes used to control PIC
#define PIC_INIT            0x11

#define PIC_OFFSET_MASTER   0x20
#define PIC_OFFSET_SLAVE    0x28

#define ICW1_SINGLE         0x02
#define ICW1_INTERVAL4      0x04

#define ICW1_8086           0x01
#define DEFAULT_MASK        0x00


// define the HW ports used for the data and cmd
// for both PICs
// define the ports for master and slave PICs
#define PIC_MASTER_PORT_CMD 0x20
#define PIC_MASTER_DATA     0x21
#define PIC_SLAVE_PORT_CMD  0xA0
#define PIC_SLAVE_DATA      0xA1



/**
 * Class to interface with the master and slave PICs
 * Uses the slower, synchronous, hw port to send data to PIC.
 */
class PIC
{

protected:

    // store the HW ports used to talk to PIC
    // create  prots to communicate with the PIC
    // there are really two pic, master and slave.
    // One port for commands, another for data
    // same with slave port
    HWPort_Byte_Slow pic_master_cmd;
    HWPort_Byte_Slow pic_slave_cmd;
    HWPort_Byte_Slow pic_master_data;
    HWPort_Byte_Slow pic_slave_data;



public:

    /**
     * Define the constructor and destructs. No Params.
     */
    PIC();
    ~PIC();

    /**
     * Functions to send a byte of command to the master or slave, or send
     * a byte of data to the data ports of the PICs. In total, one word is accepted
     * By the PICs. 
     */
    void send_master_cmd(uint8_t cmd)   {    this->pic_master_cmd.Put(cmd);    }
    void send_master_data(uint8_t data) {    this->pic_master_data.Put(data);    }
    void send_slave_cmd(uint8_t cmd)    {    this->pic_slave_cmd.Put(cmd);    }
    void send_slave_data(uint8_t data)  {    this->pic_slave_data.Put(data);    }



};


#endif