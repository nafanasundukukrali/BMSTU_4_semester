.intel_syntax noprefix
.global my_strncpy
.text

get_copy_len:
.cfi_startproc
        mov edi, edx
        call strlen
        push eax
        mov edi, esi
        call strlen
        pop edi
        xchg ecx, eax
        call cmp_eax_ecx_sp # СЕЙЧАС: EAX: len ESI, EDI: len EDX
        ret
.cfi_endproc

cmp_eax_ecx_sp:
.cfi_startproc
        cmp ecx, eax
        cmovb eax, ecx
        cmp edi, eax
        cmovb eax, edi
        push ecx
        mov ecx, eax
        pop eax
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
        mov esi, [ebp + 8] # Копирование параметров. Здесь указатель на dsc
        mov edx, [ebp + 12] # src
        mov ecx, [ebp + 16] # len

        cmp edx, esi # Проверка того, что строки не перекрываются
        jae sub_addr
        xchg edx, esi
        mov eax, edx
        sub eax, esi
        xchg edx, esi
        sub_addr:
                mov eax, edx
                sub eax, esi


        cmp eax, ecx
        jae not_reverse_copy

reverse_copy:
        call get_copy_len
        add edx, edi
        add esi, edi
        sub edx, 1
        sub esi, 1
        std
        jmp copy


not_reverse_copy:
        call get_copy_len
copy:
        mov edi, edx
        xchg edi, esi
        rep movsb
        cld
exit:
        pop ebp

        ret
