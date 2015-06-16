# Memtest
Bootloader and real mode programming demo

# How to use it
There is a makefile provided to automatically build binaries, and set them 
up on a disk image file named disk.hdd. To construct all of this, open up 
your terminal, cd to the root directory of this repository and run the 
command "make".

The disk image file can then be used with virtual machine software such as 
VirtualBox.

Note that this project is *not* an operating system.

# Source code organisation
The source code is split over three directories, for three quite different 
tasks.

Code for the bootsector is contained in bootsector/, which is written 
entirely in assembly, compatible with the GNU assembler. This is kept very 
simple; no filesystem is used, the bootsector loads a number of sectors 
starting immediately after the bootsector on the disk into memory, then 
starts executing them. The number of sectors to be loaded is implanted 
into the bootsector at install time by a special purpose program contained 
in the tools/ directory.

The program that the bootsector loads is contained in the memtest/ 
directory, and is compiled into a flat binary format, the same as for the 
bootsector. This format means that the bootsector does not need to 
understand anything about executable file formats, keeping things simple.

The memtest program will make use of BIOS calls to obtain information 
about what memory is available on the computer, then print the information 
on the screen, also with BIOS calls.
