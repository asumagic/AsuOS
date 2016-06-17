#!/bin/bash

# Kernel code
ARGSCPP="-O3 -Wall -Wextra -ffreestanding -nostdlib -lgcc -mno-red-zone -fno-exceptions -fno-rtti"

echo "-- Compiling C++ code"
objects=(kernel vga     logger     portio    cpuid     interrupts)
sources=(kernel vga/vga vga/logger io/portio cpu/cpuid cpu/interrupts)
arraylength=${#objects[@]}
for ((i=0; i<${arraylength}; i++));
do
	echo "- Building ${sources[$i]}..."
	bash -c "x86_64-elf-g++ -o ${objects[$i]}.o $ARGSCPP -c ../src/${sources[$i]}.cpp"
done

# Full assembly code
echo "-- Compiling x86 assembly code"
objectsasm=(boot)
sourcesasm=(boot)
arraylength=${#objectsasm[@]}
for ((i=0; i<${arraylength}; i++));
do
	echo "- Building ${sourcesasm[$i]}..."
	x86_64-elf-as -o ${objectsasm[$i]}.o ../src/${sourcesasm[$i]}.s
done

# Build the kernel image
objectsstr=$(printf "%s.o " "${objects[@]}")
objectsasmstr=$(printf "%s.o " "${objectsasm[@]}")

echo "-- Building kernel.bin..."
bash -c "x86_64-elf-gcc -T ../src/linker.ld -o ../iso/boot/kernel.bin $ARGSCPP -flto $objectsstr $objectsasmstr"

# Strip symbols from the kernel
echo "-- Stripping symbols from kernel.bin..."
strip ../iso/boot/kernel.bin

# Show the ELF64 as ELF32 to have GRUB recongizing it (the boot.s code initializes the long mode)
objcopy -O elf32-i386 ../iso/boot/kernel.bin

# Generate the iso file
echo "-- Building GRUB iso image..."
grub-mkrescue /usr/lib/grub/i386-pc/ -o asuos.iso ../iso &> /dev/null
