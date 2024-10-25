#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definir la estructura genérica
typedef struct estructura
{
    void *datos; // Puntero genérico a cualquier tipo de datos
    int tipo;    // 1 para int, 2 para float, 3 para char*, etc.
} Estructura;

int main()
{
    int opcion;
    Estructura *puntero = malloc(sizeof(Estructura)); // Reservamos memoria para una estructura

    if (puntero == NULL)
    {
        printf("Error al reservar memoria.\n");
        return 1;
    }

    // Preguntar al usuario qué tipo de datos quiere ingresar
    printf("Seleccione el tipo de datos a almacenar:\n");
    printf("1. Entero (int)\n");
    printf("2. Flotante (float)\n");
    printf("3. Cadena (char*)\n");
    scanf("%d", &opcion);

    // Procesar la opción seleccionada
    switch (opcion)
    {
    case 1:
    {
        // Reservamos memoria para un entero
        puntero->datos = malloc(sizeof(int));
        puntero->tipo = 1; // Indicamos que el tipo es int
        printf("Ingrese un número entero: ");
        scanf("%d", (int *)puntero->datos); // Almacenamos el dato
        break;
    }
    case 2:
    {
        // Reservamos memoria para un float
        puntero->datos = malloc(sizeof(float));
        puntero->tipo = 2; // Indicamos que el tipo es float
        printf("Ingrese un número flotante: ");
        scanf("%f", (float *)puntero->datos); // Almacenamos el dato
        break;
    }
    case 3:
    {
        // Reservamos memoria para una cadena
        puntero->datos = malloc(100 * sizeof(char)); // Supongamos una cadena de 100 caracteres
        puntero->tipo = 3;                           // Indicamos que el tipo es char*
        printf("Ingrese una cadena de texto: ");
        getchar();                                                           // Consumimos el salto de línea anterior
        fgets((char *)puntero->datos, 100, stdin);                           // Almacenamos la cadena
        ((char *)puntero->datos)[strcspn((char *)puntero->datos, "\n")] = 0; // Eliminamos el salto de línea
        break;
    }
    default:
        printf("Opción inválida.\n");
        free(puntero); // Liberar memoria
        return 1;
    }

    // Mostrar los datos almacenados
    printf("\nDatos almacenados:\n");
    if (puntero->tipo == 1)
    {
        printf("Entero: %d\n", *(int *)puntero->datos); // Desreferenciar el puntero para int
    }
    else if (puntero->tipo == 2)
    {
        printf("Flotante: %.2f\n", *(float *)puntero->datos); // Desreferenciar el puntero para float
    }
    else if (puntero->tipo == 3)
    {
        printf("Cadena: %s\n", (char *)puntero->datos); // Imprimir la cadena de texto
    }

    // Liberar la memoria asignada para los datos
    free(puntero->datos);
    // Liberar la memoria de la estructura
    free(puntero);

    return 0;
}
