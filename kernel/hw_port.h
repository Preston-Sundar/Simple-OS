#ifndef __HW_PORT_H
#define __HW_PORT_H

#include "types.h"

/**
 * Set of classes to handle putting and getting byte lengths of data from harware ports.
 * Define a prent class that implements functions for all the classes, then define the child classes, 
 * where in that actual varying lengths are managed.
 */


class HWPort
{

    protected:
        
        //16 bit port number
        uint16_t port_number;

        //define the constructor and destructors
        HWPort(uint16_t port_number);
        ~HWPort();

};


/**
 * HW port that handles byte long data. 
 */


class HWPort_Byte : public HWPort
{
    public:
        //define the constructor and destructors
        HWPort_Byte(uint16_t port_number);
        ~HWPort_Byte();

        //method to write to port
        virtual void Put(uint8_t data);


        //method to read from port, returns a byte
        virtual uint8_t Get();
};


/**
 * Slow version of the 8 bit port
 */

class HWPort_Byte_Slow : public HWPort_Byte
{
    public:
        //define the constructor and destructors
        HWPort_Byte_Slow(uint16_t port_number);
        ~HWPort_Byte_Slow();

        //method to write to port
        virtual void Put(uint8_t data);
};



class HWPort_Word : public HWPort
{
    public:
        //define the constructor and destructors
        HWPort_Word(uint16_t port_number);
        ~HWPort_Word();

        //method to write to port
        virtual void Put(uint16_t data);


        //method to read from port, returns a word
        virtual uint16_t Get();
};


class HWPort_DWord : public HWPort
{
    public:
        //define the constructor and destructors
        HWPort_DWord(uint16_t port_number);
        ~HWPort_DWord();

        //method to write to port
        virtual void Put(uint32_t data);


        //method to read from port, returns a Dword
        virtual uint32_t Get();

};


#endif