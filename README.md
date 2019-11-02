# Simple-Operating System
Creating a simple OS from scratch. My primary rescourse 


## Goal
Learn how operating systems work by implementing one. The end result should support TCP connections, Support graphics and visualizations, and have memory and thread management.

## Bootloader
I have not implemented a bootloader, and instead utilize GNU GRUB to load my kernel. 

## Global Descriptor Table
Created a simple Global Descriptor table that models the following segment:
![alt text](https://github.com/Preston-Sundar/Poop-OS/blob/master/readmeimages/segment-descriptor.png)

Implemented in global_desc_table.cpp with functions to create new segments, retrieve the pointer to a block, check limits, and set flags.

