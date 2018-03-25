find_bios_string:

	mov bx, 0
	mov es, bx

	_search_loop:
		
		mov al, [es:bx]
		cmp al, 'B'		
		jne _continue_search

		mov al, [es:bx+1]
		cmp al, 'I'		
		jne _continue_search

		mov al, [es:bx+2]
		cmp al, 'O'		
		jne _continue_search

		mov al, [es:bx+3]
		cmp al, 'S'		
		jne _continue_search		

		mov dx, es
		call printHex

		mov dx, bx
		call printHex

		ret

	_continue_search:		

		inc bx
		cmp bx, 0
		je incSeg
		jmp _search_loop
		
	incSeg:
		mov cx, es
		add cx, 0x1000
		mov es, cx
		jmp _search_loop

