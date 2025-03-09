bits 32 ; assembling for the 32 bits architecture
; declare the EntryPoint (a label defining the very first instruction of the program)
global start        
; declare external functions needed by our program
extern exit               ; tell nasm that exit exists even if we won't be defining it
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
                          ; msvcrt.dll contains exit, printf and all the other important C-runtime specific functions
; our data is declared here (the variables needed by our program)
segment data use32 class=data
    r dd 01010010111101100101110110000101b
    t dd 00010100001011111101110000101101b
    q dd 0
; our code starts here
segment code use32 class=code
    start:
    ;Given 2 dwords R and T. Compute the doubleword Q as follows:
    ;the bits 0-6 of Q are the same as the bits 10-16 of T
    ;the bits 7-24 of Q are the same as the bits 7-24 of (R XOR T).
    ;the bits 25-31 of Q are the same as the bits 5-11 of R.
    mov eax, [t]
    and eax, 00000000000000011111110000000000b
    ror eax, 10
    mov ebx, [t]
    mov ecx, [r]
    xor ebx, ecx; ebx=(r xor t)
    and ebx, 00000001111111111111111110000000b
    or eax, ebx
    and ecx, 00000000000000000000111111100000b
    rol ecx, 20
    or eax, ecx
    mov [q], eax
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program