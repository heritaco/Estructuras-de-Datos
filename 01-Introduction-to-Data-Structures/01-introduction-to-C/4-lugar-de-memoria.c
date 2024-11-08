#include <stdio.h>

int main()
{
    int a[10];
    a[1] = 32;

    printf("Value: %d\n", a[1]);
    printf("Address: %p\n", (void *)&a[1]);

    return 0;
}
