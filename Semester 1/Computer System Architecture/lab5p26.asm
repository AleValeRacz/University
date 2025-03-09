bits 32 ; assembling for the 32 bits architecture
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    s db 1, 4, 2, 3, 8, 4, 9, 5
    l equ $-s
    max_even db 0
    min_odd db 0
    two db 2
; our code starts here
segment code use32 class=code
start:  
;A byte string S is given. Obtain the maximum of the elements found on the even positions and the minimum of the elements found on the odd positions of S
    mov esi, s
    mov al, [esi]
    mov [max_even], al
    mov al, [esi+1]
    mov [min_odd], al
    mov ecx, l-2
    add esi, 2
    mov bx, 1
    jecxz end_loop
    repeat_label:
        mov dl, [esi]
        inc bx
        mov ax, bx
        idiv byte [two]
        cmp ah, 1
        jne even_poz
            cmp dl, [min_odd]
            jge continuation
            mov [min_odd], dl
            jmp continuation
        even_poz:
            cmp dl, [max_even]
            jle continuation
            mov [max_even], dl
        continuation:
            inc esi   
        loop repeat_label
        end_loop:
        
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program