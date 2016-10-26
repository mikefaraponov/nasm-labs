int function_y2(int a, int x) {
    int y2;
    asm volatile(
        "mov eax, %1\n"
        "mov ebx, %2\n"
        "cmp ebx, 10\n"
        "jg gthen\n"
        "mov %0, ebx\n"
        "jmp else\n"
        "gthen:\n"
        "imul eax, ebx\n"
        "mov %0, eax\n"
        "else:\n"
        : "=r"(y2) // %0
        : "r"(a), "r"(x) // %1, %2
    );
    return y2;
}
