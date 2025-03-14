/*
 * main.c
 *
 *  Created on: Aug 11, 2024
 *      Author: yahia raouf
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Student Structure
struct student {
    char name[50];
    int id;
    int age;
    float gpa;
};

// Node structure for linked list
struct node {
    struct student data;
    struct node *next;
};

struct node *head = NULL;

// Function Prototypes
void enterData(struct student*);
void addStudent(const struct student* const);
void displayStudents();
void searchStudentById(int);
void updateStudent(int);
float calculateAverageGPA();
void searchHighestGPA();
void deleteStudent(int);

int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    struct student students;
    char input = 0;
    int id = 0;

    while (1) {
        printf("\n__________STUDENT MANAGEMENT SYSTEM__________\n\n");
        printf("MENU\n");
        printf("1] Add Student To Database\n");
        printf("2] Display All Students\n");
        printf("3] Search For Student By ID\n");
        printf("4] Update Student Data\n");
        printf("5] Calculate Average GPA\n");
        printf("6] Display Student With Highest GPA\n");
        printf("7] Delete Student From Database\n");
        printf("8] Exit\n");

        printf("Enter your choice: ");
        scanf(" %c", &input);
        while (getchar() != '\n'); // Clear input buffer

        switch (input) {
            case '1':
                enterData(&students);
                addStudent(&students);
                break;
            case '2':
                displayStudents();
                break;
            case '3':
                printf("Enter Student's ID: ");
                scanf("%d", &id);
                searchStudentById(id);
                break;
            case '4':
                printf("Enter Student's ID: ");
                scanf("%d", &id);
                updateStudent(id);
                break;
            case '5':
                printf("Average GPA: %.2f\n", calculateAverageGPA());
                break;
            case '6':
                searchHighestGPA();
                break;
            case '7':
                printf("Enter Student's ID: ");
                scanf("%d", &id);
                deleteStudent(id);
                break;
            case '8':
                exit(0);
            default:
                printf("Invalid choice, please try again!\n");
        }
    }
}

void enterData(struct student *stdnt) {
    printf("Enter Student's Name: ");
    scanf("%[^\n]s", stdnt->name);
    //fgets(stdnt->name, sizeof(stdnt->name), stdin);
    printf("Enter Student ID: ");
    scanf("%d", &stdnt->id);
    printf("Enter Student's Age: ");
    scanf("%d", &stdnt->age);
    printf("Enter Student's GPA: ");
    scanf("%f", &stdnt->gpa);
}

void addStudent(const struct student *const students) {
    struct node *current = head;
    struct node *newNode = (struct node*) malloc(sizeof(struct node));

    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = *students;
    newNode->next = NULL;

    if (head == NULL) {
        head = newNode;
    } else {
        while (current->next != NULL) {
            if (current->data.id == students->id) {
                printf("Error: Student ID already exists!\n");
                free(newNode);
                return;
            }
            current = current->next;
        }
        current->next = newNode;
    }
    printf("Student Added Successfully!\n");
}

void displayStudents() {
    struct node *current = head;
    if (current == NULL) {
        printf("No students in the list!\n");
        return;
    }
    printf("\nStudent Data:\n");
    while (current != NULL) {
        printf("ID: %d\nName: %s\nAge: %d\nGPA: %.2f\n\n",
               current->data.id, current->data.name, current->data.age, current->data.gpa);
        current = current->next;
    }
}

void searchStudentById(int id) {
    struct node *current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            printf("Student Found:\nID: %d\nName: %s\nAge: %d\nGPA: %.2f\n",
                   current->data.id, current->data.name, current->data.age, current->data.gpa);
            return;
        }
        current = current->next;
    }
    printf("Student Not Found!\n");
}

void updateStudent(int id) {
    struct node *current = head;
    while (current != NULL) {
        if (current->data.id == id) {
            printf("Updating Student Record:\n");
            enterData(&current->data);
            printf("Student data updated successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Student Not Found!\n");
}

float calculateAverageGPA() {
    struct node *current = head;
    if (!current) return 0.0;

    float sum = 0;
    int count = 0;

    while (current != NULL) {
        sum += current->data.gpa;
        count++;
        current = current->next;
    }
    return sum / count;
}

void searchHighestGPA() {
    if (!head) {
        printf("No students found!\n");
        return;
    }
    struct node *current = head, *highest = head;
    while (current != NULL) {
        if (current->data.gpa > highest->data.gpa) highest = current;
        current = current->next;
    }
    printf("Student with Highest GPA:\nID: %d\nName: %s\nAge: %d\nGPA: %.2f\n",
           highest->data.id, highest->data.name, highest->data.age, highest->data.gpa);
}

void deleteStudent(int id) {
    struct node **indirect = &head, *temp;
    while (*indirect && (*indirect)->data.id != id)
        indirect = &((*indirect)->next);
    if (*indirect) {
        temp = *indirect;
        *indirect = (*indirect)->next;
        free(temp);
        printf("Student Deleted Successfully!\n");
    } else {
        printf("Student Not Found!\n");
    }
}
