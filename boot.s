	BITS 16

	jmp short boot
	nop

OEMLabel		db "LKRosE"
BytesPerSector		dw 512
SectorsPerCluster	db 1
ReservedForBoot		dw 1
NumberOfFats		db 2
RootDirEntries		dw 224
LogicalSectors		dw 2880
MediumByte		db 0F0h
SectorsPerFat		dw 9
SectorsPerTrack		dw 18
Sides			dw 2
HiddenSectors		dd 0
LargeSectors		dd 0
DriveNo			dw 0
Signature		db 41
VolumeID		dd 00000000h
VolumeLabel		dd "LKRosE"
FileSystem		db "FAT12"

start:
	mov ax, 07c0h
	add ax, 544
	cli
	mov ss, ax
	mov sp, 4096
	sti
	mov ax, 0x7c0h
	mov ds, ax
	mov byte [bootdev], d1
	
