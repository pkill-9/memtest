SRC = configure.c
CC = gcc
AS = as
CFLAGS = -Wall --std=c99 -m 16


all:		install

%.o:		%.s
	$(AS) $< -o $@

hello.bin:	x86-hello.o
	ld --script=link.ld x86-hello.o -o hello.bin

disk.hdd:
	dd if=/dev/zero of=disk.hdd bs=1 count=0 seek=1GB

install:	disk.hdd hello.bin 
	dd conv=notrunc if=hello.bin of=disk.hdd bs=512 count=1

clean:
	rm -f x86-hello.o hello.bin disk.hdd

.PHONY:		clean install all

# vim: ts=8 sw=4 noet
