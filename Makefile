OS_IMAGE = kernel.elf
SRC_DIR = src 

CC = riscv64-unknown-elf-gcc
CFLAGS = -g -O0 -mcmodel=medany -ffreestanding -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith -Wcast-align\
		 -Wconversion -Wunreachable-code -Wswitch-enum -Wswitch-default -Wcast-qual -Wwrite-strings\
		 -Wstrict-overflow=5  -nostdlib -nodefaultlibs -nostartfiles -I./src -I./src/cstdlib
AS = riscv64-unknown-elf-as 
AS_FLAGS= -g
LD = riscv64-unknown-elf-ld 
LD_FLAGS = --gc-sections -nostdlib
LD_SCRIPT = linker.ld
OBJDUMP = riscv64-unknown-elf-objdump
GDB = gdb-multiarch
GDB_FLAGS = -tui -ex 'target remote :1234' -ex 'dir $(SRC_DIR)'

QEMU = qemu-system-riscv64
QEMU_MACH = virt
QEMU_DRIVE_FILE = virt-drive.raw
QEMU_RUN_FLAGS = -machine $(QEMU_MACH) -m 128M -bios none\
				 -drive if=none,format=raw,file=$(QEMU_DRIVE_FILE),id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0

QEMU_DEBUG_RUN_FLAGS = -gdb tcp::1234 -S -machine $(QEMU_MACH) -m 128M -bios none\
					   -drive if=none,format=raw,file=$(QEMU_DRIVE_FILE),id=x0 -device virtio-blk-device,drive=x0,bus=virtio-mmio-bus.0 

VIRT_DTB_FILE = riscv64-virt.dtb
VIRT_DTS_FILE = riscv64-virt.dts

HEADERS = $(wildcard src/*.h src/cstdlib/*.h)
C_SRCS = $(wildcard src/*.c src/cstdlib/*.c)
C_OBJS = $(C_SRCS:.c=.o)

ASM_SRCS = $(wildcard src/*.s src/cstdlib/*.s)
ASM_OBJS = $(ASM_SRCS:.s=.o)

.PHONY: clean all run 

run: all
	$(QEMU) -kernel $(OS_IMAGE) $(QEMU_RUN_FLAGS)

debug-run: all 
	$(QEMU) -kernel $(OS_IMAGE) $(QEMU_DEBUG_RUN_FLAGS)

debug: all
	$(GDB) $(OS_IMAGE) $(GDB_FLAGS)

all: $(OS_IMAGE) $(QEMU_DRIVE_FILE)

clean:
	rm -rf src/*.o *.dtb *.elf



$(OS_IMAGE): $(C_OBJS) $(ASM_OBJS)
	$(LD) $(LD_FLAGS) -T $(LD_SCRIPT) $^ -o $(OS_IMAGE) 

$(QEMU_DRIVE_FILE):
	touch $(QEMU_DRIVE_FILE)

#src/boot.o: src/boot.s 
#	$(AS) -o src/boot.o -c src/boot.s

#kernel.o: src/kernel.c
#	$(CC) -o kernel.o -c src/kernel.c $(CFLAGS)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.s
	$(AS) $(AS_FLAGS) -c $< -o $@

gen-dtb:
	$(QEMU) -machine $(QEMU_MACH) -machine dumpdtb=$(VIRT_DTB_FILE)

gen-dts: gen-dtb 
	dtc -I dtb -O dts $(VIRT_DTB_FILE) -o $(VIRT_DTS_FILE)

objdump-os-image: $(OS_IMAGE)
	$(OBJDUMP) -d $(OS_IMAGE)
