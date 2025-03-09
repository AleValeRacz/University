bits 32 ; assembling for the 32 bits architecture
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1, 5, 3, 8, 2, 9
    l equ $-s
    d1 resb 10
    d2 resb 10
    two db 2
; our code starts here
segment code use32 class=code
start:  
;A byte string S is given. Obtain the string D1 which contains all the even numbers of S and the string D2 which contains all the odd numbers of S
    mov esi, s
    mov edi, d1
    mov ebx, d2
    mov ecx, l
    mov dl, [two]
    jecxz end_loop
    repeat_label: 
        mov al, [esi]
        test al,1
        jz even_nr
            mov [d2], esi
            inc ebx
            jmp over_even
        even_nr:
            mov [d1], esi
            inc edi
        over_even:
           inc esi 
    loop repeat_label
    end_loop:
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program