/**
 * Class to handle sending and recieving varying lengths of data from hwardware ports.
 * At the lowest level, CPU level calls using 'inx' and 'outx' are used to get and send
 * data to the ports.
 */


#include "hw_port_unified.h"


/**
 * constructor of the HW port class.
 * Sets up the local variables.
 */

HWPort::HWPort(uint16_t port_number, uint8_t data_length)
{
    this->port_number = port_number;
    this->data_length = data_length;
}


/**
 * Use the standard destructor
 */
HWPort::~HWPort()
{
}

/**
 * define the method to send data to the port
 * 
 */
void HWPort::put_data(uint32_t data)
{
    // use the data_length to call the correct put function
    switch (this->data_length)
    {
    case DATA_BYTE:
    
        // cast the data
        uint8_t _data = (uint8_t) data;
        // call the byte put function
        this->put_byte_data(_data);

        break;

    case DATA_BYTE_SLOW:
    
        // cast the data
        uint8_t _data = (uint8_t) data;
        // call the byte put function
        this->put_byte_slow_data(_data);
        
        break;
    
    case DATA_WORD:
    
        // cast the data
        uint16_t _data = (uint16_t) data;
        // call the byte put function
        this->put_word_data(_data);
        
        break;
    
    case DATA_DWORD:
    
        // cast the data
        uint32_t _data = (uint32_t) data;
        // call the byte put function
        this->put_dword_data(_data);
        
        break;

    default:
        break;
    }
}


// define the functions to send the data

