bits 32 ; assembling for the 32 bits architecture
global start        
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    A dd 34a17bc1h, 000010a3h, 222d4e10h, 103e8a01h
    len equ ($-A)/4
    B1 resb 4
    B2 resb 4
; our code starts here
segment code use32 class=code
;Given an array A of doublewords, build two arrays of bytes:  
 ;- array B1 contains as elements the higher part of the higher words from A
 ;- array B2 contains as elements the lower part of the lower words from A
start:  
    mov esi, A
    cld
    mov ecx, len
    mov edi, B1
    mov ebx, B2
    jecxz end_loop
    repeta:
        lodsd
        ror eax, 24
        stosb
        rol eax, 24
        mov [ebx], al
        inc ebx
    loop repeta
        
    end_loop:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program