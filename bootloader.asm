[org 0x7c00]

mov bp, 0xffff		; Stack begins (Stack Base) at 0x8000, decreasing Stack
mov sp, bp		; Point to the bottom of the stack

mov si, MSGRL
call print_string

call printNewline

mov si, MSGLD
call print_string

call printNewline

mov al, 9
mov bx, loadKernel
call readFromDisk

mov si, MSGSW
call print_string

call printNewline

call switchToProtected

jmp $			; Endless Hang - stops execution of further bytes

%include "functions.asm"
%include "data.asm"
%include "switch.asm"
%include "protectedfunctions.asm"

[bits 32]

beginProtectedMode:

mov esi, MSGPR
call printStringProtected

jmp loadKernel

[bits 16]

MSGRL db "Started in 16 bit mode",0
MSGSW db "Switching to 32 bit protected mode",0
MSGLD db "Loading Kernel from disk to address 0x7e00",0
MSGPR db "Switched to 32 bit protected mode",0

times 510-($-$$) db 0	; Sets 0 - 510 with zeroes - must be exactly 512 bytes long (sector)
dw 0xaa55		; The "Magic Number" - tells the BIOS to boot

loadKernel:

