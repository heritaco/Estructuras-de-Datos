// Read out a list of 5 students with the next information:
// name, age, and the grades at the end of the 5 courses.
// Show the average of each student using a function.

#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char name[50];
    int age;
    float grades[5];
} Student;

// Function to calculate the average of the grades per student
float average(float grades[5])
{
    float sum = 0;
    for (int i = 0; i < 5; i++)
    {
        sum += grades[i];
    }
    int averagee = sum / 5;
    if (averagee < 6)
    {
        printf("Failed\t");
    }
    else
    {
        printf("Passed\t");
    }
    return averagee;
}

int main()
{
    Student students[5];

    for (int i = 0; i < 5; i++)
    {
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Age: ");
        scanf("%d", &students[i].age);
        for (int j = 0; j < 3; j++)
        {
            printf("Grade %d: ", j + 1);
            scanf("%f", &students[i].grades[j]);
        }
    }

    printf("\n\nAverage of students that passed\n");

    for (int i = 0; i < 5; i++)
    {
        printf("Name: %s\t", students[i].name);
        printf("Age: %d\t", students[i].age);
        printf("Average: %.2f\t", average(students[i].grades));
        printf("\n");
    }

    return 0;
}
