.intel_syntax noprefix
.global my_strncpy
.text

get_copy_len:
.cfi_startproc
        push edi
        mov edi, esi
        call strlen
        cmp eax, ecx
        cmovb ecx, eax # cf = 1, если ниже
        pop edi
        ret
.cfi_endproc

strlen:
.cfi_startproc
        push ecx
        mov ecx, -1
        xor al, al
        repne scasb
        not ecx
        dec ecx
        mov eax, ecx
        pop ecx
        ret
.cfi_endproc

my_strncpy:
        push ebp # Создание кадра стека
        mov ebp, esp
        mov edi, [ebp + 8] # Копирование параметров. Здесь указатель на dsc
        mov esi, [ebp + 12] # src
        mov ecx, [ebp + 16] # len

        cmp edi, esi
        jae sub_addr # cf = 0, если больше или равно
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
