bits 32
global start
extern exit, fopen, fclose, printf, fread
import exit msvcrt.dll
import fopen msvcrt.dll
import fclose msvcrt.dll
import printf msvcrt.dll
import fread msvcrt.dll
segment data use32 class = data
    file_name db "numbers26.txt", 0
    access_mode db "r", 0
    file_descriptor dd -1
    len equ 100
    nr times len db 0
    P db 0
    N db 0
segment code use32 class = code
;Read from file numbers.txt a string of numbers (odd and even). Build two strings using readen numbers:
;P – only with even numbers
;N – only with odd numbers
;Display the strings on the screen.
start:
    push dword access_mode
    push dword file_name
    call [fopen]
    add esp, 4*2
    mov [file_descriptor], eax
    cmp eax, 0
    je final
    
    push dword [file_descriptor]
    push dword len
    push dword 1
    push dword nr
    call [fread]
    add esp, 4*4
    
    
    push dword [file_descriptor]
    call [fclose]
    add esp, 4
    
    
    
    final:
    push dword 0
    call [exit]