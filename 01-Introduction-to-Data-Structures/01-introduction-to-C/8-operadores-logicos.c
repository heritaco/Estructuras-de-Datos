#include <stdio.h>

// Los que no son 0 son verdaderos

int main(void)
{
    int p = 10, q = 0, and, or, not ;

    and = p && q;
    or = p || q;
    not = !p;

    printf("%d\n", and);
    printf("%d\n", or);
    printf("%d\n", not );

    return 0;
}
