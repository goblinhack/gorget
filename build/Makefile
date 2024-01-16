pre:
	@build/check_files.sh
	@build/ramdisk.py

all: pre
	@if [ ! -f src/Makefile ]; then \
	    (./RUNME;) \
	fi
	(cd src; $(MAKE) $@)

format:
	(cd src ; sh ../build/tidy_source.sh do)
	build/format.sh

tidy:
	build/tidy_source.sh

clean:
	(cd src; $(MAKE) $@)
	/bin/rm -rf data/sounds
	/bin/rm -rf data/gfx
	/bin/rm -rf build.log
	/bin/rm -rf appdata

clobber: clean
	(cd src; $(MAKE) $@)

.PHONY: all clean clobber format tidy pre

.DEFAULT_GOAL := all
