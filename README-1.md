# Student Management System (C++)

A console-based Student Management System written in C++ that manages student records using file handling and a menu-driven interface.

## Features
- Add, display, search, update and delete student records
- Persistent storage in `students.txt` (data stays after closing the program)
- Menu-driven navigation with input validation

## How to run
```bash
g++ main.cpp -o student_app
./student_app        # Windows: student_app.exe
```

## Sample menu
```
===== STUDENT MANAGEMENT SYSTEM =====
1. Add Student
2. Display All Students
3. Search Student
4. Update Student
5. Delete Student
6. Exit
```

## Concepts used
Structs, vectors, file I/O (`ifstream` / `ofstream`), functions, input validation, switch-case menu.
