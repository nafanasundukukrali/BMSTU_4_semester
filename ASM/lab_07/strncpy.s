.intel_syntax noprefix
.global my_strncpy
.text

get_copy_len:
        push edi
        mov edi, esi
        call strlen
        cmp eax, ecx
        cmovb ecx, eax
        pop edi
        ret

strlen:
        push ecx
        mov ecx, -1
        xor al, al
        repne scasb
        not ecx
        dec ecx
        mov eax, ecx
        pop ecx
        ret

my_strncpy:
        push ebp
        mov ebp, esp
        mov ecx, [ebp + 8]
        mov edi, [ebp + 12]
        mov esi, [ebp + 16]

        cmp edi, esi
        jae sub_addr
        xchg edi, esi
        mov eax, edi
        sub eax, esi
        xchg edi, esi
        jmp cont
        sub_addr:
                mov eax, edi
                sub eax, esi
        cont:

        cmp eax, ecx
        jae not_reverse_copy

reverse_copy:
        call get_copy_len
        add edi, ecx
        add esi, eax
        movb [edi], 0x0
        sub edi, 1
        sub esi, 1
        std
        jmp copy

not_reverse_copy:
        call get_copy_len
        add edi, ecx
        movb [edi], 0x0
        sub edi, ecx
copy:
        rep movsb
        cld
exit:
        pop ebp

        ret
