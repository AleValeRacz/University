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
    number db 0
    message1 db "number =", 0
    message db "%x in base 10 is %d", 0
    hexa db "%x", 0
; our code starts here
segment code use32 class=code

start:  
    push dword message1
    call [printf]
    add esp, 4
    
    push dword number
    push dword hexa
    call [scanf]
    add esp, 4 * 2
    
    push dword [number]
    push dword [number]
    push dword message
    call [printf]
    add esp, 4*3
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program