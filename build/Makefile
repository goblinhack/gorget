pre:
	@build/check_files.sh
	@build/ramdisk.py

TOP=$(shell pwd)
DIRS=src

all: pre
	$(foreach var,$(DIRS), $(MAKE) -C $(var) $@; )

format:
	$(foreach var,$(DIRS), (cd $(var); cp $(TOP)/.clang-format .) ;)
	$(foreach var,$(DIRS), (cd $(var); sh $(TOP)/build/tidy_source.sh do) ;)
	$(foreach var,$(DIRS), (cd $(var); sh $(TOP)/build/format.sh do) ;)

clean_files:
	/bin/rm -rf data/sounds/
	/bin/rm -rf data/gfx/
	/bin/rm -rf appdata/
	/bin/rm -f build.log

clean: clean_files
	$(foreach var,$(DIRS), $(MAKE) -C $(var) $@; )

clobber: clean_files
	$(foreach var,$(DIRS), $(MAKE) -C $(var) $@; )

.PHONY: all clean_files clean clobber format pre

.DEFAULT_GOAL := all
