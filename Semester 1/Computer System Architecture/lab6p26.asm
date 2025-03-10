bits 32 ; assembling for the 32 bits architecture
global start        
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s dd 12345678h, 1A2B3C4Dh, 1E98DC76h    
    len equ ($-s)/4
    d resb 4
    ten db 10
; our code starts here
segment code use32 class=code
;A string of doublewords is given. Compute the string formed by the high bytes of the low words from the ;elements of the doubleword string and these bytes should be multiple of 10
start:  
    mov esi, s
    cld
    mov ecx, len
    mov edi, d 
    jecxz end_loop
    repeat_label:
        lodsd
        shr eax, 8
        mov ah, 0
        mov ebx, 0
        mov bl, al
        div byte [ten]
        cmp ah, 0
        jnz nonmultiple
        mov al, bl
        stosb
        nonmultiple:
    loop repeat_label
        
    end_loop:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program