
# Aquila software development

You can use the standard [RISC-V GCC toolchain] (https://github.com/riscv/riscv-gcc) to develop software for an Aquila SoC. We are using gcc 8.2.0 with RV32IMA configuration. Simply put, you can go into each application software directory and type 'make' to generate an application binary *.ebf.

Please refer to the Aquila's manual for details of running an application on an Aquila SoC.

# gnu toolchain issue

wint_t type not defined:

add:
```
#define __need_size_t     
#define __need_wint_t     
#define wint_t unsigned int
```
to /opt/riscv/riscv32-unknown-elf/include/sys/_types.h line 22.
