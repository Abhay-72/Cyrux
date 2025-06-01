#include <stdio.h>
//#include <conio.h>
#include <stdlib.h>

void addStudent();
void viewRecord();
void searchStudent();
void deleteStudent();

struct Student {
    int roll;
    char name[50];
    int age;
    char branch[50];
    char add[200];
    float per; // in percentage
}s;

void main() {
    int choice = 0;
    while (choice != 5) {
        printf("\n\t\t\t\t  ======= Student Database Management System =======\n");
        printf("\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
        printf("\n\n\t\t\t\t\t  1. Add Student Record\n");
        printf("\t\t\t\t\t  2. View Student Record\n");
        printf("\t\t\t\t\t  3. Search Student Record\n");
        printf("\t\t\t\t\t  4. Delete Student Record\n");
        printf("\t\t\t\t\t  5. Exit Student Record\n");
        printf("\n\t\t\t\t=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
        
        printf("\t\t\t\tEnter your choice: ");
        scanf("%d", &choice);
        getchar(); // Clear newline character from buffer

        switch (choice) {
            case 1:
                //clrscr();
                addStudent();
                break;
            case 2:
                //clrscr();
                viewRecord();
                printf("\n\t\t\t\t Press any key for Exit...!!!\n");
                getchar();
                break;
            case 3:
                searchStudent();
                printf("\n\t\t\t\t Press any key for Exit..!!!\n");
                break;
            case 4:
                deleteStudent();
                printf("\n\t\t\t\t Press any key for Exit..!!!\n");
                break;
            case 5:
                printf("\t\t\t\t Exiting...\n");
                exit(0);
                break;
            default:
                printf("\t\t\t\t Invalid choice. Try again.\n");
        }
    }
}

void addStudent() {
    char other;
    FILE* fp;
    do {
        printf("\n\t\t\t\t ========= Add Student's info =========\n");
        fp = fopen("student.txt", "ab");
        if (fp == NULL) {
            fprintf(stderr, "\t\t\t\tCan't Open File...\n");
            return;
        }

        printf("\n\t\t\t\t Enter Roll No.    : ");
        scanf("%d", &s.roll);
        getchar();
        printf("\t\t\t\t Enter Name        : ");
        fgets(s.name, sizeof(s.name), stdin);
        printf("\t\t\t\t Enter Age         : ");
        scanf("%d", &s.age);
        getchar();
        printf("\t\t\t\t Enter Branch      : ");
        fgets(s.branch, sizeof(s.branch), stdin);
        printf("\t\t\t\t Enter Marks(in %%) : ");
        scanf("%f", &s.per);
        getchar();
        printf("\t\t\t\t Enter Address     : ");
        fgets(s.add, sizeof(s.add), stdin);

        fwrite(&s, sizeof(struct Student), 1, fp);
        fclose(fp);

        printf("\n\t\t\t\t______________________________________________\n");
        printf("\n\t\t\t\t Record is Stored Successfully...\n");
        printf("\n\t\t\t\t Do you want to add another record? (y/n): ");
        scanf(" %c", &other);
        getchar();

    } while (other == 'y' || other == 'Y');
}

void viewRecord() {
    FILE* fp;
    fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        fprintf(stderr, "\t\t\t\tCan't Open File...\n");
        return;
    }

    printf("\t\t\t\t ======= Students Records =======\n");
    printf("\t\t\t\t=============================================\n\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\n\t\t\t\tStudent's Roll No. : %d", s.roll);
        printf("\n\t\t\t\tStudent's Name     : %s", s.name);
        printf("\n\t\t\t\tStudent's Age      : %d", s.age);
        printf("\n\t\t\t\tStudent's Branch   : %s", s.branch);
        printf("\n\t\t\t\tStudent's Marks    : %.2f", s.per);
        printf("\n\t\t\t\tStudent's Address  : %s", s.add);
        printf("\n\t\t\t\t______________________________________________\n");
    }
    fclose(fp);
}

void searchStudent(){
    int roll, found=0;
    FILE* fp;
    fp = fopen("student.txt", "rb");

    printf("\t\t\t\t ======= Search in Student's Records =======\n");
    printf("\t\t\t\t=============================================\n");
    printf("\t\t\t\tEnter Roll No. : ");
    scanf("%d",&roll);
    printf("\t\t\t\t=============================================\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if(s.roll == roll){
            found = 1;
            printf("\n\t\t\t\tStudent's Roll No. : %d", s.roll);
            printf("\n\t\t\t\tStudent's Name     : %s", s.name);
            printf("\n\t\t\t\tStudent's Age      : %d", s.age);
            printf("\n\t\t\t\tStudent's Branch   : %s", s.branch);
            printf("\n\t\t\t\tStudent's Marks    : %.2f", s.per);
            printf("\n\t\t\t\tStudent's Address  : %s", s.add);
            printf("\n\t\t\t\t______________________________________________\n");
        }
    }

    if(!found){
        printf("\n\t\t\t\t Record not found in the DataBase...\n");
    }
    fclose(fp);
}

void deleteStudent() {
    int roll, found = 0;
    FILE *fp, *fp1;

    printf("\n\t\t\t\t ======= Delete from Student's Records =======\n");
    printf("\t\t\t\t===============================================\n");
    printf("\t\t\t\tEnter Roll No. : ");
    scanf("%d", &roll);
    printf("\t\t\t\t===============================================\n");

    fp = fopen("student.txt", "rb");
    if (fp == NULL) {
        fprintf(stderr, "\t\t\tCan't Open File...\n");
        return;
    }

    fp1 = fopen("temp.txt", "wb"); // Temporary file
    if (fp1 == NULL) {
        fprintf(stderr, "\t\t\tCan't Open Temporary File...\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, fp1);
        }
    }

    fclose(fp);
    fclose(fp1);

    if (found) {
        remove("student.txt");
        rename("temp.txt", "student.txt");
        printf("\n\t\t\t\t Record deleted Successfully...\n");
    } else {
        printf("\n\t\t\t\t Record not found in the Database...\n");
        remove("temp.txt"); // Cleanup
    }
}