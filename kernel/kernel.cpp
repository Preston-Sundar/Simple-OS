/*NOTES: 
 * when compiling this code, tell compiler that there isnt any os to make calls to
 * and that ther is no glibc. this is done in makefile.
 * 
 * 
 * 
 * 
 * 
 * 
 */ 

void printf(char* str)
{
    // simple printf implementation, takes a string and writes it into video memory


    // store the pointer to start of video memory
    unsigned short* video_memory = (unsigned short*) 0xb8000;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        // preserve the high byte in the video memory as that sets the color
        video_memory[i] = (video_memory[i] & 0xFF00) | str[i];
    }
    

}


/*   main function of our kernal 
 *   accepts the pointer to multiboot and the magic code (no particular reason to take the magic number)
 * 
 *      use extern C to prevent gcc from changing the name
 */


extern "C" void kernal_main(void* multiboot_structure, unsigned int magic_number)
{
    
    // can't use the standard printf as we're outside an OS currently
    // we don't have access to glibc so we write our own printf
    printf("Hello, im the os");

    /* kernal never really stops, inf loop */
    while(1);
}