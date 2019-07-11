TITLE_ID = NIDUMP001
TARGET = mDump
PSVITAIP = 192.168.1.115

PLUGIN_OBJS = mmu_dump.o
HEADERS = $(wildcard *.h)

PLUGIN_LIBS = -ltaihen_stub -lSceSysclibForDriver_stub -lSceModulemgrForKernel_stub -lSceIofilemgrForDriver_stub

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O3
ASFLAGS = $(CFLAGS)

all: kDump.skprx

kDump.skprx: kDump.velf
	vita-make-fself -c $< $@

kDump.velf: kDump.elf
	vita-elf-create -e exports.yml $< $@

kDump.elf: $(PLUGIN_OBJS)
	$(CC) $(CFLAGS) $^ $(PLUGIN_LIBS) -o $@ -nostdlib

clean:
	@rm -rf *.velf *.elf *.vpk *.skprx $(MAIN_OBJS) $(PLUGIN_OBJS) param.sfo eboot.bin

send: eboot.bin
	curl -T eboot.bin ftp://$(PSVITAIP):1337/ux0:/app/$(TITLE_ID)/
	@echo "Sent."
