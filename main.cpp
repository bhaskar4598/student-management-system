// Student Management System - console based, C++
// Features: Add, Display, Search, Update, Delete + file handling (students.txt)

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

const string FILE_NAME = "students.txt";

struct Student {
    int roll;
    string name;
    string course;
    float marks;
};

vector<Student> students;

// ---------- File handling ----------
void loadFromFile() {
    students.clear();
    ifstream in(FILE_NAME);
    if (!in) return;  // file doesn't exist yet
    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        Student s;
        string rollStr, marksStr;
        getline(ss, rollStr, '|');
        getline(ss, s.name, '|');
        getline(ss, s.course, '|');
        getline(ss, marksStr, '|');
        try {
            s.roll = stoi(rollStr);
            s.marks = stof(marksStr);
            students.push_back(s);
        } catch (...) {
            // skip corrupted line
        }
    }
}

void saveToFile() {
    ofstream out(FILE_NAME);
    for (const auto &s : students)
        out << s.roll << '|' << s.name << '|' << s.course << '|' << s.marks << '\n';
}

// ---------- Helpers ----------
int findIndex(int roll) {
    for (size_t i = 0; i < students.size(); i++)
        if (students[i].roll == roll) return (int)i;
    return -1;
}

int readInt(const string &prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Number daalo.\n";
    }
}

float readMarks(const string &prompt) {
    float x;
    while (true) {
        cout << prompt;
        if (cin >> x && x >= 0 && x <= 100) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid! Marks 0 se 100 ke beech hone chahiye.\n";
    }
}

string readLine(const string &prompt) {
    string s;
    do {
        cout << prompt;
        getline(cin, s);
    } while (s.empty());
    // '|' is our file separator, so remove it from input
    for (char &c : s) if (c == '|') c = '-';
    return s;
}

void printHeader() {
    cout << left << setw(8) << "Roll" << setw(22) << "Name"
         << setw(18) << "Course" << setw(8) << "Marks" << '\n';
    cout << string(56, '-') << '\n';
}

void printStudent(const Student &s) {
    cout << left << setw(8) << s.roll << setw(22) << s.name
         << setw(18) << s.course << setw(8) << s.marks << '\n';
}

// ---------- Operations ----------
void addStudent() {
    Student s;
    s.roll = readInt("Roll number: ");
    if (findIndex(s.roll) != -1) {
        cout << "Is roll number ka student already exist karta hai!\n";
        return;
    }
    s.name = readLine("Name: ");
    s.course = readLine("Course: ");
    s.marks = readMarks("Marks (0-100): ");
    students.push_back(s);
    saveToFile();
    cout << "Student add ho gaya!\n";
}

void displayStudents() {
    if (students.empty()) {
        cout << "Koi record nahi mila.\n";
        return;
    }
    printHeader();
    for (const auto &s : students) printStudent(s);
}

void searchStudent() {
    int roll = readInt("Search karne ke liye roll number: ");
    int i = findIndex(roll);
    if (i == -1) {
        cout << "Student nahi mila.\n";
        return;
    }
    printHeader();
    printStudent(students[i]);
}

void updateStudent() {
    int roll = readInt("Update karne ke liye roll number: ");
    int i = findIndex(roll);
    if (i == -1) {
        cout << "Student nahi mila.\n";
        return;
    }
    cout << "Naya data daalo (purana: " << students[i].name << ", "
         << students[i].course << ", " << students[i].marks << ")\n";
    students[i].name = readLine("New name: ");
    students[i].course = readLine("New course: ");
    students[i].marks = readMarks("New marks (0-100): ");
    saveToFile();
    cout << "Record update ho gaya!\n";
}

void deleteStudent() {
    int roll = readInt("Delete karne ke liye roll number: ");
    int i = findIndex(roll);
    if (i == -1) {
        cout << "Student nahi mila.\n";
        return;
    }
    students.erase(students.begin() + i);
    saveToFile();
    cout << "Record delete ho gaya!\n";
}

// ---------- Menu ----------
void showMenu() {
    cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n"
         << "1. Add Student\n"
         << "2. Display All Students\n"
         << "3. Search Student\n"
         << "4. Update Student\n"
         << "5. Delete Student\n"
         << "6. Exit\n";
}

int main() {
    loadFromFile();
    int choice;
    do {
        showMenu();
        choice = readInt("Choice (1-6): ");
        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Bye! Data students.txt mein save hai.\n"; break;
            default: cout << "Galat choice, dobara try karo.\n";
        }
    } while (choice != 6);
    return 0;
}
