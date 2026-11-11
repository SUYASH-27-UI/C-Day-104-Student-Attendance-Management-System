
#include <stdio.h>

#define FILE_NAME "attendance.txt"

struct Student {
    int id;
    char name[50];
    int totalClasses;
    int attended;
};

float percentage(int attended, int total) {
    if (total == 0) {
        return 0;
    }

    return (attended * 100.0f) / total;
}

int findStudent(int id) {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        return 0;
    }

    while (fscanf(fp, "%d|%49[^|]|%d|%d\n",
                  &s.id, s.name,
                  &s.totalClasses, &s.attended) == 4) {
        if (s.id == id) {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void addStudent() {
    struct Student s;
    FILE *fp;

    printf("\nEnter Student ID: ");
    if (scanf("%d", &s.id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    if (findStudent(s.id)) {
        printf("Student ID already exists.\n");
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %49[^\n]", s.name);

    printf("Enter Total Classes: ");
    if (scanf("%d", &s.totalClasses) != 1) {
        printf("Invalid input.\n");
        return;
    }

    printf("Enter Attended Classes: ");
    if (scanf("%d", &s.attended) != 1) {
        printf("Invalid input.\n");
        return;
    }

    if (s.totalClasses <= 0 ||
        s.attended < 0 ||
        s.attended > s.totalClasses) {
        printf("Invalid attendance details.\n");
        return;
    }

    fp = fopen(FILE_NAME, "a");

    if (fp == NULL) {
        printf("Unable to open file.\n");
        return;
    }

    fprintf(fp, "%d|%s|%d|%d\n",
            s.id, s.name,
            s.totalClasses, s.attended);

    fclose(fp);

    printf("Attendance record added successfully.\n");
    printf("Attendance: %.2f%%\n",
           percentage(s.attended, s.totalClasses));
}

void displayStudents() {
    struct Student s;
    FILE *fp = fopen(FILE_NAME, "r");
    int found = 0;

    if (fp == NULL) {
        printf("\nNo attendance records found.\n");
        return;
    }

    printf("\n--- ATTENDANCE RECORDS ---\n");

    while (fscanf(fp, "%d|%49[^|]|%d|%d\n",
                  &s.id, s.name,
                  &s.totalClasses, &s.attended) == 4) {

        printf("\nID: %d\n", s.id);
        printf("Name: %s\n", s.name);
        printf("Total Classes: %d\n", s.totalClasses);
        printf("Attended: %d\n", s.attended);

        printf("Percentage: %.2f%%\n",
               percentage(s.attended, s.totalClasses));

        found = 1;
    }

    if (!found) {
        printf("No records available.\n");
    }

    fclose(fp);
}

void searchStudent() {
    struct Student s;
    int id, found = 0;

    FILE *fp = fopen(FILE_NAME, "r");

    if (fp == NULL) {
        printf("No attendance records found.\n");
        return;
    }

    printf("\nEnter Student ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        fclose(fp);
        return;
    }

    while (fscanf(fp, "%d|%49[^|]|%d|%d\n",
                  &s.id, s.name,
                  &s.totalClasses, &s.attended) == 4) {

        if (s.id == id) {
            float p = percentage(s.attended, s.totalClasses);

            printf("\nStudent Found!\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Attendance: %.2f%%\n", p);

            if (p < 75.0f) {
                printf("Status: Below 75%% attendance\n");
            } else {
                printf("Status: Attendance satisfactory\n");
            }

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Student not found.\n");
    }

    fclose(fp);
}

int main() {
    int choice;

    while (1) {
        printf("\n===== STUDENT ATTENDANCE SYSTEM =====\n");
        printf("1. Add Student Attendance\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Exit\n");

        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input.\n");
            break;
        }

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
                printf("Attendance system closed.\n");
                return 0;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}
