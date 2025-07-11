#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <limits>

using namespace std;

// Student structure to store student information
struct Student {
    int rollNumber;
    string name;
    string department;
    int age;
    string email;
    string phone;
    
    // Constructor
    Student(int roll = 0, string n = "", string dept = "", int a = 0, string e = "", string p = "") 
        : rollNumber(roll), name(n), department(dept), age(a), email(e), phone(p) {}
};

// Student Management System class
class StudentManagementSystem {
private:
    vector<Student> students;
    string filename = "students.csv";
    
    // Helper function to find student by roll number
    int findStudentByRoll(int rollNumber) {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].rollNumber == rollNumber) {
                return static_cast<int>(i);
            }
        }
        return -1; // Not found
    }
    
    // Helper function to find students by name (partial match)
    vector<int> findStudentsByName(const string& name) {
        vector<int> indices;
        string searchName = name;
        transform(searchName.begin(), searchName.end(), searchName.begin(), ::tolower);
        
        for (size_t i = 0; i < students.size(); i++) {
            string studentName = students[i].name;
            transform(studentName.begin(), studentName.end(), studentName.begin(), ::tolower);
            
            if (studentName.find(searchName) != string::npos) {
                indices.push_back(static_cast<int>(i));
            }
        }
        return indices;
    }
    
    // Helper function to get student input
    Student getStudentInput() {
        Student student;
        
        cout << "\nEnter Student Details:\n";
        cout << "Roll Number: ";
        cin >> student.rollNumber;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Name: ";
        getline(cin, student.name);
        
        cout << "Department: ";
        getline(cin, student.department);
        
        cout << "Age: ";
        cin >> student.age;
        
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        
        cout << "Email: ";
        getline(cin, student.email);
        
        cout << "Phone: ";
        getline(cin, student.phone);
        
        return student;
    }
    
    // Helper function to display a single student
    void displayStudent(const Student& student) {
        cout << "\n" << string(80, '-') << "\n";
        cout << "Roll Number: " << student.rollNumber << "\n";
        cout << "Name: " << student.name << "\n";
        cout << "Department: " << student.department << "\n";
        cout << "Age: " << student.age << "\n";
        cout << "Email: " << student.email << "\n";
        cout << "Phone: " << student.phone << "\n";
        cout << string(80, '-') << "\n";
    }
    
