.global fpuinitialize

// FPU control word
// Defines FPU exception masks and different controls
// See https://goo.gl/lY9i6b for details
.global fpu_cword
fpu_cword:
.word 0b0000001101111111

fpuinitialize:
fninit
fldcw fpu_cword // @TODO : Make the control word loaded from C++ code
ret