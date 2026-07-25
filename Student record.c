#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    int age;
    float marks;
};

void addStudent();
void displayStudents();
void searchStudent();
void updateStudent();
void deleteStudent();

int main() {
    int choice;

    while (1) {
        printf("\n=====================================\n");
        printf("   STUDENT RECORD MANAGEMENT SYSTEM\n");
        printf("=====================================\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Thank you!\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}

void addStudent() {
    FILE *fp = fopen("students.dat", "ab");
    struct Student s;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Roll Number: ");
    scanf("%d", &s.roll);

    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent Added Successfully!\n");
}

void displayStudents() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("\n-----------------------------------------------------\n");
    printf("Roll\tName\t\tAge\tMarks\n");
    printf("-----------------------------------------------------\n");

    while (fread(&s, sizeof(s), 1, fp)) {
        printf("%d\t%-15s\t%d\t%.2f\n",
               s.roll, s.name, s.age, s.marks);
    }

    fclose(fp);
}

void searchStudent() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    printf("Enter Roll Number to Search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {
            printf("\nStudent Found\n");
            printf("Roll : %d\n", s.roll);
            printf("Name : %s\n", s.name);
            printf("Age : %d\n", s.age);
            printf("Marks : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void updateStudent() {
    FILE *fp = fopen("students.dat", "rb+");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Roll Number to Update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {
        if (s.roll == roll) {

            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter New Age: ");
            scanf("%d", &s.age);

            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, fp);

            found = 1;
            printf("\nRecord Updated Successfully!\n");
            break;
        }
    }

    if (!found)
        printf("Student Not Found!\n");

    fclose(fp);
}

void deleteStudent() {
    FILE *fp, *temp;
    struct Student s;
    int roll, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("Enter Roll Number to Delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.roll == roll) {
            found = 1;
            continue;
        }

        fwrite(&s, sizeof(s), 1, temp);
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("Student Deleted Successfully!\n");
    else
        printf("Student Not Found!\n");
}