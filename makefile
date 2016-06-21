CPP = x86_64-elf-g++
AS = x86_64-elf-as
LDFLAGS = -flto
CPPFLAGS = -O3 -Wall -Wextra -ffreestanding -nostdlib -lgcc -mno-red-zone -fno-exceptions -fno-rtti

OBJDIR = build

SOURCESCPP = $(shell find ./src -name *.cpp)
SOURCESASM = $(shell find ./src -name *.s) 
OBJECTSCPP = $(SOURCESCPP:.cpp=.o)
OBJECTSASM = $(SOURCESASM:.s=.o)

all: $(OBJECTSCPP) $(OBJECTSASM)
	@$(CPP) -T ./src/linker.ld -o ./iso/boot/kernel.bin $^ $(CPPFLAGS) $(LDFLAGS)
	@strip ./iso/boot/kernel.bin
	@objcopy -O elf32-i386 ./iso/boot/kernel.bin
	@bash -c "grub-mkrescue /usr/lib/grub/i386-pc -o ./build/asuos.iso ./iso &> /dev/null"

$(OBJDIR)/%.o:%.s
	@$(AS) -o $@ -c $<

$(OBJDIR)/%.o:%.cpp
	@$(CPP) -o $@ -c $< $(CPPFLAGS)

clean:
	@rm -rf $(OBJECTSCPP) $(OBJECTSASM)
	@rm ./build/asuos.iso
	@rm ./iso/boot/kernel.bin

