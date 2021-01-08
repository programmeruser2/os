global load_idt
load_idt:
	mov eax, [esp + 4] ; get pointer to idt
	lidt [eax]
	ret
