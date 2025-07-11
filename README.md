# Student Management System

A comprehensive CLI-based Student Management System written in C++ that allows you to add, update, delete, and search student records with persistent data storage.

## Features

### Core Functionality
- ✅ **Add New Student** - Add students with roll number, name, department, age, email, and phone
- ✅ **Update Student** - Modify existing student records
- ✅ **Delete Student** - Remove students with confirmation prompt
- ✅ **Search by Roll Number** - Find students by their unique roll number
- ✅ **Search by Name** - Find students by name (supports partial matching)
- ✅ **Display All Students** - View all students in a formatted table

### Technical Features
- ✅ **Struct-based Student Model** - Clean data structure for student information
- ✅ **Vector Storage** - Dynamic memory management for student records
- ✅ **CSV File Storage** - Persistent data storage in CSV format
- ✅ **Menu-driven Interface** - User-friendly switch-case menu system
- ✅ **Input Validation** - Prevents duplicate roll numbers and validates input
- ✅ **Case-insensitive Search** - Search by name works regardless of case

## File Structure

```
Student Management System/
├── student_management.cpp    # Main source code
├── Makefile                  # Build configuration
├── README.md                 # This file
└── students.csv              # Data file (created automatically)
```

## Compilation and Installation

### Prerequisites
- GCC compiler (g++)
- Make utility
- Linux/Unix environment (or WSL on Windows)

### Quick Start

1. **Clone or download the project files**

2. **Compile the program:**
   ```bash
   make
   ```
   or manually:
   ```bash
   g++ -std=c++11 -Wall -Wextra -O2 student_management.cpp -o student_management
   ```

3. **Run the program:**
   ```bash
   ./student_management
   ```
   or use make:
   ```bash
   make run
   ```

### Additional Make Commands

- `make clean` - Remove build files
- `make install` - Install to system (requires sudo)
- `make uninstall` - Remove from system
- `make help` - Show available commands

## Usage Guide

### Main Menu
The program presents a clean menu interface:

```
==================================================
    STUDENT MANAGEMENT SYSTEM
==================================================
1. Add New Student
2. Update Student
3. Delete Student
4. Search by Roll Number
5. Search by Name
6. Display All Students
7. Exit
==================================================
Enter your choice (1-7):
```

### Adding a Student
1. Select option `1` from the main menu
2. Enter the following details:
   - **Roll Number**: Unique identifier (integer)
   - **Name**: Full name of the student
   - **Department**: Academic department
   - **Age**: Student's age
   - **Email**: Email address
   - **Phone**: Contact number

**Note**: Roll numbers must be unique. The system will prevent duplicate entries.

### Updating a Student
1. Select option `2` from the main menu
2. Enter the roll number of the student to update
3. View current details
4. Enter new details for all fields
5. The system validates that the new roll number doesn't conflict with existing students

### Deleting a Student
1. Select option `3` from the main menu
2. Enter the roll number of the student to delete
3. Confirm the deletion by entering 'y' or 'Y'
4. The student record is permanently removed

### Searching Students
- **By Roll Number** (Option 4): Enter exact roll number for precise search
- **By Name** (Option 5): Enter partial name for flexible search (case-insensitive)

### Viewing All Students
Select option `6` to display all students in a formatted table showing:
- Roll Number
- Name
- Department
- Age
- Email
- Phone

## Data Storage

### CSV Format
Student data is stored in `students.csv` with the following structure:
```csv
RollNumber,Name,Department,Age,Email,Phone
1001,John Doe,Computer Science,20,john@email.com,1234567890
1002,Jane Smith,Mathematics,19,jane@email.com,0987654321
```

### Automatic Data Management
- Data is automatically loaded when the program starts
- Changes are automatically saved after each operation
- Data persists between program sessions

## Error Handling

The system includes comprehensive error handling:
- **Duplicate Roll Numbers**: Prevents adding students with existing roll numbers
- **Invalid Roll Numbers**: Handles cases where roll numbers don't exist
- **File I/O Errors**: Gracefully handles file read/write issues
- **Input Validation**: Manages invalid user input

## Example Session

```
Welcome to Student Management System!

No existing data file found. Starting with empty database.

==================================================
    STUDENT MANAGEMENT SYSTEM
==================================================
1. Add New Student
2. Update Student
3. Delete Student
4. Search by Roll Number
5. Search by Name
6. Display All Students
7. Exit
==================================================
Enter your choice (1-7): 1

=== ADD NEW STUDENT ===

Enter Student Details:
Roll Number: 1001
Name: John Doe
Department: Computer Science
Age: 20
Email: john@email.com
Phone: 1234567890

Student added successfully!

Press Enter to continue...
```

## Technical Details

### Data Structure
```cpp
struct Student {
    int rollNumber;
    string name;
    string department;
    int age;
    string email;
    string phone;
};
```

### Key Classes
- **StudentManagementSystem**: Main class handling all operations
- **Student**: Data structure for student information

### Memory Management
- Uses `std::vector<Student>` for dynamic storage
- Automatic memory management with RAII principles
- Efficient search algorithms for roll number and name lookups

## Contributing

Feel free to enhance this system with additional features such as:
- Sorting capabilities
- Advanced search filters
- Data export options
- Backup and restore functionality
- GUI interface

## License

This project is open source and available under the MIT License.

## Support

For issues or questions, please check the code comments or create an issue in the repository. 
