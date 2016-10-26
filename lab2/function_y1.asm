SECTION .text
    global function_y1
function_y1:
    push ebp
    mov ebp, esp
    mov eax, [ebp+8]; a
    mov ebx, [ebp+12]; x
    cmp eax, ebx
    jge aGreaterThenX
    add eax, ebx
    jmp return
    aGreaterThenX:
    shl eax, 1
    sub eax, ebx
    return:
    pop ebp
    ret
