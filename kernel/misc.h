#ifndef __MISC_H
#define __MISC_H
/**
 * 
 * This headers is used to declare any miscellanious functions. 
 * These functions are really just used to debug when testing new additions.
 * 
 */

#include "types.h"


// define the screen dimenstions (standard)
#define SCREEN_X 80
#define SCREEN_Y 25

// define other colors          
#define COLOR_BLACK             00         
#define COLOR_BLUE              01
#define COLOR_GREEN             02
#define COLOR_CYAN              03
#define COLOR_RED               04
#define COLOR_PURPLE            05
#define COLOR_BROWN             06
#define COLOR_GRAY              07
#define COLOR_LIGHT_BLUE        09
#define COLOR_LIGHT_GREEN       10
#define COLOR_DARK_GRAY         08
#define COLOR_LIGHT_CYAN        11
#define COLOR_LIGHT_RED         12
#define COLOR_LIGHT_PURPLE      13
#define COLOR_YELLOW            14
#define COLOR_WHITE             15

// define the boot color
#define COLOR_BOOT  COLOR_LIGHT_CYAN

/**
 * Simple printf function that uses the VRAM to print DOS chars to the screen.
 * This is not application specific and simple used to print debug related content
 * such as flags and messages.
 */
void printf(char *str);


/**
 * Function to print Boot up related messages using a different color to denote them
 * Same as printf. 
 */
void printf_boot_message(char *str);


/**
 * clears the screen. Used before printing boot related messages.
 * Can be user called as well, but designed to be system only
 */
void clear_screen(void);


#endif