bits 32 ; assembling for the 32 bits architecture
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    a db 01101101b
    b dw 0001100101010011b
    c db 0
; our code starts here
segment code use32 class=code
start:
    ;Given the byte A and the word B, compute the byte C as follows:
    ;the bits 0-3 are the same as the bits 2-5 of A
    ;the bits 4-7 are the same as the bits 6-9 of B.
    mov al, [a]
    and al, 00111100b; al = 0010 1100b
    ror al, 2; al = 0000 1011b
    mov ah, 0
    mov bx, [b]
    and bx, 0000001111000000b
    ror bx, 2; bx = 0000 0000 0101 0000b
    or  ax, bx
    mov [c], al; c = 0101 1011
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program