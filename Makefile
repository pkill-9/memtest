SUBDIRS = bootsector memtest tools

all:		install

# make rules for subdirectories.
$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

disk.hdd:
	dd if=/dev/zero of=disk.hdd bs=1 count=0 seek=1GB

install:	disk.hdd $(SUBDIRS)
	dd conv=notrunc if=bootsector/bootsector of=disk.hdd bs=512 count=1
	./tools/install-memtest memtest/memtest.bin disk.hdd

clean:		$(SUBDIRS)

scrub:		clean $(SUBDIRS)
	rm -f disk.hdd

.PHONY:		clean scrub install all $(SUBDIRS)

# vim: ts=8 sw=4 noet
