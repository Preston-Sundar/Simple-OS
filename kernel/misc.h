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


// define the positions for the messages
#define K_STATE_X    3
#define K_MESSAGE_X  30
#define K_ERROR_X    67


//                   0123456789012345678901234567890123   
// bottom of screen: s: (STATE) | m: (message) | err: (error)
// define boundries for the lower line of text
// here is where all the kernel related messages are printed
#define KERNEL_MSG_X 0
#define KERNEL_MSG_Y 24



// define other colors          
#define COLOR_BLACK             00         
#define COLOR_BLUE              01
#define COLOR_GREEN             02
#define COLOR_CYAN              03
#define COLOR_RED               04
#define COLOR_PURPLE            05
#define COLOR_BROWN             06
#define COLOR_GRAY              07
#define COLOR_DARK_GRAY          8
#define COLOR_LIGHT_BLUE         9
#define COLOR_LIGHT_GREEN       10
#define COLOR_LIGHT_CYAN        11
#define COLOR_LIGHT_RED         12
#define COLOR_LIGHT_PURPLE      13
#define COLOR_YELLOW            14
#define COLOR_WHITE             15

// define the boot color
#define COLOR_SKELETON COLOR_YELLOW
#define COLOR_MESSAGE  COLOR_LIGHT_PURPLE
#define COLOR_STATE    COLOR_LIGHT_GREEN
#define COLOR_ERROR    COLOR_RED

// define the varous print states
// for the skeleton
#define PRINT_STATE     0
#define PRINT_MESSAGE   1
#define PRINT_ERROR     2



/**
 * Simple printf function that uses the VRAM to print DOS chars to the screen.
 * This is not application specific and simple used to print debug related content
 * such as flags and messages.
 */
void printf(char *str);


/**
 * Function to print Boot up related messages using a different color to denote them
 * prints to the bottom line of the screen, as that's reserved for kernel related messages
 * prints into the message section of the skeleton
 */
void print_skeleton(void);


/**
 * Prints a message in the message section of the sekeleton
 * useful for running process to output stuff in a neat way
 * sectiond_id specified which field to input the data into
 * 0: state 1: message 2: error
 */
void printf_skeleton_message(char *str, uint8_t section_id);


/**
 * clears the screen. Used before printing boot related messages.
 * Can be user called as well, but designed to be system only
 */
void clear_screen(void);

/**
 * Function to initilaize the screen and print the status skeleton
 * System called
 */
void init_screen(void);

#endif