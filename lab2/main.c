#include <stdio.h>
#include <stdlib.h>

extern int function_y1(int a, int x);
extern int function_y2(int a, int x);

int main(int argc, char **argv) {
    int a, x, y;
    if(argc > 1) {
        puts("Usage: lab2");
        return EXIT_FAILURE;
    }
    printf(
        "Hello, user!\n"
        "Please, enter a: "
    );
    scanf("%d", &a);
    printf("Enter x: ");
    scanf("%d", &x);
    int y1 = function_y1(a, x);
    int y2 = function_y2(a, x);
    y = y1 + y2;
    printf("y is equal: %d!\n", y);
    return EXIT_SUCCESS;
}
