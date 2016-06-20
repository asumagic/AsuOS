#!/bin/bash

# Kernel code
ARGSCPP="-O3 -Wall -Wextra -ffreestanding -nostdlib -lgcc -mno-red-zone -fno-exceptions -fno-rtti"

echo "-- Compiling C++ code"
objects=(kernel module        vga     logger     portio    cpuid     interrupts     kernelcommon)
sources=(kernel module/module vga/vga vga/logger io/portio cpu/cpuid cpu/interrupts common/kernel)
arraylength=${#objects[@]}
for ((i=0; i<${arraylength}; i++));
do
	bash -c "x86_64-elf-g++ -o ${objects[$i]}.o $ARGSCPP -c ../src/${sources[$i]}.cpp"&
done

# Full assembly code
echo "-- Compiling plain assembly"
objectsasm=(boot interruptsasm)
sourcesasm=(boot cpu/interrupts)
arraylength=${#objectsasm[@]}
for ((i=0; i<${arraylength}; i++));
do
	x86_64-elf-as -o ${objectsasm[$i]}.o ../src/${sourcesasm[$i]}.s&
done

# Wait for compiling jobs to end before compiling the kernel
for job in `jobs -p`
do
	wait $job
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
