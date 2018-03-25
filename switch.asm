[bits 16]

%include "gdt.asm"

switchToProtected:
	cli
	lgdt [gdtDescriptor]
	mov eax, cr0
	or eax, 0x1
	mov cr0, eax

	jmp CODESEG:initProtected

[bits 32]

initProtected:
	mov ax, DATASEG
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	call beginProtectedMode

[bits 16]
