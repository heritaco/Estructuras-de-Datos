#include <stdio.h>

int main()
{
    int a[5];

    printf("\nEnter 5 ints (separated by a space, then press ENTER):\n");

    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        printf("Value: %d, Address: %p\n", a[i], (void *)&a[i]);
    }

    return 0;
}
