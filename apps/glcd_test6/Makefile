# File:   Makefile
# Author: M. P. Hayes, UCECE
# Date:   5 August 2009
# Descr:  Makefile for glcd_test6

MCU = AT91SAM7S256

## Create ROM-Image (final)
#RUN_MODE = ROM_RUN
## Create RAM-Image (debugging) 
RUN_MODE = RAM_RUN

# Select optimisation level
OPT = -O2

TARGET = glcd_test6.out

SRC = syscalls.c glcd_test6.c glcd.c pit.c spi.c crt0.c piezo.c piezo_beep.c font.c glcd_text.c textview.c 

MAT91LIB = ../../mat91lib
MMCULIB = ../../mmculib


# Nothing to modify below here.

CC = arm-elf-gcc
OBJCOPY = arm-elf-objcopy
SIZE = arm-elf-size
DEL = rm

VPATH = $(MMCULIB) $(MAT91LIB)

OBJ = $(sort $(SRC:.c=.o))
DEPS = $(sort $(SRC:.c=.d))

#CFLAGS = -mcpu=arm7tdmi -Wall -Wstrict-prototypes -W -gdwarf-2 -std=c99 -D$(RUN_MODE) -I$(MAT91LIB) -I$(MMCULIB) -I. $(OPT) -D$(MCU)
CFLAGS = -mcpu=arm7tdmi -Wall -Wstrict-prototypes -W -gdwarf-2 -D$(RUN_MODE) -I$(MAT91LIB) -I$(MMCULIB) -I. $(OPT) -D$(MCU)

LDFLAGS = -mthumb-interwork -nostartfiles -lm -lc

ifeq ($(RUN_MODE),RAM_RUN)
LDFLAGS +=-T$(MAT91LIB)/ldscripts/$(MCU)-RAM.ld
else 
LDFLAGS +=-T$(MAT91LIB)/ldscripts/$(MCU)-ROM.ld
endif


# Default target.
all: $(TARGET)

# Automatically generate C source code dependencies.
%.d: %.c
	set -e; $(CC) -MM $(CFLAGS) $< \
	| sed 's,\(.*\)\.o[ :]*,\1.o \1.d : ,g' > $@; \
	[ -s $@ ] || rm -f $@

# Include the dependency files.
-include $(DEPS)

# Compile C source files to object files.
%.o: %.c config.h target.h
	$(CC) -c $(CFLAGS) $< -o $@


# This cannot be compiled in thumb mode.  It must be compiled with optimisation
#
crt0.o: crt0.c config.h target.h
	$(CC) -c $(CFLAGS) -O2 $< -o $@


# Link object files to form output file.
$(TARGET): $(OBJ)
	$(CC) $^ $(LDFLAGS) -o $@ -lm -Wl,-Map=$*.map,--cref
	$(SIZE) $@


# Remove non-source files.
.PHONY: clean
clean: 
	-$(DEL) *.o *.out *.hex *.bin *.elf *.map *.d

