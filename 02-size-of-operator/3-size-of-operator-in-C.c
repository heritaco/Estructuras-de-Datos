#include <stdio.h>

// X porque es una direccion de memoria

int main()
{

    int const x = 10; // 10 variables, numbered from 0 to 9
    int arrayint[x];

    printf("\n%X = %X", &arrayint, &arrayint[0]);

    // Las direcciones coinciden
    return 0;
}