bits 32
global start
extern exit
import exit msvcrt.dll
extern printf, scanf
import printf msvcrt.dll
import scanf  msvcrt.dll

extern conversion

segment data use32 class = data
    nr resb 20
    stringf db "%s", 0
    hexaf db "%x", 10, 0
    
    
segment code use32 class = code
;Multiple numbers in base 2 are read from the keyboard. Display these numbers in the base 16.
start:
    numbers_loop:
        push dword nr
        push dword stringf
        call [scanf] 
        add esp, 4*2
        
        push dword nr
        call conversion
        add esp, 4 * 2
        
        push edx
        push dword hexaf
        call [printf]
        add esp, 4*2
        jmp numbers_loop
    
    push dword 0
    call [exit]  

            
            
            