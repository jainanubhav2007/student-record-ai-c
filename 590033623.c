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

float calcCGPA(struct Student st) {
    float sum = 0;
    int i, count = 0;
    for (i = 0; i < SEMS; i++) {
        if (st.sgpa[i] >= 0) {
            sum += st.sgpa[i];
            count++;
        }
    }
    if (count == 0)
        return -1;
    return (int)(sum / count * 100 + 0.5) / 100.0f;
}

void advisor(float cg) {
    if (cg < 0) {
        printf("CGPA   : NA\nAdvice : No result declared yet - advice will be given after the first semester result.\n");
        return;
    }
    printf("CGPA   : %.2f\nAdvice : ", cg);
    if (cg >= 9.5)
        printf("Outstanding Performance - keep it up and take on research projects, hackathons or mentoring juniors.\n");
    else if (cg >= 8.5)
        printf("Excellent Performance - maintain your current study pattern and try projects or internships.\n");
    else if (cg >= 7.0)
        printf("Good Performance - revise your weaker subjects regularly to reach the excellent range.\n");
    else if (cg >= 6.0)
        printf("Needs Improvement - focus more on subjects with lower SGPA and follow a daily study timetable.\n");
    else
        printf("Requires Immediate Attention - meet your faculty mentor and attend doubt/remedial classes.\n");
}

void printStudent(struct Student st) {
    int i;
    printf("\nSAP ID : %d | Roll No: %s | Name: %s\n", st.sap, st.roll, st.name);
    printf("Phone  : %s | Email: %s\n", st.phone, st.email);
    printf("Year   : %d | Semester: %d\n", st.year, st.sem);
    printf("SGPA   :");
    for (i = 0; i < SEMS; i++) {
        if (st.sgpa[i] < 0)
            printf("   NA");
        else
            printf(" %4.2f", st.sgpa[i]);
    }
    printf("\n");
    advisor(calcCGPA(st));
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

void searchStudent() {
    int idx = findStudent(readInt("Enter SAP ID to search: ", 1, 999999999));
    if (idx == -1)
        printf("Student not found.\n");
    else
        printStudent(s[idx]);
}

void displayAll() {
    int i;
    if (n == 0) {
        printf("No student records available.\n");
        return;
    }
    for (i = 0; i < n; i++)
        printStudent(s[i]);
}

void deleteStudent() {
    int i, idx = findStudent(readInt("Enter SAP ID to delete: ", 1, 999999999));
    if (idx == -1) {
        printf("Student not found.\n");
        return;
    }
    for (i = idx; i < n - 1; i++)
        s[i] = s[i + 1];
    n--;
    printf("Student deleted successfully. Total students: %d\n", n);
}

void yearAverage() {
    int y, i, count;
    float sum, cg;
    for (y = 1; y <= 4; y++) {
        sum = 0;
        count = 0;
        for (i = 0; i < n; i++) {
            cg = calcCGPA(s[i]);
            if (s[i].year == y && cg >= 0) {
                sum += cg;
                count++;
            }
        }
        if (count == 0)
            printf("Year %d: No students with declared results\n", y);
        else
            printf("Year %d: Average CGPA = %.2f (students counted: %d)\n", y, sum / count, count);
    }
}

int nameCmp(char a[], char b[]) {
    int i = 0;
    while (a[i] != '\0' && tolower(a[i]) == tolower(b[i]))
        i++;
    return tolower(a[i]) - tolower(b[i]);
}

void sortStudents(int byName) {
    int i, j, swap;
    struct Student t;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - 1 - i; j++) {
            if (byName)
                swap = nameCmp(s[j].name, s[j + 1].name) > 0;
            else
                swap = s[j].sap > s[j + 1].sap;
            if (swap) {
                t = s[j];
                s[j] = s[j + 1];
                s[j + 1] = t;
            }
        }
    }
    displayAll();
}

void advisorReport() {
    int i;
    if (n == 0) {
        printf("No student records available.\n");
        return;
    }
    for (i = 0; i < n; i++) {
        printf("\n%d - %s\n", s[i].sap, s[i].name);
        advisor(calcCGPA(s[i]));
    }
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
            case 2: searchStudent(); break;
            case 3: displayAll(); break;
            case 4: deleteStudent(); break;
            case 5: yearAverage(); break;
            case 6: sortStudents(0); break;
            case 7: sortStudents(1); break;
            case 8: advisorReport(); break;
            case 0: printf("Exiting program. Goodbye!\n"); break;
        }
    } while (choice != 0);
    return 0;
}
