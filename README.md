# AI-Assisted Student Record and Result Management System

A console-based, menu-driven program in C that stores student records, calculates CGPA, and gives simple academic advice based on CGPA.

- **Course:** Programming in C (PRC1001), B.Tech CSE Semester I, UPES
- **Student:** Anubhav Jain (SAP ID: 590033623)
- **Source file:** `590033623.c`

## Features

1. Add a student record (SAP ID, Roll No., Name, Phone No., Email ID, Year, Semester, SGPA of all 8 semesters)
2. Prevents duplicate SAP IDs
3. Search and display a student by SAP ID
4. Display all student records
5. Delete a student record
6. CGPA of each student = average of the **available** SGPA values only
7. Average CGPA of students in each year (1st to 4th)
8. Display records in increasing order of SAP ID
9. Display records in increasing (alphabetical) order of Name (not case-sensitive)
10. AI-Assisted Academic Advisor (five categories using if-else)
11. Input validation for menu choice, SAP ID, year, semester and SGPA

## How to Compile and Run

You need the GCC compiler.

**Linux / macOS**
```
gcc -Wall -Wextra 590033623.c -o student
./student
```

**Windows (MinGW / Code::Blocks / VS Code terminal)**
```
gcc -Wall -Wextra 590033623.c -o student.exe
student.exe
```

**Run with the sample input file**
```
./student < tests/sample_input.txt
```
(On Windows Command Prompt: `student.exe < tests\sample_input.txt`.)

When input comes from a file, the typed values are not shown on screen. `tests/sample_output.txt` was recorded in a terminal, so it shows each prompt with the value entered.

## Input Rules

| Field | Rule |
|---|---|
| SAP ID | Whole number from 1 to 999999999, must be unique |
| Year | 1 to 4 |
| Semester | Must match the year (Year 1: Sem 1 or 2, Year 2: Sem 3 or 4, and so on) |
| SGPA | 0 to 10, or **-1** if the result is not declared |
| Text fields | Cannot be empty; extra characters beyond the field size are ignored |

The program asks for SGPA only up to the current semester. Later semesters are automatically stored as -1 (not available), because their results cannot exist yet. All 8 SGPA values are stored in the array.

The program can store up to 10 students (`#define MAX 10`). To change this, edit the `MAX` value.

## AI-Assisted Academic Advisor

| CGPA | Category | Advice |
|---|---|---|
| 9.5 and above | Outstanding Performance | Keep it up and take on research projects, hackathons or mentoring juniors |
| 8.5 to below 9.5 | Excellent Performance | Maintain your current study pattern and try projects or internships |
| 7.0 to below 8.5 | Good Performance | Revise weaker subjects regularly to reach the excellent range |
| 6.0 to below 7.0 | Needs Improvement | Focus more on subjects with lower SGPA and follow a daily study timetable |
| Below 6.0 | Requires Immediate Attention | Meet your faculty mentor and attend doubt/remedial classes |

If no SGPA is available, the program shows "CGPA: NA" with no category. No external AI API is used; the advice is produced by if-else statements in C. See `AI_USAGE_LOG.md` for how an AI tool was used.

## Functions Used

| Function | Purpose |
|---|---|
| `clearLine()` | Removes the remaining characters of the current input line |
| `readInt()` | Reads a whole number within a range and repeats on invalid input |
| `readSgpa()` | Reads one SGPA value (0–10 or -1) |
| `readStr()` | Reads a non-empty line of text safely |
| `findStudent()` | Linear search by SAP ID; returns the index or -1 |
| `calcCGPA()` | Average of available SGPA values, rounded to 2 decimals; -1 if none |
| `advisor()` | Prints CGPA and advice using if-else |
| `printStudent()` | Prints one complete student record |
| `addStudent()` | Adds a new student after checking capacity and duplicate SAP ID |
| `searchStudent()` | Searches by SAP ID and displays the record |
| `displayAll()` | Displays all records |
| `deleteStudent()` | Deletes a record by shifting later records one place left |
| `yearAverage()` | Average CGPA for each year 1 to 4 |
| `nameCmp()` | Compares two names alphabetically, ignoring upper/lower case |
| `sortStudents()` | Bubble sort by SAP ID (0) or by Name (1), then displays |
| `advisorReport()` | Shows CGPA and advice for every student |

## Menu

```
1. Add Student
2. Search Student
3. Display All Students
4. Delete Student
5. Year-wise Average CGPA
6. Display Sorted by SAP ID
7. Display Sorted by Name
8. AI Academic Advisor (all students)
0. Exit
```

## Repository Structure

```
student-record-ai-c/
├── 590033623.c
├── README.md
├── AI_USAGE_LOG.md
└── tests/
    ├── sample_input.txt
    └── sample_output.txt
```

## Limitations

- Records are kept in memory only and are lost when the program exits (file storage was not part of the assignment).
- Phone number and email format are not checked.
- Sorting rearranges the stored list, so later displays use the new order.
