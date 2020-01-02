#include "../include/io.h"

/**
 * io.h
 * 
 * Functions to interact with HW devices. 
 * Communicnate with PICs, send bytes to addresses.
 */

/**
 * Function to read a byte of data from a HW port.
 * Calls the assembly inb.
 */
uint8_t inb(uint16_t _port)
{
    uint8_t rv;
    __asm__ __volatile__("inb %1, %0"
                         : "=a"(rv)
                         : "dN"(_port));
    return rv;
}

/**
 * Function to send a byte of data to a HW port.
 * Calls the assembly outb.
 */
void outb(uint16_t _port, uint8_t _data)
{
    __asm__ __volatile__("outb %1, %0"
                         :
                         : "dN"(_port), "a"(_data));
}

