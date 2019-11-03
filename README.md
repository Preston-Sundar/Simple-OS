# Simple-Operating System
Creating a simple OS from scratch. My primary resource for this project are the articles on https://wiki.osdev.org. 


## Goal
Learn how operating systems work by implementing one. The end result should support TCP connections, Support graphics and visualizations, and have memory and thread management.

## Bootloader
I have not implemented a bootloader, and instead utilize GNU GRUB to load my kernel. 

## Global Descriptor Table
Created a simple Global Descriptor table that models the following segment:
![alt text](https://github.com/Preston-Sundar/Poop-OS/blob/master/readmeimages/segment-descriptor.png)

Implemented in global_desc_table.cpp with functions to create new segments, retrieve the pointer to a block, check limits, and set flags.

## How to use?
To boot into the OS for testing, I use VirtualBox for a VM and grub-mkrescue to generate a bootable disk image from a given file structure.

Prior to booting, initialize an emty VM within VirtualBox setting all options to 'other' and 64MB of RAM.
Boot into the OS by running the following commands within the kernel direcory:
```console
foo@bar:~/$ git clone https://github.com/Preston-Sundar/Simple-OS.git
foo@bar:~/$ cd Simple-OS/kernel/
foo@bar:~/$ make run
```
