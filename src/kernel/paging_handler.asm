global pmmngr_paging_enable
pmmngr_paging_enable:
push ebp
mov ebp,esp
mov	eax, cr0
push edi
mov edi, [ebp+8]
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
pop edi
pop ebp
ret


global pmmngr_is_paging
pmmngr_is_paging:
push ebp
push ebx
mov ebx,0
mov	eax, cr0
mov	ebx, eax
and ebx, 0x80000000
mov eax, ebx
pop ebx
pop ebp
ret


global pmmngr_load_PDBR  
pmmngr_load_PDBR:
push ebp
mov ebp, esp
push edi
mov edi, [esp+8]
mov	eax, edi
mov	cr3, eax	
pop edi
pop ebp
ret	


global pmmngr_get_PDBR 
pmmngr_get_PDBR:
push ebp
mov	eax, cr3
pop ebp
ret


global test1
test1:
push ebp
mov  ebp, esp
mov eax, [ebp+8]
pop ebp
ret