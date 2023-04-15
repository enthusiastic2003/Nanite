global pmmngr_paging_enable
pmmngr_paging_enable:
mov	eax, cr0
cmp edi, 1
je	enable
jmp disable
enable:
or eax, 0x80000000		
mov	cr0, eax
jmp done
disable:
and eax, 0x7FFFFFFF		
mov	cr0, eax
done:
ret



global pmmngr_is_paging
pmmngr_is_paging:
push ebx
mov ebx,0
mov	eax, cr0
mov	ebx, eax
and ebx, 0x80000000
mov eax, ebx
pop ebx
ret

global pmmngr_load_PDBR
pmmngr_load_PDBR:
mov	eax, edi
mov	cr3, eax		


global pmmngr_get_PDBR
pmmngr_get_PDBR:
mov	eax, cr3
ret
