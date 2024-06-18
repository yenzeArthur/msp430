
MAP= $(BUILDS)/blink.map
FILE=blink.c
BUILDS=build

GCC_DIR = C:/ti/msp430-gcc/bin
SUPPORTING_SCRIPTS = C:/ti/msp430-gcc/include

CC = $(GCC_DIR)/msp430-elf-gcc
GDB = $(GCC_DIR)/msp430-elf-gdb
DEVICE = msp430g2553

C_FLAGS = -g -Wall -mmcu=$(DEVICE) $(addprefix -I,$(SUPPORTING_SCRIPTS))
L_FLAGS = -mmcu=$(DEVICE) -Wl,-Map,$(MAP),--gc-sections $(addprefix -L,$(SUPPORTING_SCRIPTS))

all: compile link debug

compile: $(FILE)
	$(CC) -c $(C_FLAGS) -o $(BUILDS)/blink.o $(FILE)

link: $(BUILDS)/blink.o
	$(CC) $(L_FLAGS) -o $(BUILDS)/blink.elf $(BUILDS)/blink.o

debug:
	$(GDB) $(BUILDS)/blink.elf

clean:
	del /Q $(BUILDS)\blink*.o
	del /Q $(BUILDS)\blink*.map
	del /Q $(BUILDS)\blink*.elf