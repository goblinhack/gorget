pre:
	@build/check_files.sh
	@build/ramdisk.py

TOP=$(shell pwd)
DIRS=plugin/gfx \
		 plugin/things \
		 src

all: pre
	@if [ ! -f src/Makefile ]; then \
	    (./RUNME;) \
	fi
	$(foreach var,$(DIRS), (cd $(var); $(MAKE) $@) ;)

format:
	$(foreach var,$(DIRS), (cd $(var); sh $(TOP)/build/tidy_source.sh do) ;)
	$(foreach var,$(DIRS), (cd $(var); sh $(TOP)/build/format.sh do) ;)

clean:
	$(foreach var,$(DIRS), (cd $(var); $(MAKE) $@) ;)
	/bin/rm -rf data/sounds
	/bin/rm -rf data/gfx
	/bin/rm -rf build.log
	/bin/rm -rf appdata

clobber: clean
	$(foreach var,$(DIRS), (cd $(var); $(MAKE) $@) ;)

.PHONY: all clean clobber format pre

.DEFAULT_GOAL := all
