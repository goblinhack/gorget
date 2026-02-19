include ../build/Makefile.template

#
# For incremental builds, this is a lot faster
#
#ifeq ($(origin USE_PRECOMPILED),undefined)
#COMPILER_FLAGS+=-O0
#endif

NAME=gorget
BUILD_DIR=../.o

TARGET_GAME=../$(NAME)$(EXE)
SRC_DIR=.

#
# To force clean and avoid "up to date" warning.
#
.PHONY: all clean clobber

all: $(TARGET_GAME)

# function to make object names from source files
# (changes suffix to .o, encodes directory names so subdirectories in build dir aren't necessary)
obj_name = $(addsuffix .o,$(subst /,__,$(subst ../,,$(basename $1))))

# recursively search all src/ subdirectories for cpp source files
CPP_SOURCES := $(subst ./,,$(shell find $(SRC_DIR) -name \*.cpp -not -path "*3rdparty*"))
CPP_3RD_PARTY_SOURCES := $(subst ./,,$(shell find $(SRC_DIR)/3rdparty -name \*.cpp))
ASM_SOURCES := $(wildcard *.S)
SOURCES := $(CPP_3RD_PARTY_SOURCES) $(CPP_SOURCES) $(ASM_SOURCES)

OBJECTS := $(call obj_name,$(SOURCES))
OBJ_FILES := $(addprefix $(BUILD_DIR)/,$(OBJECTS))

DEP_FILES := $(OBJ_FILES:.o=.d)
DEP_FLAGS = -MMD -MP

CFLAGS := -I. $(COMPILER_FLAGS) $(COMPILER_WARNINGS) $(DEP_FLAGS)

$(BUILD_DIR): ; mkdir -p $(BUILD_DIR)
$(OBJ_FILES): | $(BUILD_DIR)

# custom compile command for each source file needed because object file
# base names don't match source files that were in src/ subdirectories

PRECOMPILED_H := precompiled.hpp
PRECOMPILED_H_OBJ := $(PRECOMPILED_H).gch

#
# Must use the same flags as normal .cpp files for precompiled
#
%.hpp.gch: $(PRECOMPILED_H)
		$(CC) $(CFLAGS) -c -o $@ $<

#
# Precompiled headers are good for the initial build, but after that it
# is faster to use dependancies
#
ifeq ($(origin USE_PRECOMPILED),undefined)

$(foreach x,$(CPP_SOURCES),\
$(eval $(BUILD_DIR)/$(call obj_name,$x): $x ;\
  $(CC) $(CFLAGS) -c -o $$@ $$<))

else

$(foreach x,$(CPP_SOURCES),\
$(eval $(BUILD_DIR)/$(call obj_name,$x): $x | $(PRECOMPILED_H_OBJ) ;\
  $(CC) -include $(PRECOMPILED_H) $(CFLAGS) -c -o $$@ $$<))

endif

$(foreach x,$(CPP_3RD_PARTY_SOURCES),\
$(eval $(BUILD_DIR)/$(call obj_name,$x): $x ;\
  $(CC) $(CFLAGS) -c -o $$@ $$<))

$(foreach x,$(ASM_SOURCES),\
$(eval $(BUILD_DIR)/$(call obj_name,$x): $x ;\
  $(CC) $(CFLAGS) -c -o $$@ $$<))

# use file list instead of wildcard for link command so we don't accidentally
# link with old object files for removed source files
$(TARGET_GAME): $(OBJ_FILES)
	cd $(BUILD_DIR); $(CC) $(OBJECTS) $(LDLIBS) $(LDFLAGS) -o $(TARGET_GAME); $(DSYM)

#####################################################
# to show options:
# clang-tidy -checks=* -list-checks
#
# This is good, but introduces some errors in macros
#			bugprone-*,\
#####################################################
tidy:
	for src in $(CPP_SOURCES) ; do \
		echo "Running tidy on $$src..." ; \
		clang-tidy -fix -checks="-*,\
			performance-*,\
			cppcoreguidelines-no-malloc,\
			misc-redundant-expression,\
			modernize-avoid-bind,\
			modernize-avoid-c-arrays,\
			modernize-concat-nested-namespaces,\
			modernize-deprecated-headers,\
			modernize-deprecated-ios-base-aliases,\
			modernize-loop-convert,\
			modernize-macro-to-enum,\
			modernize-make-shared,\
			modernize-make-unique,\
			modernize-min-max-use-initializer-list,\
			modernize-pass-by-value,\
			modernize-raw-string-literal,\
			modernize-redundant-void-arg,\
			modernize-replace-auto-ptr,\
			modernize-replace-disallow-copy-and-assign-macro,\
			modernize-replace-random-shuffle,\
			modernize-return-braced-init-list,\
			modernize-shrink-to-fit,\
			modernize-type-traits,\
			modernize-unary-static-assert,\
			modernize-use-auto,\
			modernize-use-bool-literals,\
			modernize-use-constraints,\
			modernize-use-default-member-init,\
			modernize-use-designated-initializers,\
			modernize-use-emplace,\
			modernize-use-equals-default,\
			modernize-use-equals-delete,\
			modernize-use-integer-sign-comparison,\
			modernize-use-nodiscard,\
			modernize-use-noexcept,\
			modernize-use-nullptr,\
			modernize-use-override,\
			modernize-use-ranges,\
			modernize-use-starts-ends-with,\
			modernize-use-std-format,\
			modernize-use-std-numbers,\
			modernize-use-std-print,\
			modernize-use-using,\
			readability-*" \
			-header-filter=".*" "$(SRC_DIR)/$$src" -- $(CFLAGS); \
	done
	git checkout 3rdparty
	git checkout my_cfg.hpp # avoids enum errors
	@echo "Done"

.PHONY: style check-style tidy

clean:
	rm -f $(TARGET_GAME) ../stdout.txt ../stderr.txt
	@# safer delete of build dir instead of just 'rm -rf $(BUILD_DIR)'
	rm -f $(BUILD_DIR)/*.[od]
	@([ -d "$(BUILD_DIR)" ] && rmdir $(BUILD_DIR) 2>/dev/null) || true

clobber: clean
	rm -f ramdisk_data.cpp $(wildcard ramdisk_data*.S) $(wildcard *.gch)

# delete corresponding object file if dependency file needs regeneration
$(BUILD_DIR)/%.d: ; @rm -f "$(@:.d=.o)"

# include all dependency files
-include $(DEP_FILES)
