#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct libro {
    char titulo[100]; // Título del libro
    int paginas;      // Número de páginas
    float precio;     // Precio del libro
} Libro;

int main() {
    int cantidadLibros = 0;        // Contador para la cantidad de libros
    int capacidad = 2;             // Capacidad inicial (puede ser cualquier número)
    Libro *libros = malloc(capacidad * sizeof(Libro)); // Reservamos memoria para 2 libros inicialmente

    if (libros == NULL) {
        printf("Error al reservar memoria.\n");
        return 1;
    }

    char continuar;

    do {
        // Si llegamos al límite de capacidad, ampliamos el tamaño del arreglo
        if (cantidadLibros == capacidad) {
            capacidad *= 2;  // Duplicamos la capacidad
            libros = realloc(libros, capacidad * sizeof(Libro));
            if (libros == NULL) {
                printf("Error al ampliar memoria.\n");
                return 1;
            }
        }

        // Pedimos al usuario que ingrese los datos del libro
        printf("Ingrese el título del libro: ");
        getchar();  // Consumimos el salto de línea previo
        fgets(libros[cantidadLibros].titulo, 100, stdin);
        libros[cantidadLibros].titulo[strcspn(libros[cantidadLibros].titulo, "\n")] = 0;  // Eliminamos el salto de línea

        printf("Ingrese el número de páginas: ");
        scanf("%d", &libros[cantidadLibros].paginas);

        printf("Ingrese el precio del libro: ");
        scanf("%f", &libros[cantidadLibros].precio);

        cantidadLibros++;  // Incrementamos la cantidad de libros ingresados

        // Preguntamos si quiere ingresar otro libro
        printf("¿Desea ingresar otro libro? (s/n): ");
        getchar();  // Consumimos el salto de línea previo
        continuar = getchar();

    } while (continuar == 's' || continuar == 'S');

    // Mostrar todos los libros ingresados
    printf("\nLista de libros ingresados:\n");
    for (int i = 0; i < cantidadLibros; i++) {
        printf("Libro %d: \n", i + 1);
        printf("Título: %s\n", libros[i].titulo);
        printf("Páginas: %d\n", libros[i].paginas);
        printf("Precio: %.2f\n\n", libros[i].precio);
    }

    // Liberar la memoria dinámica al final
    free(libros);

    return 0;
}
