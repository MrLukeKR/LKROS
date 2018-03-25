gdtStart:

gdtNull:
	dd 0x0
	dd 0x0

gdtCode:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10011010b
	db 11001111b
	db 0x0

gdtData:
	dw 0xffff
	dw 0x0
	db 0x0
	db 10010010b
	db 11001111b
	db 0x0

gdtEnd:
	
gdtDescriptor:
	dw gdtEnd - gdtStart - 1
	dd gdtStart

CODESEG equ gdtCode - gdtStart
DATASEG equ  gdtData - gdtStart
