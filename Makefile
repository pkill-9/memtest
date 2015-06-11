all:		install

# make rules for subdirectories.
bootsector:
	$(MAKE) -C bootsector

memtest:
	$(MAKE) -C memtest

tools:
	$(MAKE) -C tools

disk.hdd:
	dd if=/dev/zero of=disk.hdd bs=1 count=0 seek=1GB

install:	disk.hdd bootsector memtest tools
	dd conv=notrunc if=bootsector/bootsector of=disk.hdd bs=512 count=1

clean:
	rm -f $(OBJS)

scrub:		clean
	rm -f disk.hdd

.PHONY:		clean scrub install all bootsector memtest tools

# vim: ts=8 sw=4 noet
