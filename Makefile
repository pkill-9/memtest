OBJS = memtest.o output.o bios.o
CC = gcc
AS = as
CFLAGS = -fno-hosted -fleading-underscore -nostdlib -Wall --std=c99 -m16


all:		install

%.o:		%.s
	$(AS) $< -o $@

memtest.bin:	$(OBJS)
	ld --script=link.ld -o memtest.bin $(OBJS)

disk.hdd:
	dd if=/dev/zero of=disk.hdd bs=1 count=0 seek=1GB

install:	disk.hdd memtest.bin 
	dd conv=notrunc if=memtest.bin of=disk.hdd bs=512 count=1

clean:
	rm -f $(OBJS)

scrub:		clean
	rm -f disk.hdd memtest.bin

.PHONY:		clean scrub install all

# vim: ts=8 sw=4 noet
