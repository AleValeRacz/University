bits 32 ; assembling for the 32 bits architecture
global start        
; declare external functions needed by our program
extern exit            ; tell nasm that exit exists even if we won't be defining it
extern printf
extern scanf
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import printf msvcrt.dll
import scanf msvcrt.dll
segment data use32 class=data
    a db 0
    b db 0
    k dw 6
    message_a db "a=", 0
    message_b db "b=", 0
    format db "%d", 0
    print_format db "r = %x", 0
; our code starts here
segment code use32 class=code
;Two numbers a and b are given. Compute the expression value: (a-b)*k, where k is a constant value defined in data segment. Display the expression value (in base 16).
start:  
    push dword message_a
    call [printf]
    add esp, 4*1
    
    push dword a
    push dword format
    call [scanf]
    add esp, 4 * 2
    
    push dword message_b
    call [printf]
    add esp, 4*1
    
    push dword b
    push dword format
    call [scanf]
    add esp, 4*2
    
    mov ax, word[a]
    sub ax, word[b]
    imul word[k]
    push dx
    push ax
    push dword print_format
    call [printf]
    add esp, 4*3

        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program