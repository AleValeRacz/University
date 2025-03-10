
bits 32 ; assembling for the 32 bits architecture
global start        
; declare external functions needed by our program
extern exit            ; tell nasm that exit exists even if we won't be defining it
extern fopen, fclose, fprintf, scanf, printf
import exit msvcrt.dll    ; exit is a function that ends the calling process. It is defined in msvcrt.dll
import fopen msvcrt.dll
import printf msvcrt.dll
import fclose msvcrt.dll
import fprintf msvcrt.dll
import scanf msvcrt.dll
import printf msvcrt.dll
segment data use32 class=data
    file_name db "p26.txt", 0
    access_mode db "w", 0
    file_descriptor dd -1
    message1 db "enter text:", 0
    format db "%s", 0
    newline db "%s", 10, 0
    text resb 100

;A file name (defined in data segment) is given. Create a file with the given name, then read words from the keyboard until character '$' is read. Write only the words that contain at least one uppercase letter to file

; our code starts here
segment code use32 class=code
start:  
    push dword access_mode
    push dword file_name
    call [fopen]
    add esp, 4*2
    mov [file_descriptor], eax
    cmp eax, 0
    je final
    read_loop:
        push dword message1
        call [printf]
        add esp, 4*1
        push dword text
        push dword format
        call [scanf]
        add esp, 4*2
        mov al, [text]
        mov bl, '$'
        cmp al, bl
        jz close_file
        mov esi, text
        check_uppercase:
            lodsb
            cmp al, 0
            jz read_loop
            cmp al, 'A'
            jb check_uppercase
            cmp al, 'Z'
            ja check_uppercase
            push dword text
            push dword newline
            push dword [file_descriptor]
            call [fprintf]
            add esp, 4*3
            jmp read_loop
        
    close_file:
        push dword [file_descriptor]
        call [fclose]
        add esp, 4
    final:
    
        ; exit(0)
        push    dword 0      ; push the parameter for exit onto the stack
        call    [exit]       ; call exit to terminate the program