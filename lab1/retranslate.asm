section .data
    buffer db 0
    hello_msg db 'Enter string: ', 0x00
    hello_msg_len: equ $-hello_msg
    dest_filename db 'result.txt', 0x00
    STDIN_FILE: equ 0
    STDOUT_FILE: equ 1
    dest_fd dd 0
section .text
    global main 
main:
    mov eax, 4
    mov ebx, STDOUT_FILE
    mov ecx, hello_msg
    mov edx, 15
    int 0x80
    
    mov eax, 8 ; Create and truncate file
    mov ebx, dest_filename
    mov ecx, 0400q | 200q | 0x900; O_CREAT | O_TRUNC | S_IRWU
    int 0x80    
    
    mov eax, 5 ; Open file
    mov ebx, dest_filename
    mov ecx, 0x02 
    int 0x80
    mov [dest_fd], eax ; Get result of open file syscall
        
    mov ecx, 1
    cycle:
        mov eax, 3
        mov ebx, STDIN_FILE
        push ecx
        mov ecx, buffer
        mov edx, 1
        int 0x80 
        pop ecx

        test ecx, 1
        jne if_odd 
        
        mov eax, 4
        mov ebx, [dest_fd]
        push ecx
        mov ecx, buffer
        mov edx, 1 
        int 0x80
        pop ecx

        if_odd:
        inc ecx
        cmp byte [buffer], 10
    jne cycle

    mov eax, 6
    mov ebx, [dest_fd]
    int 0x80

    mov eax, 0
    mov ebx, 1
    int 0x80 

