# Copyright 2018 Embedded Microprocessor Benchmark Consortium (EEMBC)
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Original Author: Shay Gal-on

# Make sure the default target is to simply build and run the benchmark.
CROSS = riscv32-unknown-elf
CCPATH = $(RISCV)/bin

CC = $(CCPATH)/$(CROSS)-gcc
LD = $(CCPATH)/$(CROSS)-ld
OC = $(CCPATH)/$(CROSS)-objcopy
OD = $(CCPATH)/$(CROSS)-objdump

LIBC=../elibc

CCFLAGS = -Wall -O2 -I$(LIBC) -fomit-frame-pointer -fno-builtin -march=rv32im -mstrict-align -mabi=ilp32
LDFLAGS = -T$(PROJ).ld -Map=$(PROJ).map
LD_SOFT_FP = /opt/riscv/lib/gcc/riscv32-unknown-elf/10.2.0/rv32im/ilp32/libgcc.a -L/opt/riscv/riscv32-unknown-elf/lib/rv32im/ilp32 -lm /opt/riscv/lib/gcc/riscv32-unknown-elf/10.2.0/rv32im/ilp32/libgcc.a  /opt/riscv/riscv32-unknown-elf/lib/rv32im/ilp32/libm.a

OCFLAGS = -O binary
ODFLAGS = -d

RSTAMP = v1.0

vpath %.c
vpath %.h


HEADERS = coremark.h core_portme.h
# -DPROFILE_RUN=1
# -DPERFORMANCE_RUN=1
# -DVALIDATION_RUN=1
# TOTAL_DATA_SIZE=2000 1200 666
ITERATIONS=2000
XCFLAGS = -DITERATIONS=$(ITERATIONS) -DVALIDATION_RUN=1

PROJ = coremark


run1.log-PARAM=$(PARAM1) 7 1 2000
run2.log-PARAM=$(PARAM2) 7 1 2000 
run3.log-PARAM=$(PARAM3) 7 1 1200

FLAGS_STR = "$(CCFLAGS) $(XCFLAGS) $(XLFLAGS) $(LFLAGS_END)"
CFLAGS = $(CCFLAGS) $(XCFLAGS) -I. -DFLAGS_STR=\"$(FLAGS_STR)\" 
#Flag : LFLAGS_END
#	Define any libraries needed for linking or other flags that should come at the end of the link line (e.g. linker scripts). 
#	Note : On certain platforms, the default clock_gettime implementation is supported but requires linking of librt.
# You must also define below how to create an object file, and how to link.
vpath %.c
vpath %.s


LIB_OBJS = $(LIBC)/stdio.o $(LIBC)/stdlib.o $(LIBC)/string.o $(LIBC)/time.o $(LIBC)/uart.o
PORT_OBJS = ee_printf.o core_portme.o cvt.o
CORE_OBJS = core_list_join.o core_main.o core_matrix.o core_state.o core_util.o
OBJS = boot.o $(PORT_OBJS) $(CORE_OBJS) $(LIB_OBJS)
all:
	make $(PROJ).ebf

%$.o : %.c %(PROJ).ld
	$(CC) $(CFLAGS) -c $< -o $@

%$.o : %.s
	$(AS) $(ASFLAGS) $< $(OBJOUT) $@

_$(PROJ).o: $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) $(LD_SOFT_FP) -o $@

$(PROJ).bin: _$(PROJ).o
	$(OC) $(OCFLAGS) $< $@
	$(OD) $(ODFLAGS) $< > $(PROJ).objdump
	$(OD) -s $< > $(PROJ).content

$(PROJ).ebf: $(PROJ).bin
	./create_ebf.sh $<

.PHONY: clean
clean:
	rm -rf $(LIBC)/*.o *.o *.bin *.objdump *.map *.ebf *.content
