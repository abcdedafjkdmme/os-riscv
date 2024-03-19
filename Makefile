OS_IMAGE = kernel.elf
SRC_DIR = src 

CC = riscv64-unknown-elf-gcc
CFLAGS = -g -ffreestanding -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align\
		 -Wconversion -Wunreachable-code -Wswitch-enum -Wswitch-default -Wcast-qual -Wwrite-strings\
		 -Wstrict-overflow=5  -nostdlib -nodefaultlibs -nostartfiles
AS = riscv64-unknown-elf-as 
AS_FLAGS=
LD = riscv64-unknown-elf-ld 
LD_FLAGS = --gc-sections 
LD_SCRIPT = linker.ld
OBJDUMP = riscv64-unknown-elf-objdump
GDB = gdb-multiarch
GDB_FLAGS = -tui -ex 'target remote :1234' -ex 'dir $(SRC_DIR)'
QEMU = qemu-system-riscv64
QEMU_MACH = virt
QEMU_RUN_FLAGS = -machine $(QEMU_MACH) -m 128M -bios none -gdb tcp::1234 -S
VIRT_DTB_FILE = riscv64-virt.dtb
VIRT_DTS_FILE = riscv64-virt.dts


C_SRCS = src/kernel.c
C_OBJS = $(C_SRCS:%.c=%.o)

ASM_SRCS = src/boot.s 
ASM_OBJS = $(ASM_SRCS:%.c=%.o)

debug: all
	$(GDB) $(OS_IMAGE) $(GDB_FLAGS)
run: all
	$(QEMU) -kernel $(OS_IMAGE) $(QEMU_RUN_FLAGS)

all: $(OS_IMAGE)

clean:
	rm -rf *.o *.dtb *.elf

gen-virt-dtb:
	$(QEMU) -machine $(QEMU_MACH) -machine dumpdtb=${VIRT_DTB_FILE}

$(OS_IMAGE): boot.o kernel.o 
	$(LD) -T $(LD_SCRIPT) boot.o kernel.o -o $(OS_IMAGE) $(LD_FLAGS)

boot.o: src/boot.s 
	$(AS) -o boot.o -c src/boot.s

kernel.o: src/kernel.c
	$(CC) -o kernel.o -c src/kernel.c $(CFLAGS)

gen-virt-dts: gen-virt-dtb 
	dtc -I dtb -O dts $(VIRT_DTB_FILE) -o $(VIRT_DTS_FILE)

objdump-os-image: $(OS_IMAGE)
	$(OBJDUMP) -d $(OS_IMAGE)
