SRC = start.s
OBJS = start.o
CC = gcc
AS = as
CFLAGS = -fno-hosted -fleading-underscore -nostdlib -Wall --std=c99 -m16


all:		bootsector

%.o:		%.s
	$(AS) $< -o $@

bootsector:	depend $(OBJS)
	ld --script=link.ld -o bootsector $(OBJS)

depend:		$(SRC)
	gcc -MM $(SRC) > depend

clean:
	rm -f $(OBJS)

scrub:		clean
	rm -f bootsector

.PHONY:		clean scrub install all

include depend

# vim: ts=8 sw=4 noet