public:
    // Constructor - load existing data
    StudentManagementSystem() {
        loadFromFile();
    }
    
    // Destructor - save data
    ~StudentManagementSystem() {
        saveToFile();
    }
    
    // Add a new student
    void addStudent() {
        cout << "\n=== ADD NEW STUDENT ===\n";
        
        Student newStudent = getStudentInput();
        
        // Check if roll number already exists
        if (findStudentByRoll(newStudent.rollNumber) != -1) {
            cout << "\nError: Student with Roll Number " << newStudent.rollNumber << " already exists!\n";
            return;
        }
        
        students.push_back(newStudent);
        cout << "\nStudent added successfully!\n";
        saveToFile();
    }
    
    // Update an existing student
    void updateStudent() {
        cout << "\n=== UPDATE STUDENT ===\n";
        
        int rollNumber;
        cout << "Enter Roll Number to update: ";
        cin >> rollNumber;
        
        int index = findStudentByRoll(rollNumber);
        if (index == -1) {
            cout << "\nError: Student with Roll Number " << rollNumber << " not found!\n";
            return;
        }
        
        cout << "\nCurrent student details:";
        displayStudent(students[index]);
        
        cout << "\nEnter new details:\n";
        Student updatedStudent = getStudentInput();
        
        // Check if new roll number conflicts with existing students (excluding current)
        if (updatedStudent.rollNumber != rollNumber) {
            int conflictIndex = findStudentByRoll(updatedStudent.rollNumber);
            if (conflictIndex != -1 && conflictIndex != index) {
                cout << "\nError: Student with Roll Number " << updatedStudent.rollNumber << " already exists!\n";
                return;
            }
        }
        
        students[index] = updatedStudent;
        cout << "\nStudent updated successfully!\n";
        saveToFile();
    }
    
    // Delete a student
    void deleteStudent() {
        cout << "\n=== DELETE STUDENT ===\n";
        
        int rollNumber;
        cout << "Enter Roll Number to delete: ";
        cin >> rollNumber;
        
        int index = findStudentByRoll(rollNumber);
        if (index == -1) {
            cout << "\nError: Student with Roll Number " << rollNumber << " not found!\n";
            return;
        }
        
        cout << "\nStudent to be deleted:";
        displayStudent(students[index]);
        
        char confirm;
        cout << "\nAre you sure you want to delete this student? (y/n): ";
        cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            students.erase(students.begin() + index);
            cout << "\nStudent deleted successfully!\n";
            saveToFile();
        } else {
            cout << "\nDeletion cancelled.\n";
        }
    }
    
    // Search student by roll number
    void searchByRollNumber() {
        cout << "\n=== SEARCH BY ROLL NUMBER ===\n";
        
        int rollNumber;
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        
        int index = findStudentByRoll(rollNumber);
        if (index == -1) {
            cout << "\nStudent with Roll Number " << rollNumber << " not found!\n";
            return;
        }
        
        cout << "\nStudent found:";
        displayStudent(students[index]);
    }
    
    // Search students by name
    void searchByName() {
        cout << "\n=== SEARCH BY NAME ===\n";
        
        string name;
        cout << "Enter name (or partial name): ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, name);
        
        vector<int> indices = findStudentsByName(name);
        
        if (indices.empty()) {
            cout << "\nNo students found with name containing '" << name << "'\n";
            return;
        }
        
        cout << "\nFound " << indices.size() << " student(s):\n";
        for (int index : indices) {
            displayStudent(students[index]);
        }
    }
    
    // Display all students
    void displayAllStudents() {
        cout << "\n=== ALL STUDENTS ===\n";
        
        if (students.empty()) {
            cout << "\nNo students in the database.\n";
            return;
        }
        
        cout << "\nTotal students: " << students.size() << "\n";
        cout << string(80, '=') << "\n";
        cout << setw(12) << "Roll Number" << " | ";
        cout << setw(20) << "Name" << " | ";
        cout << setw(15) << "Department" << " | ";
        cout << setw(8) << "Age" << " | ";
        cout << setw(20) << "Email" << " | ";
        cout << setw(15) << "Phone" << "\n";
        cout << string(80, '=') << "\n";
        
        for (const Student& student : students) {
            cout << setw(12) << student.rollNumber << " | ";
            cout << setw(20) << student.name << " | ";
            cout << setw(15) << student.department << " | ";
            cout << setw(8) << student.age << " | ";
            cout << setw(20) << student.email << " | ";
            cout << setw(15) << student.phone << "\n";
        }
        cout << string(80, '=') << "\n";
    }
    
    // Save data to CSV file
    void saveToFile() {
        ofstream file(filename);
        if (!file.is_open()) {
            cout << "\nError: Could not open file for writing!\n";
            return;
        }
        
        // Write header
        file << "RollNumber,Name,Department,Age,Email,Phone\n";
        
        // Write student data
        for (const Student& student : students) {
            file << student.rollNumber << ","
                 << student.name << ","
                 << student.department << ","
                 << student.age << ","
                 << student.email << ","
                 << student.phone << "\n";
        }
        
        file.close();
    }
    
    // Load data from CSV file
    void loadFromFile() {
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "\nNo existing data file found. Starting with empty database.\n";
            return;
        }
        
        string line;
        // Skip header
        getline(file, line);
        
        while (getline(file, line)) {
            if (line.empty()) continue;
            
            Student student;
            size_t pos = 0;
            string token;
            int field = 0;
            
            while ((pos = line.find(',')) != string::npos) {
                token = line.substr(0, pos);
                line.erase(0, pos + 1);
                
                switch (field) {
                    case 0: student.rollNumber = stoi(token); break;
                    case 1: student.name = token; break;
                    case 2: student.department = token; break;
                    case 3: student.age = stoi(token); break;
                    case 4: student.email = token; break;
                }
                field++;
            }
            // Last field (phone)
            if (!line.empty()) {
                student.phone = line;
            }
            
            students.push_back(student);
        }
        
        file.close();
        cout << "\nLoaded " << students.size() << " students from database.\n";
    }
    
    // Display menu
    void displayMenu() {
        cout << "\n" << string(50, '=') << "\n";
        cout << "    STUDENT MANAGEMENT SYSTEM\n";
        cout << string(50, '=') << "\n";
        cout << "1. Add New Student\n";
        cout << "2. Update Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Search by Roll Number\n";
        cout << "5. Search by Name\n";
        cout << "6. Display All Students\n";
        cout << "7. Exit\n";
        cout << string(50, '=') << "\n";
        cout << "Enter your choice (1-7): ";
    }
    
    // Run the main program loop
    void run() {
        int choice;
        
        while (true) {
            displayMenu();
            cin >> choice;
            
            switch (choice) {
                case 1:
                    addStudent();
                    break;
                case 2:
                    updateStudent();
                    break;
                case 3:
                    deleteStudent();
                    break;
                case 4:
                    searchByRollNumber();
                    break;
                case 5:
                    searchByName();
                    break;
                case 6:
                    displayAllStudents();
                    break;
                case 7:
                    cout << "\nThank you for using Student Management System!\n";
                    cout << "Data saved successfully.\n";
                    return;
                default:
                    cout << "\nInvalid choice! Please enter a number between 1-7.\n";
            }
            
            cout << "\nPress Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }
};

int main() {
    cout << "Welcome to Student Management System!\n";
    
    StudentManagementSystem sms;
    sms.run();
    
    return 0;
} 