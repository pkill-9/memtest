SRC = start.s
OBJS = start.o
CC = gcc
AS = as
CFLAGS = -fno-hosted -fleading-underscore -nostdlib -Wall --std=c99 -m16


all:		bootsector

%.o:		%.s
	$(AS) $< -o $@

bootsector:	$(OBJS)
	ld --script=link.ld -o bootsector $(OBJS)

clean:
	rm -f $(OBJS)

scrub:		clean
	rm -f bootsector

.PHONY:		clean scrub install all

# vim: ts=8 sw=4 noet
