[bits 32]

VIDEOMEMORY equ 0xb8000
WHITEONBLACK equ 0x0f

printStringProtected:
	pusha
	mov edx, VIDEOMEMORY

printStringProtectedLoop:
	mov al, [esi]
	mov ah, WHITEONBLACK

	cmp al, 0
	je printStringProtectedComplete

	mov [edx], ax

	add esi, 1
	add edx, 2

	jmp printStringProtectedLoop

printStringProtectedComplete:
	popa
	ret

[bits 16]
