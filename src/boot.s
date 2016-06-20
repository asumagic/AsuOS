# Mostly dschatzberg's code from #osdev
# @TODO : Recode parts and move up as much as possible to C++ code? e.g. SSE and FPU initialization
# @TODO : Add console feedback when required features are not detected.

.text
.code32 # 32-bits code

# Multiboot header data
.set ALIGN,     1<<0             # Align loaded modules on page boundaries
.set MEMINFO,   1<<1             # Provide the memory map
.set FLAGS,     ALIGN | MEMINFO  # Multiboot flag field (provide MEMINFO & ALIGN)
.set MAGIC,     0x1BADB002       # Magic multiboot header number
.set CHECKSUM,  -(MAGIC + FLAGS) # Checksum of the multiboot header

# Multiboot header declaration
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

.data
.align 4096
pml4:
	.quad pdpt + 0x3
	.rept 511
	.quad 0
	.endr
pdpt:
	.quad pd + 0x3
	.rept 511
	.quad 0
	.endr
pd:
	index = 0
	.rept 512
	.quad (index << 21) | 0x83
	index = index + 1
	.endr

GDTPointer:
	.short GDTEnd - GDT - 1
	.long GDT

.align 8
GDT:
# NULL descriptor
.word 0 # Limit (low) - unused on x86-64
.word 0 # Base (low) - unused on x86-64
.byte 0 # Base (middle) - unused on x86-64
.byte 0 # Access
.byte 0 # Granularity
.byte 0 # Base (high)

# Code segment descriptor
.word 0
.word 0
.byte 0
.byte 0x98 # Present, Not system, Execute only
.byte 0x20 # 64-bit descriptor
.byte 0

# Data segment descriptor
.word 0
.word 0
.byte 0
.byte 0x90 # Present, Not system
.byte 0
.byte 0
GDTEnd = .

.globl _fpu_control_word
_fpu_control_word:
.word 0x37f //enable both division by zero and invalid operand exceptions

.bss
.align 16
. = . + 16 * 1024
stackTop = .

.text
.align 4        
.globl start32
start32:
	cli # Disable interruptions

	mov %ebx, %edi # Loads GRUB arguments

	# Initialize the stack
	lea stackTop, %esp
	mov $0, %ebp

	# Check for CPUID support, because some CPUs does not support this feature
	# Verify if ID bits can be flipped in flags.
	# Loads the value in %eax and %ecx, to flip the ID bit in %eax, save it and reload it to compare it with the %ecx version.
	pushf # Push EFLAGS register to the stack
	pop %eax
	mov %eax, %ecx
	xor $(1<<21), %eax # Flip the ID bit in %eax
	push %eax
	popf # Pop back the EFLAGS value with the ID bit flipped
	pushf
	xor %eax, %ecx # If eax == ecx then the bit was not flipped
	jz start32.no_cpuid

	
	# Check for CPUID extended features
	mov $0x80000000, %eax # Extended CPUID feature
	cpuid
	cmp $0x80000001, %eax # Check if there are extended CPUID features
	jb start32.no_ext_features


	# Check for long mode availability
	mov $0x80000001, %eax
	cpuid
	test $(1 << 29), %edx # Check if the long mode bit is on
	jz start32.no_long_mode    

	# Enable PAE and SSE 
	mov $0x628, %eax
	mov %eax, %cr4
	//point to the pml4
        lea pml4, %eax
        mov %eax, %cr3
        //paging is setup, but not enabled
        //set long mode
        mov $0xC0000080, %ecx //EFER MSR
	mov $0x900, %eax //NXE + LME
        mov $0, %edx
        wrmsr
        
	mov $0x80010023, %eax //set page bit and FPU
	mov %eax, %cr0

        fninit // initial fpu state
        fldcw _fpu_control_word

	lgdt GDTPointer
	ljmp $8, $start64

start32.no_cpuid:
        jmp start32.no_cpuid

start32.no_ext_features:
        jmp start32.no_ext_features

start32.no_long_mode:
        jmp start32.no_long_mode

.code64
.align 4
start64:
	.cfi_startproc simple
	.cfi_def_cfa %rsp, 0
	.cfi_undefined %rip
	mov $0x0, %ax
	mov %ax, %es
	mov %ax, %ss
	mov %ax, %ds
	mov %ax, %fs
	mov %ax, %gs
	lea stackTop, %rsp # 64-bit stack pointer
	call kmain
	cli
	hlt
	.cfi_endproc
