/**
 *  C program to install the memory testing program onto a specified disk
 *  image file.
 *
 *  This program is to be given two command line arguments, for the memory
 *  test binary file, and the disk image file. It will then skip over the
 *  first 512 bytes of the image file (the bootsector) and will copy the
 *  memtest program into the disk image following the bootsector, 
 *  overwriting any existing data. The memtest program is copied in sector
 *  increments. Once this copy is complete, this program will seek back
 *  into the bootsector and will write in the number of sectors that were
 *  copied at the end of the bootsector, so that the bootsector knows how
 *  many sectors it needs to load.
 */

#include <stdio.h>
#include <stdlib.h>
#include <err.h>

#include "utils.h"

#define BYTES_PER_SECTOR        512

/**********************************************************/

PRIVATE void print_usage (void);
PRIVATE void initialise_files (const char *memtest, const char *image);
PRIVATE void write_sector_count (int bytes_copied);
PRIVATE void close_files (void);

/**********************************************************/

/**
 *  File handles for the compiled binary machine code for the memtest
 *  program, and for the disk image file onto which it is to be copied.
 */
PRIVATE FILE *memtest_fd = NULL;
PRIVATE FILE *disk_fd = NULL;

/**********************************************************/

    int
main (argc, argv)
    int argc;
    char **argv;
{
    int bytes_copied = 0, next_byte;

    // expect two command line params.
    if (argc != 3)
        print_usage ();

    initialise_files (argv [1], argv [2]);

    // read from the memtest program and write to the disk image.
    while ((next_byte = fgetc (memtest_fd)) != EOF)
    {
        fputc (next_byte, disk_fd);
        bytes_copied ++;
    }

    // now write in the number of sectors that the memtest program takes
    // up, which we can calculate simply from the number of bytes copied.
    write_sector_count (bytes_copied);

    // all done.
    close_files ();

    return 0;
}

/**********************************************************/

/**
 *  Calculate the number of sectors that the memtest program takes up on
 *  the disk image, and write that value into the bootsector, immediately
 *  before the boot signature.
 */
    PRIVATE void
write_sector_count (bytes_copied)
    int bytes_copied;           // number of bytes in the memtest program
{
    int numsectors = bytes_copied / BYTES_PER_SECTOR;

    // check if the program runs onto a part sector.
    if (bytes_copied % BYTES_PER_SECTOR != 0)
        numsectors ++;

    // seek the disk image to the correct offset in the bootsector. The
    // boot signature is two bytes at 510 and 511, so we want to seek to
    // offset 509.
    fseek (disk_fd, 512 - 3, SEEK_SET);
    fputc (numsectors, disk_fd);
}

/**********************************************************/

/**
 *  Opens the memtest program file and the disk image file, and seeks over
 *  the bootsector in the disk image.
 */
    PRIVATE void
initialise_files (memtest, image)
    const char *memtest;        // path to the memtest program file.
    const char *image;          // path to the disk image file.
{
    // open the files to be writable, without truncating them.
    memtest_fd = fopen (memtest, "r");
    disk_fd = fopen (image, "r+");

    // seek over the bootsector in the disk image file.
    if (fseek (disk_fd, 512, SEEK_SET) == -1)
        err (1, "Could not seek on disk image");
}

/**********************************************************/

/**
 *  Close the two file descriptors.
 */
    PRIVATE void
close_files (void)
{
    fclose (memtest_fd);
    fclose (disk_fd);
}

/**********************************************************/

/**
 *  Print a usage message and exit the program.
 */
    PRIVATE
void print_usage (void)
{
    printf ("install-memtest: Tool for installing a simple program on a\n"
      "bootable disk, without a structured file system. Usage:\n\n"
      "install-memtest <memtest> <disk>\n\n"
      "Where memtest is the path to the program file to be copied onto\n"
      "the disk and disk is the path to the disk image file.\n");
}

/**********************************************************/

/** vim: set ts=4 sw=4 et : */
