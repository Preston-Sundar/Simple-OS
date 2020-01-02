#ifndef __IO_H
#define __IO_H

/**
 * io.h
 * 
 * Functions to interact with HW devices. 
 * Communicnate with PICs, send bytes to addresses.
 */
#include "types.h"

/**
 * Function to read a byte of data from a HW port.
 * Calls the assembly inb.
 * @param _port 16bit address
 * @return byte of data from address
 */
uint8_t inb(uint16_t _port);

/**
 * Function to send a byte of data to a HW port.
 * Calls the assembly outb.
 * @param _port 16bit address
 * @param _data byte of data
 * @return None
 */
void outb(uint16_t _port, uint8_t _data);


#endif /* io.h */