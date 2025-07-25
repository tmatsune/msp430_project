# === Paths ===
TOOLS_PATH       = /home/terence/dev/tools
MSP430_ROOT      = $(TOOLS_PATH)/msp430-gcc
MSP430_BIN       = $(MSP430_ROOT)/bin
MSP430_GCC       = $(MSP430_BIN)/msp430-elf-gcc
MSP430_INCLUDE   = $(MSP430_ROOT)/include
MSP430_LD        = $(MSP430_ROOT)/include

BUILD_DIR        = build
OBJ_DIR          = $(BUILD_DIR)/obj
BIN_DIR          = $(BUILD_DIR)/bin

# /home/terence/dev/tools/ccs2020/ccs/ccs_base/DebugServer/bin
TI_CCS_DIR = $(TOOLS_PATH)/ccs2020/ccs
DEBUG_BIN_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/bin
DEBUG_DRIVERS_DIR = $(TI_CCS_DIR)/ccs_base/DebugServer/drivers

# === Compiler & Flags & Debug ===
CC        = $(MSP430_GCC)
MCU       = msp430g2553
WFLAGS    = -Wall -Wextra -Werror -Wshadow
CFLAGS    = -mmcu=$(MCU) $(WFLAGS) -Og -g $(addprefix -I, $(MSP430_INCLUDE))
LDFLAGS   = -mmcu=$(MCU) $(addprefix -L, $(MSP430_LD))
DEBUG := LD_LIBRARY_PATH=$(DEBUG_DRIVERS_DIR) $(DEBUG_BIN_DIR)/mspdebug

# === Source and Targets ===
SRCS      = src/main.c \
						src/drivers/led.c
OBJS      = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))
TARGET    = $(BIN_DIR)/output.elf

# === Linking ===
$(TARGET): $(OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

# === Compiling ===
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# === Default Target ===
all: $(TARGET)

.PHONY: all clean flash cppcheck format
# === Clean ===
clean:
	rm -rf $(BUILD_DIR)

flash: $(TARGET)
	$(DEBUG) tilib "prog $(TARGET)"


# seperate compiling from linking 
# blank.o: blank.c \\ converts c code to binary format 
# 	gcc -c main.c -o main.o
# 	gcc -c led.c -o led.o
# target: blank.o \\ links all .o files to make final program 
# 	gcc main.o led.o -o output

# Original compile command 
# /home/terence/dev/tools/msp430-gcc/bin/msp430-elf-gcc 
# -mmcu=msp430g2553 
# -I /home/terence/dev/tools/msp430-gcc/include 
# -L /home/terence/dev/tools/msp430-gcc/include 
# -Og -g -Wall 
# led.c main.c -o output

