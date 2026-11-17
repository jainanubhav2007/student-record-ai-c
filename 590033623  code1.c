#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10
#define SEMS 8

struct Student {
    int sap;
    char roll[20];
    char name[50];
    char phone[15];
    char email[50];
    int year;
    int sem;
    float sgpa[SEMS];
};

struct Student s[MAX];
int n = 0;

void clearLine() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int readInt(char msg[], int lo, int hi) {
    int x, r;
    while (1) {
        printf("%s", msg);
        r = scanf("%d", &x);
        if (r == EOF) exit(0);
        clearLine();
        if (r == 1 && x >= lo && x <= hi)
            return x;
        printf("Invalid input! Enter a number from %d to %d.\n", lo, hi);
    }
}

float readSgpa(int semNo) {
    float x;
    int r;
    while (1) {
        printf("Enter SGPA of Semester %d (-1 if result not declared): ", semNo);
        r = scanf("%f", &x);
        if (r == EOF) exit(0);
        clearLine();
        if (r == 1 && (x == -1 || (x >= 0 && x <= 10)))
            return x;
        printf("Invalid SGPA! Enter a value from 0 to 10, or -1.\n");
    }
}

void readStr(char msg[], char str[], int size) {
    int len;
    do {
        printf("%s", msg);
        if (fgets(str, size, stdin) == NULL) exit(0);
        len = strlen(str);
        if (len > 0 && str[len - 1] == '\n')
            str[len - 1] = '\0';
        else
            clearLine();
    } while (str[0] == '\0' || isspace(str[0]));
}

int findStudent(int sap) {
    int i;
    for (i = 0; i < n; i++)
        if (s[i].sap == sap)
            return i;
    return -1;
}




void addStudent() {
    int sap, i;
    if (n == MAX) {
        printf("Cannot add: maximum capacity of %d students reached.\n", MAX);
        return;
    }
    sap = readInt("Enter SAP ID: ", 1, 999999999);
    if (findStudent(sap) != -1) {
        printf("A student with SAP ID %d already exists!\n", sap);
        return;
    }
    s[n].sap = sap;
    readStr("Enter Roll No: ", s[n].roll, sizeof(s[n].roll));
    readStr("Enter Name: ", s[n].name, sizeof(s[n].name));
    readStr("Enter Phone No: ", s[n].phone, sizeof(s[n].phone));
    readStr("Enter Email ID: ", s[n].email, sizeof(s[n].email));
    s[n].year = readInt("Enter Year (1-4): ", 1, 4);
    s[n].sem = readInt("Enter Current Semester (must match the year): ", 2 * s[n].year - 1, 2 * s[n].year);
    for (i = 0; i < SEMS; i++) {
        if (i < s[n].sem)
            s[n].sgpa[i] = readSgpa(i + 1);
        else
            s[n].sgpa[i] = -1;
    }
    n++;
    printf("Student added successfully. Total students: %d\n", n);
}








int main() {
    int choice;
    do {
        printf("\n===== AI-ASSISTED STUDENT RECORD & RESULT MANAGEMENT =====\n");
        printf("1. Add Student\n2. Search Student\n3. Display All Students\n");
        printf("4. Delete Student\n5. Year-wise Average CGPA\n6. Display Sorted by SAP ID\n");
        printf("7. Display Sorted by Name\n8. AI Academic Advisor (all students)\n0. Exit\n");
        choice = readInt("Enter your choice: ", 0, 8);
        switch (choice) {
            case 1: addStudent(); break;
            case 0: printf("Exiting program. Goodbye!\n"); break;
        }
    } while (choice != 0);
    return 0;
}
