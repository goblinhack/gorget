include ../build/Makefile.template

NAME=yelindor
BUILD_DIR=../.o

TARGET_GAME=$(NAME)$(EXE)
SRC_DIR=.

#
# To force clean and avoid "up to date" warning.
#
.PHONY: all clean clobber

all: $(TARGET_GAME)

SOURCES := $(wildcard *.cpp) $(wildcard */*.cpp) $(wildcard */*/*.cpp) $(wildcard *.S)
OBJECTS :=\
	$(addprefix $(BUILD_DIR)/,$(addsuffix .o,$(basename $(SOURCES))))

DEP_FILES := $(OBJECTS:.o=.d)
DEP_FLAGS = -MMD -MP

$(BUILD_DIR)/things/world: ; mkdir -p $(BUILD_DIR)/things/world
$(OBJECTS): | $(BUILD_DIR)/things/world

$(BUILD_DIR)/things/player: ; mkdir -p $(BUILD_DIR)/things/player
$(OBJECTS): | $(BUILD_DIR)/things/player

$(BUILD_DIR)/things/dungeon: ; mkdir -p $(BUILD_DIR)/things/dungeon
$(OBJECTS): | $(BUILD_DIR)/things/dungeon

$(BUILD_DIR): ; mkdir -p $(BUILD_DIR)
$(OBJECTS): | $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.cpp
	$(CC) $(CFLAGS) $(DEP_FLAGS) -c -o $@ $<

$(BUILD_DIR)/%.o: %.S
	$(CC) $(DEP_FLAGS) -c -o $@ $<

$(TARGET_GAME): $(OBJECTS)
	cd $(BUILD_DIR); $(CC) $(LDFLAGS) *.o */*/*.o $(LDLIBS) -o $(TARGET_GAME)
	cp -f $(BUILD_DIR)/$(NAME)* ..

tidy:
	for src in $(SOURCES) ; do \
		echo "Running tidy on $$src..." ; \
		clang-tidy -fix -checks="-*,bugprone-sizeof-expression,cppcoreguidelines-no-malloc,misc-redundant-expression,modernize-loop-convert,modernize-use-auto,modernize-use-nullptr,modernize-use-default-member-init,modernize-use-equals-default,modernize-use-equals-delete,modernize-use-nullptr,readability-else-after-return,readability-else-after-return,readability-redundant-member-init,readability-redundant-member-init,readability-simplify-boolean-expr" -header-filter=".*" "$(SRC_DIR)/$$src" -- $(CFLAGS); \
	done
	@echo "Done"

.PHONY: style check-style tidy

clean:
	rm -f ../$(TARGET_GAME) ../stdout.txt ../stderr.txt
	rm -f $(TARGET_GAME) stdout.txt stderr.txt
	rm -rf $(BUILD_DIR)

clobber: clean
	rm -f ramdisk_data.cpp $(wildcard ramdisk_data*.S)

# delete corresponding object file if dependency file needs regeneration
$(BUILD_DIR)/%.d: ; @rm -f "$(@:.d=.o)"

# include all dependency files
-include $(DEP_FILES)
