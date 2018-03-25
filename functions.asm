print_string:
	mov ah, 0x0e
	_loop:
		lodsb
		cmp al,0
		je _end
		
		int 0x10
		jmp _loop
	_end:
	
	ret

print_char:
	mov ah, 0x0e
	int 0x10
	ret

printHex:
	push bx
	push si
	mov si, HEXTEMPLATE
	
	mov bx, dx
	shr bx,12
	mov bx, [bx+HEXABET]
	mov [HEXTEMPLATE+2],bl

	mov bx, dx
	shr bx,8
	and bx, 0x000f
	mov bx, [bx+HEXABET]
	mov [HEXTEMPLATE+3],bl

	mov bx, dx
	shr bx,4
	and bx, 0x000f
	mov bx, [bx+HEXABET]
	mov [HEXTEMPLATE+4],bl
	
	mov bx, dx
	and bx, 0x000f
	mov bx, [bx+HEXABET]
	mov [HEXTEMPLATE+5],bl

	call print_string

	pop si
	pop bx
	ret

printNewline:
	push bx
	mov al, 0x0a
	call print_char
	mov al, 0x0d
	call print_char
	pop bx
	ret

readFromDisk:
	pusha
	mov ah, 0x02	; Read sectors from drive
	
	;mov al, 1	; Only read 1 sector
	mov ch, 0	; Cylinder number (BootSec is on C0) to select
	mov dh, 0	; Select first r/w head
	mov cl, 2	; Select second sector

	push bx
	mov bx, 0
	mov es, bx
	pop bx
	;mov bx, 0x7c00 + 512
	
	int 0x13

	jc readError
	
	popa
	ret

readError:
	mov si, DISKERROR
	call print_string
	jmp $
