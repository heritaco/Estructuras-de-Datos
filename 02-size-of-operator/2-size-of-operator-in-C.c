#include <stdio.h>
#include <stdlib.h>

int main()
{
    int arrayint[10];
    float arrayfloat[10];
    char arraychar[10];
    double arraydouble[10];

    printf("Size of Primitive Data Type\n");
    printf("Size of array int: %ld bytes\n", sizeof(arrayint));
    printf("Size of array float: %ld bytes\n", sizeof(arrayfloat));
    printf("Size of array char: %ld bytes\n", sizeof(arraychar));
    printf("Size of array double: %ld bytes\n", sizeof(arraydouble));

    return 0;
}