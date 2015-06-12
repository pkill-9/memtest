SRC = memtest.c output.c
OBJS = memtest.o output.o bios.o
CC = gcc
AS = as
CFLAGS = -fno-hosted -fleading-underscore -nostdlib -Wall --std=c99 -m16


all:		memtest.bin

%.o:		%.s
	$(AS) $< -o $@

memtest.bin:	depend $(OBJS)
	ld --script=link.ld -o memtest.bin $(OBJS)

depend:		$(SRC)
	gcc -MM $(SRC) > depend

clean:
	rm -f $(OBJS)

scrub:		clean
	rm -f memtest.bin cscope.out depend

tags:
	cscope -b

.PHONY:		clean scrub tags all

include depend

# vim: ts=8 sw=4 noet
