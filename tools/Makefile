SRC = install-memtest.c
OBJS = install-memtest.o
CC = gcc
AS = as
CFLAGS = -Wall -O0 -g


all:		install-memtest

%.o:		%.s
	$(AS) $< -o $@

install-memtest:	install-memtest.o
	$(CC) $(CFLAGS) -o install-memtest $(OBJS)

depend:		$(SRC)
	gcc -MM $(SRC) > depend

clean:
	rm -f $(OBJS)

scrub:		clean
	rm -f install-memtest

.PHONY:		clean scrub all

include depend

# vim: ts=8 sw=4 noet
