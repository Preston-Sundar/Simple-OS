/**
 * Define the classes specified in hw_port.h.
 */

#include "hw_port.h"

/**
 * Define the parent class.
 */

HWPort::HWPort(uint16_t port_number)
{
    // set the port number
    this->port_number = port_number;
}

HWPort::~HWPort()
{
}

/**
 * HW port that handles byte long data. 
 * Call the constructor of the Parent class. 
 */

HWPort_Byte::HWPort_Byte(uint16_t port_number) : HWPort(port_number)
{
}

HWPort_Byte::~HWPort_Byte()
{
}

void HWPort_Byte::Put(uint8_t data)
{
    // call the outb function, b denotes writing a byte. Pass the params.
    __asm__ volatile("outb %0, %1"
                     :
                     : "a"(data), "Nd"(port_number));
}

uint8_t HWPort_Byte::Get()
{
    uint8_t val = 0;
    // call inb to retreive a value from the port.
    __asm__ volatile("inb %1, %0"
                     : "=a"(val)
                     : "Nd"(port_number));
    return val;
}

/**
 * Slow version of the byte port
 */
HWPort_Byte_Slow::HWPort_Byte_Slow(uint16_t port_number) : HWPort_Byte(port_number)
{

    // set the port number
    this->port_number = port_number;
}

HWPort_Byte_Slow::~HWPort_Byte_Slow()
{
}

void HWPort_Byte_Slow::Put(uint8_t data)
{
    // call the outb function, b denotes writing a byte. Pass the params.
    // this version waits for the port to be done writing the data before return.
    // Safer when chaining calls.
    __asm__ volatile("outb %0, %1\njmp 1f\n1: jmp 1f\n1:"
                     :
                     : "a"(data), "Nd"(port_number));
}

/**
 * Repeat the same process fort the 16 bit reads and writes.
 */

HWPort_Word::HWPort_Word(uint16_t port_number) : HWPort(port_number)
{
}

HWPort_Word::~HWPort_Word()
{
}

void HWPort_Word::Put(uint16_t data)
{
    // call the outb function, w denotes writing a Word. Pass the params.
    __asm__ volatile("outw %0, %1"
                     :
                     : "a"(data), "Nd"(port_number));
}

uint16_t HWPort_Word::Get()
{
    uint16_t val = 0;
    // call inb to retreive a value from the port.
    __asm__ volatile("inw %1, %0"
                     : "=a"(val)
                     : "Nd"(port_number));
    return val;
}

/**
 * Repeat the same process fort the 32 bit reads and writes.
 */

HWPort_DWord::HWPort_DWord(uint16_t port_number) : HWPort(port_number)
{
}

HWPort_DWord::~HWPort_DWord()
{
}

void HWPort_DWord::Put(uint32_t data)
{
    // call the outb function, b denotes writing a Word. Pass the params.
    __asm__ volatile("outl %0, %1"
                     :
                     : "a"(data), "Nd"(port_number));
}

uint32_t HWPort_DWord::Get()
{
    uint32_t val = 0;
    // call inb to retreive a value from the port.
    __asm__ volatile("inl %1, %0"
                     : "=a"(val)
                     : "Nd"(port_number));
    return val;
}
