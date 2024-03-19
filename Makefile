VIRT_DTB_FILE = riscv64-virt.dtb
VIRT_DTS_FILE = riscv64-virt.dts

debug: all
	gdb-multiarch kernel.elf --tui -ex 'target remote :1234'
run: all
	qemu-system-riscv64 -machine virt -m 128M -bios none -kernel kernel.elf -gdb tcp::1234 -S

all: kernel.elf

gen-virt-dts: gen-virt-dtb 
	dtc -I dtb -O dts ${VIRT_DTB_FILE} -o ${VIRT_DTS_FILE}
	rm ${VIRT_DTB_FILE}

gen-virt-dtb:
	qemu-system-riscv64 -machine virt -machine dumpdtb=${VIRT_DTB_FILE}

objdump-kernel.elf: kernel.elf
	riscv64-unknown-elf-objdump -d kernel.elf

kernel.elf: boot.o kernel.o 
	riscv64-unknown-elf-ld -T linker.ld --gc-sections -nostdlib -nostartfiles -nodefaultlibs boot.o kernel.o -o kernel.elf

boot.o: boot.s 
	riscv64-unknown-elf-as -o boot.o boot.s

kernel.o: kernel.c
	riscv64-unknown-elf-gcc -o kernel.o -c kernel.c -g -ffreestanding -Wall -Wextra 

