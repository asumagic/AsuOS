.macro pushaq
pushq %rax
pushq %rcx
pushq %rdx
pushq %rbx
pushq %rbp
pushq %rsi
pushq %rdi
.endm

.macro popaq
popq %rax
popq %rcx
popq %rdx
popq %rbx
popq %rbp
popq %rsi
popq %rdi
.endm

.global isrcommonhandler
.align 4
isrcommonhandler:
pushaq # Push x86-64 GP registers to the stack
cld # Clear the direction flag
#call # Call the C++ ISR handler
popaq # Pop back GP registers from the stack
iretq # Long mode interrupt return
