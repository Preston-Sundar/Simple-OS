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
void printf_boot_message(char *str)
{
        // simple printf implementation, takes a string and writes it into video memory

    // create a cursor to keep track of where to print next in video memory
    static uint8_t cx, cy = 0;

    // create the char and color mask
    static uint16_t mask = (COLOR_BOOT << 8);

    // store the pointer to start of video memory
    static  uint16_t *video_memory = (uint16_t *)0xb8000;

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
            video_memory[SCREEN_X * cy + cx] = (video_memory[SCREEN_X * cy + cx] & mask) | str[i];
            //*video_memory++ = COLOR_BOOT;
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
                    video_memory[SCREEN_X * cy + cx] = (video_memory[SCREEN_X * cy + cx] & mask) | ' ';
                    //*video_memory++ = COLOR_BOOT;
                }
            }
        }
    }
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