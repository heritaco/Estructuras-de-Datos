#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
    char name[50];
    int age;
    int num_grades;
    float *grades;
} Student;

// Function to calculate the average of the grades per student
float average(float *grades, int num_grades)
{
    float sum = 0;
    for (int i = 0; i < num_grades; i++)
    {
        sum += grades[i];
    }
    float avg = sum / num_grades;
    if (avg < 6)
    {
        printf("Failed\t");
    }
    else
    {
        printf("Passed\t");
    }
    return avg;
}

int main()
{
    int num_students;
    printf("How many students? ");
    scanf("%d", &num_students);

    // Dynamically allocate memory for the students
    Student *students = (Student *)malloc(num_students * sizeof(Student));
    if (students == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

    for (int i = 0; i < num_students; i++)
    {
        printf("\nStudent %d\n", i + 1);
        printf("Name: ");
        scanf("%s", students[i].name);
        printf("Age: ");
        scanf("%d", &students[i].age);
        printf("Number of grades: ");
        scanf("%d", &students[i].num_grades);

        // Dynamically allocate memory for the grades
        students[i].grades = (float *)malloc(students[i].num_grades * sizeof(float));
        if (students[i].grades == NULL)
        {
            printf("Memory allocation for grades failed\n");
            return 1;
        }

        for (int j = 0; j < students[i].num_grades; j++)
        {
            printf("Grade %d: ", j + 1);
            scanf("%f", &students[i].grades[j]);
        }
    }

    printf("\nAverage of students\n");

    for (int i = 0; i < num_students; i++)
    {
        printf("Name: %s\t", students[i].name);
        printf("Age: %d\t", students[i].age);
        printf("Average: %.2f\t", average(students[i].grades, students[i].num_grades));
        printf("\n");
    }

    // Free the allocated memory for grades and students
    for (int i = 0; i < num_students; i++)
    {
        free(students[i].grades);
    }
    free(students);

    return 0;
}