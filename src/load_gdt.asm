global load_gdt
load_gdt:
	mov eax, [esp + 4] ; get the pointer (the struct's size is 4)
	lgdt [eax] ; load the pointer

	; new data segment offset
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax

	; jump to flush the code segment register
	jmp 0x08:.flush
.flush:
	ret
