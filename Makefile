# TOOLS_PATH = /home/terence/dev/tools

#------------------------------
# Argument Validation
#------------------------------
ifeq ($(HW),LAUNCHPAD)
  TARGET_HW := launchpad
else ifeq ($(HW),NSUMO)
  TARGET_HW := nsumo
else ifeq ($(MAKECMDGOALS),clean)
else ifeq ($(MAKECMDGOALS),cppcheck)
else ifeq ($(MAKECMDGOALS),format)
else
  $(error Must pass HW=LAUNCHPAD or HW=NSUMO)
endif

# Override TARGET_NAME if TEST is set
TARGET_NAME := $(TARGET_HW)
ifneq ($(TEST),)
  ifeq ($(filter test_%,$(TEST)),)
    $(error TEST=$(TEST) is invalid (test function must start with test_))
  else
    TARGET_NAME := $(TEST)
  endif
endif

#------------------------------
# Directories
#------------------------------
TOOLS_DIR := $(TOOLS_PATH)
MSPGCC_ROOT_DIR := $(TOOLS_DIR)/msp430-gcc
MSPGCC_BIN_DIR := $(MSPGCC_ROOT_DIR)/bin
MSPGCC_INCLUDE_DIR := $(MSPGCC_ROOT_DIR)/include

BUILD_DIR := build/$(TARGET_NAME)
OBJ_DIR := $(BUILD_DIR)/obj
BIN_DIR := $(BUILD_DIR)/bin/$(TARGET_HW)

TI_CCS_DIR := $(TOOLS_DIR)/ccs2020/ccs
DEBUG_BIN_DIR := $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR := $(TI_CCS_DIR)/ccs_base/DebugServer/drivers

#------------------------------
# Toolchain & Tools
#------------------------------
CC := $(MSPGCC_BIN_DIR)/msp430-elf-gcc
RM := rm -rf
DEBUG := LD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug
CPPCHECK := cppcheck
FORMAT := clang-format

#------------------------------
# Files & Sources
#------------------------------
TARGET := $(BIN_DIR)/$(TARGET_NAME)

ifeq ($(TEST),)
  SOURCES := \
    src/main.c \
    src/drivers/i2c.c \
    src/app/drive.c \
    src/app/io.c \
    src/drivers/mcu_init.c \
    src/common/assert_handler.c \
    src/drivers/led.c
else
  SOURCES := \
    src/test/test.c \
    src/app/drive.c \
    src/app/io.c \
    src/drivers/i2c.c \
    src/drivers/mcu_init.c \
    src/common/assert_handler.c \
    src/drivers/led.c
endif

OBJECT_NAMES := $(notdir $(SOURCES:.c=.o))
OBJECTS := $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

vpath %.c src src/drivers src/app src/common src/test

#------------------------------
# Preprocessor Defines
#------------------------------
HW_DEFINE := $(addprefix -D,$(HW))
TEST_DEFINE := $(addprefix -DTEST=,$(TEST))
DEFINES := $(HW_DEFINE) $(TEST_DEFINE)

#------------------------------
# Compilation Flags
#------------------------------
MCU := msp430g2553
WFLAGS := -Wall -Wextra -Werror -Wshadow
CFLAGS := -mmcu=$(MCU) $(WFLAGS) -fshort-enums -I$(MSPGCC_INCLUDE_DIR) $(DEFINES) -Isrc -Og -g
LDFLAGS := -mmcu=$(MCU) $(DEFINES) -L$(MSPGCC_INCLUDE_DIR)

#------------------------------
# Default Target
#------------------------------
all: $(TARGET)

#------------------------------
# Link Target
#------------------------------
$(TARGET): $(OBJECTS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $^ -o $@

#------------------------------
# Compile Objects
#------------------------------
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

#------------------------------
# Utility Targets
#------------------------------
.PHONY: all clean flash cppcheck format

clean:
	$(RM) $(BUILD_DIR)

flash: $(TARGET)
	$(DEBUG) tilib "prog $(TARGET)"

cppcheck:
	$(CPPCHECK) $(SOURCES)

format:
	$(FORMAT) -i $(SOURCES)
