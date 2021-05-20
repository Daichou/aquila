# ======================================================================
#  This Makefile builds a test application *.ebf file for Aquila.
#
#  Chun-Jen Tsai, Jan/12/2020
# ======================================================================

CROSS = riscv32-unknown-elf
CCPATH = $(RISCV)/bin

CC = $(CCPATH)/$(CROSS)-gcc
LD = $(CCPATH)/$(CROSS)-ld
OC = $(CCPATH)/$(CROSS)-objcopy
OD = $(CCPATH)/$(CROSS)-objdump

LIBC = ../elibc
LD_LIBRARY_PATH = /opt/riscv/lib/gcc/riscv32-unknown-elf/10.2.0/include
CCFLAGS = -Wall -O2 -I$(LIBC)  -fomit-frame-pointer -fno-builtin -march=rv32im -mstrict-align -mabi=ilp32
LDFLAGS = -T$(PROJ).ld -Map=$(PROJ).map
LD_SOFT_FP = /opt/riscv/lib/gcc/riscv32-unknown-elf/10.2.0/rv32im/ilp32/libgcc.a -L/opt/riscv/riscv32-unknown-elf/lib/rv32im/ilp32 -lm /opt/riscv/lib/gcc/riscv32-unknown-elf/10.2.0/rv32im/ilp32/libgcc.a  /opt/riscv/riscv32-unknown-elf/lib/rv32im/ilp32/libm.a

OCFLAGS = -O binary
ODFLAGS = -d

PROJ = mm
OBJS = boot.o mm.o mm_main.o $(LIBC)/stdio.o $(LIBC)/stdlib.o $(LIBC)/string.o $(LIBC)/time.o $(LIBC)/uart.o $(LIBC)/util.o

all:
	make $(PROJ).ebf

clean:
	rm -rf *.s $(LIBC)/*.o *.o *.bin *.objdump *.map *.ebf *.content

%.o: %.c $(PROJ).ld
	$(CC) $(CCFLAGS) -c $< -o $@

_$(PROJ).o: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LD_SOFT_FP) -o $@

$(PROJ).bin: _$(PROJ).o
	$(OC) $(OCFLAGS) $< $@
	$(OD) $(ODFLAGS) $< > $(PROJ).objdump
	$(OD) -s $< > $(PROJ).content
	
$(PROJ).ebf: $(PROJ).bin
	./create_ebf.sh $<

