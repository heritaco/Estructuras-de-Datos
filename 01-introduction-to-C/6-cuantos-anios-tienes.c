#include <stdio.h>

int day, month, year, age;
char nombre[50]; // Declare a character array for the name

int main()
{
    printf("Nombre: ");
    scanf("%s", nombre); // Corrected the scanf syntax

    printf("Fecha de nacimiento (daa mes anio, separados por espacios): ");
    scanf("%d %d %d", &day, &month, &year);

    age = 2024 - year;

    printf("\nHola! %s, tienes %d anios porque naciste el %02d/%02d/%d y estamos en 2024!", nombre, age, day, month, year);

    return 0;
}
