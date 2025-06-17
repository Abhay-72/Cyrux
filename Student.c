#include <stdio.h>
struct Student {
    int roll;
    char name[50];
    float marks;
};
union Employee {
    int roll;
    char name[50];
    float marks;
};

void main(){
    struct Student s1;
    union Employee s2;
    printf("Enter Student's detail:\n");
    printf("Enter Roll no.: ");
    scanf("%d",&s1.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]s",&s1.name);
    printf("Enter Marks: ");
    scanf("%f",&s1.marks);
    printf("\nRoll no.: %d\nName: %s\nMarks: %.2f",&s1.roll,&s1.name,&s1.marks);
    
    printf("\n\nEnter Roll no.: ");
    scanf("%d",&s2.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]s",&s2.name);
    printf("Enter Marks: ");
    scanf("%f",&s2.marks);
    printf("\nRoll no.: %d\nName: %s\nMarks: %.2f",&s2.roll,&s2.name,&s2.marks);
}