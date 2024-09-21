#include <stdio.h>

int main()
{
    int numero = 10;    // Una variable entera
    int *ptr = &numero; // Un puntero que almacena la dirección de "numero"

    // Imprimir el valor y la dirección de "numero"
    printf("Valor de numero: %d\n", numero);       // Imprime 10
    printf("Dirección de numero: %p\n", &numero);  // Imprime la dirección de memoria
    printf("Valor de ptr: %p\n", ptr);             // Imprime la misma dirección
    printf("Valor al que apunta ptr: %d\n", *ptr); // Imprime el valor en la dirección apuntada (10)

    return 0;
}
