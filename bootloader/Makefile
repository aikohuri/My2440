#SHELL:=/bin/bash

CROSS_COMPILE=arm-none-eabi-

# compiler
CC      = $(CROSS_COMPILE)gcc
# assembler
AS      = $(CROSS_COMPILE)as
# linker
LD      = $(CROSS_COMPILE)ld
# bin util
OBJCOPY = $(CROSS_COMPILE)objcopy

BLDDIR     = build
SRCDIR     = src

CCSRCS     = $(shell find $(SRCDIR) -name "*.c")
ASSRCS     = $(shell find $(SRCDIR) -name "*.S")
OBJS       = $(patsubst $(SRCDIR)/%.c,$(BLDDIR)/%.o,$(CCSRCS)) $(patsubst $(SRCDIR)/%.S,$(BLDDIR)/%.o,$(ASSRCS))
INCS       = -I$(SRCDIR)

LDSRC      = $(SRCDIR)/2440.ld

APP        = my2440

ELF        = $(BLDDIR)/$(APP).elf
BIN        = $(BLDDIR)/$(APP).bin
MAP        = $(BLDDIR)/$(APP).map

CCFLAGS    = -Wall $(INCS)
LDFLAGS    = -Map=$(MAP) --cref

DOWNLDRDIR = $(HOME)/workspace/arm/usb-downloader/usbpush
LDADDR     = 0x00000000

BINSIZE  = $(shell stat -c%s $(BIN))

all: $(BIN)

$(BIN): $(ELF)
	@echo
	@echo "========== Generating $@ =========="
	@$(OBJCOPY) -O binary $< $@
	@echo

$(ELF): $(OBJS)
	@echo
	@echo "========== Linking $@ =========="
	@$(LD) $(LDFLAGS) -T $(LDSRC) -o $@ $(OBJS)

$(OBJS): | $(BLDDIR)

$(BLDDIR):
	@mkdir -p $@

$(BLDDIR)/%.o: $(SRCDIR)/%.S
	@echo
	@echo "========== Compiling $< =========="
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	@echo
	@echo "========== Compiling $< =========="
	@$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	@echo
	@echo "========== Cleaning =========="
	@rm -r $(BLDDIR)

upload:
	@echo
	@echo "========== Uploading =========="
	@echo "1. Boot mini2440"
	@echo "2. choose \"[q] Goto shell of vivi\" option"
	@echo "3. Type \"load flash 0 $(BINSIZE) u\""
	@echo
	@read -p "Press any key if it's ready ..."
	@echo
	@sudo $(DOWNLDRDIR) $(BIN) $(LDADDR)

