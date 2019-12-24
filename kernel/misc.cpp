/**
 * 
 * This file is used to define any miscellanious functions. 
 * These functions are really just used to debug when testing new additions.
 * 
 */

#include "misc.h"

/**
 * Simple printf function that uses the VRAM to print DOS chars to the screen.
 * This is not application specific and simple used to print debug related content
 * such as flags and messages.
 */
void printf(char *str)
{
    // simple printf implementation, takes a string and writes it into video memory

    // create a cursor to keep track of where to print next in video memory
    static uint8_t cx, cy = 0;

    // store the pointer to start of video memory
    static uint16_t *video_memory = (uint16_t *)0xb8000;

    for (int i = 0; str[i] != '\0'; ++i)
    {

        if (str[i] == '\n')
        {
            // move the next line
            cy++;
            cx = 0;
        }

        else
        {
            // preserve the high byte in the video memory as that sets the color
            video_memory[SCREEN_X * cy + cx] = (video_memory[SCREEN_X * cy + cx] & 0xFF00) | str[i];
            cx++;
        }

        if (cx >= SCREEN_X)
        {
            // if we're out of space on screen
            // move to the next row
            cy++;
            // reset the counter on x axis
            cx = 0;
        }

        if (cy >= SCREEN_Y)
        {

            // empty the screen
            for (cy = 0; cy < SCREEN_Y; cy++)
            {
                for (cx = 0; i < SCREEN_X; cx++)
                {
                    video_memory[SCREEN_X * cy + cx] = (video_memory[SCREEN_X * cy + cx] & 0xFF00) | ' ';
                }
            }
        }
    }
}



/**
 * Function to print Boot up related messages using a different color to denote them
 * Same as printf. 
 */
void print_skeleton(void)
{
        // simple printf implementation, takes a string and writes it into video memory

    // create a cursor to keep track of where to print next in video memory
    static uint8_t cx = KERNEL_MSG_X;
    static uint8_t cy = KERNEL_MSG_Y;


    // create the char and color mask
    static uint16_t mask = (COLOR_SKELETON << 8);

    // store the pointer to start of video memory
    static  uint16_t *video_memory = (uint16_t *)0xb8000;

    video_memory[SCREEN_X * cy + cx] = (video_memory[SCREEN_X * cy + cx] & mask) | 's';
    video_memory[SCREEN_X * cy + (cx + 1)] = (video_memory[SCREEN_X * cy + cx] & mask) | ':';


    video_memory[SCREEN_X * cy + (cx + 25)] = (video_memory[SCREEN_X * cy + cx] & mask) | '|';
    video_memory[SCREEN_X * cy + (cx + 26)] = (video_memory[SCREEN_X * cy + cx] & mask) | ' ';
    video_memory[SCREEN_X * cy + (cx + 27)] = (video_memory[SCREEN_X * cy + cx] & mask) | 'm';
    video_memory[SCREEN_X * cy + (cx + 28)] = (video_memory[SCREEN_X * cy + cx] & mask) | ':';


    video_memory[SCREEN_X * cy + (cx + 55)] = (video_memory[SCREEN_X * cy + cx] & mask) | '|';    
    video_memory[SCREEN_X * cy + (cx + 56)] = (video_memory[SCREEN_X * cy + cx] & mask) | ' ';    
    video_memory[SCREEN_X * cy + (cx + 57)] = (video_memory[SCREEN_X * cy + cx] & mask) | 'e';    
    video_memory[SCREEN_X * cy + (cx + 58)] = (video_memory[SCREEN_X * cy + cx] & mask) | 'r';    
    video_memory[SCREEN_X * cy + (cx + 59)] = (video_memory[SCREEN_X * cy + cx] & mask) | 'r';    
    video_memory[SCREEN_X * cy + (cx + 60)] = (video_memory[SCREEN_X * cy + cx] & mask) | ':';    


}



/**
 * clears the screen. Used before printing boot related messages.
 * Can be user called as well, but designed to be system only
 */
void clear_screen(void)
{

    // store the pointer to start of video memory
    static  uint16_t *video_memory = (uint16_t *)0xb8000;
    uint8_t cx, cy;

    for (cy = 0; cy < SCREEN_Y; cy++)
    {
        for (cx = 0; cx < SCREEN_X; cx++)
        {
            video_memory[SCREEN_X * cy + cx] = (video_memory[SCREEN_X * cy + cx] & 0xFF00) | ' ';
            //*video_memory++ = COLOR_BOOT;
        }
    }
}


/**
 * Function to initilaize the screen and print the status skeleton
 * System called
 */
void init_screen(void)
{
    
    // clear the screen
    clear_screen();

    // print the skeleton for the status bar
    print_skeleton();


}


/**
 * Prints a message in the message section of the sekeleton
 * useful for running process to output stuff in a neat way
 */
void printf_skeleton_message(char *str, uint8_t section_id)
{

    uint16_t color = COLOR_WHITE;

    static uint8_t cx = 0;
    static uint8_t cy = KERNEL_MSG_Y;


    // determine where to print within the skeleton 
    switch (section_id)
    {
    case 0:
        
        // its a state string
        color = COLOR_STATE;
        cx = K_STATE_X;

        break;

    case 1:

        // its a message string
        color = COLOR_MESSAGE;
        cx = K_MESSAGE_X;

        break;

    case 2:

        // its an error string
        color = COLOR_ERROR;
        cx = K_ERROR_X;
    
        break;

    default:
        break;
    }



    // create the char and color mask
    uint16_t mask = (color << 8);

    // store the pointer to start of video memory
    static  uint16_t *video_memory = (uint16_t *)0xb8000;

    for (int i = 0; str[i] != '\0'; ++i)
    {

        if (str[i] == '\n')
        {
            
            // go to start of the line
            cx = 0;
        }

        else
        {
            // preserve the high byte in the video memory as that sets the color
            video_memory[SCREEN_X * cy + cx] = (video_memory[SCREEN_X * cy + cx] & mask) | str[i];
            //*video_memory++ = COLOR_BOOT;
            cx++;
        }

        if (cx >= SCREEN_X)
        {

            // reset the counter on x axis
            cx = 0;
        }
    }
}