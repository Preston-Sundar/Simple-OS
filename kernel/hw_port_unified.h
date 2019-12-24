#ifndef __HW_PORT_UNIFIED_H
#define __HW_PORT_UNIFIED_H


/**
 * Class to handle sending and recieving varying lengths of data from hwardware ports.
 * At the lowest level, CPU level calls using 'inx' and 'outx' are used to get and send
 * data to the ports.
 */


#include "types.h"

// Define the various data lengths to specify what the 
// data lengths will be.
// considering making this a struct for readablity.
#define DATA_BYTE        0
#define DATA_BYTE_SLOW   1
#define DATA_WORD        2
#define DATA_DWORD       3


class HWPort
{

private:
    
    // port numbers are 16 bits
    uint16_t port_number;

    // store the port type
    uint8_t data_length;



    // set of private functions to cast the 
    // parameter to put_data into their correct
    // types, then sends the data.
    void put_byte_data(uint8_t data);
    void put_byte_slow_data(uint8_t data);
    void put_word_data(uint16_t data);
    void put_dword_data(uint32_t data);

    


public:
    // default constructors and destructor
    HWPort(uint16_t port_number, uint8_t data_length);
    ~HWPort();
    


    // function to send data
    // calls the correct private method
    // and type casts 
    void put_data(uint32_t data);



    // function to recieve the data
    // from a hw port. 
    static const auto get_data();

};





#endif