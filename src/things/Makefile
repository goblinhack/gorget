include ../../build/Makefile.template
COMPILER_FLAGS+=-O0

BUILD_DIR=../../.o

#
# To force clean and avoid "up to date" warning.
#
.PHONY: all clean clobber

SOURCES := $(wildcard */*.cpp) $(wildcard *.S)
OBJECTS :=\
	$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(basename $(SOURCES))))

DEP_FILES := $(OBJECTS:.o=.d)
DEP_FLAGS = -MMD -MP

$(BUILD_DIR): ; mkdir -p $(BUILD_DIR)
$(BUILD_DIR)/world: ; cp .clang-format world/ ; mkdir -p $(BUILD_DIR)/world
$(BUILD_DIR)/dungeon: ; cp .clang-format dungeon/ ; mkdir -p $(BUILD_DIR)/dungeon
$(BUILD_DIR)/player: ; cp .clang-format player/ ; mkdir -p $(BUILD_DIR)/player

$(OBJECTS): | $(BUILD_DIR) \
	$(BUILD_DIR)/world \
	$(BUILD_DIR)/dungeon \
	$(BUILD_DIR)/player

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(DEP_FLAGS) -I ../../src -c -o $@ $<

$(BUILD_DIR)/%.o: %.S
	$(CC) $(DEP_FLAGS) -c -o $@ $<

all: $(OBJECTS)

clean:
	rm -rf $(OBJECTS)

clobber: clean
	rm -f ramdisk_data.cpp $(wildcard ramdisk_data*.S)

# delete corresponding object file if dependency file needs regeneration
$(BUILD_DIR)/%.d: ; @rm -f "$(@:.d=.o)"

# include all dependency files
-include $(DEP_FILES)
