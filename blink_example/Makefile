# Directories
MSPGCC_DIR = /home/terence/Downloads/msp430-gcc-9.3.1.11_linux64
MSPGCC_ROOT_DIR = /home/terence/Downloads/msp430-gcc-support-files
MSPGCC_BIN_DIR = $(MSPGCC_DIR)/bin
MSPGCC_INCLUDE_DIR = $(MSPGCC_ROOT_DIR)/include

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

TI_CCS_DIR = /home/terence/ti/ccs2020/ccs
DEBUG_BIN_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/drivers

# Toolchain
CC = $(MSPGCC_BIN_DIR)/msp430-elf-gcc
RM = rm
DEBUG = LD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug

# Files
TARGET = $(BIN_DIR)/blink

SOURCES = main.c led.c

OBJECT_NAMES = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(OBJ_DIR)/%,$(OBJECT_NAMES))

# Flags
MCU = msp430g2553
WFLAGS = -Wall -Wextra -Werror -Wshadow
CFLAGS = -mmcu=$(MCU) $(WFLAGS) -I$(MSPGCC_INCLUDE_DIR) -Og -g
LDFLAGS = -mmcu=$(MCU) -L$(MSPGCC_INCLUDE_DIR)

# Default rule
all: $(TARGET)

# Linking
$(TARGET): $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(LDFLAGS) $^ -o $@

# Compiling
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Phonies 
.PHONY: all clean flash

all: $(TARGET)

clean:
	$(RM) -r $(BUILD_DIR)

flash: $(TARGET)
	$(DEBUG) tilib "prog $(TARGET)"