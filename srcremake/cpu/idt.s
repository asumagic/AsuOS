.extern idtptr

.global loadIDT
lidt idtptr # Load the IDT from the idtptr structure
ret
