
## **GCC command**
/home/terence/dev/tools/msp430-gcc/bin/msp430-elf-gcc 
-mmcu=msp430g2553 
-I /home/terence/dev/tools/msp430-gcc/include 
-L /home/terence/dev/tools/msp430-gcc/include 
-Og -g -Wall 
led.c main.c -o output

## Make Command 
sudo make all TOOLS_PATH=/home/terence/dev/tools
sudo make flash TOOLS_PATH=/home/terence/dev/tools

## Print to Terminal
picocom /dev/ttyUSB0 -b 9600
