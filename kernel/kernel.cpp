/*NOTES: 
 * when compiling this code, tell compiler that there isnt any os to make calls to
 * and that ther is no glibc. this is done in makefile.
 * 
 * Use the datatypes universalized in types.h
 * 
 * 
 * 
 * 
 */

#include "types.h"
#include "global_desc_table.h"

#define SCREEN_X 80
#define SCREEN_Y 25

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

/* get the pointers to the contructors, filled in by linker 
 * between the pointers start_ctors and end_ctors lies function pointers 
 * placed there by the linker, execute these functions. 
 *
 */
typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void call_constructors()
{
    for (constructor *i = &start_ctors; i != &end_ctors; i++)
    {
        // call the function
        (*i)();
    }
}

/*   main function of our kernal 
 *   accepts the pointer to multiboot and the magic code (no particular reason to take the magic number)
 * 
 *      use extern C to prevent gcc from changing the name
 */

extern "C" void kernel_main(void *multiboot_structure, uint32_t magic_number)
{

    // can't use the standard printf as we're outside an OS currently
    // we don't have access to glibc so we write our own printf
    printf("Hello, WELCOME TO PoopOS's kernel.....so what now?\n");
    printf("Hello, WELCOME TO PoopOS's kernel.....so what now?");

    GlobalDescriptorTable gdt;

    /* kernal never really stops, inf loop */
    while (1)
        ;
}
