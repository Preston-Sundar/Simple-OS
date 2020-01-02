 
/* This file specifies the sizes of primitives to the sake of integrity across compilers.
*  Use these types consistently throughout code base.
*
*
*
*/

#ifndef __TYPES_H
#define __TYPES_H

// Define the various int types
typedef char int8_t;
typedef unsigned char uint8_t;

typedef short int16_t;
typedef unsigned short uint16_t;

typedef int int32_t;
typedef unsigned int uint32_t;

typedef long long int int64_t;
typedef unsigned long long int uint64_t;

typedef unsigned int size_t;

#endif