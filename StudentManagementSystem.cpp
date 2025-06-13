#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;
const int MAX_STUDENTS = 9800;
struct Student {
    int id;
    char name[30];
    char faculty[30];
    char department[30];
    char dob[15];
    int yearOfJoining;
    bool isActive; // true = active, false = deactivated
};
Student students[MAX_STUDENTS] = {
    {1001, "Ali", "Engineering", "CS", "01-01-2000", 2020, true},
    {1002, "Amina", "Science", "Math", "02-02-2001", 2021, true},
    {1003, "Omar", "Medicine", "Pharmacy", "03-03-2002", 2022, true},
    {1004, "Zahra", "Law", "International", "04-04-2003", 2023, true},
    {1005, "Fadumo", "CS", "CS", "22-09-2003", 2023, true},
    {1006, "Zamzam", "IT", "IT", "04-04-2007", 2023, false},
    {1007, "Fardowsa", "CS", "Database Administrator", "04-04-2003", 2023, true},
    {1008, "Sumayo", "CS", "Database Administrator", "04-04-2003", 2023, true},
    {1009, "Najmo", "Medicine", "Pharmacy", "04-04-2003", 2024, false},
    {1010, "Abdi", "CS", "IT", "05-04-2003", 2021, false},
    {1011, "Ali", "Law", "International", "04-04-2000", 2021, true},
    {1012, "Ali", "Medicine", "Lab", "06-08-2005", 2023, false},
    {1013, "Nuur", "Medicine", "Lab", "07-09-2006", 2023, true},
    {1014, "Hassan", "CS", "Web development", "04-04-2001", 2020, true},
    {1015, "Ibrahim", "CS", "Web design", "06-06-2002", 2020, false},
    {1016, "Fadumo", "Law", "International", "04-04-2003", 2022, true},
    {1017, "Hani", "Medicine", "Nurse", "07-04-2005", 2025, true},
    {1018, "Nasiya", "Medicine", "Nurse", "04-05-2001", 2023, false},
    {1019, "Raqiya", "CS", "Database Analyses", "04-04-2003", 2023, true},
    {1020, "Ruweyda", "Medicine", "Lab", "04-09-2005", 2023, true}
};
int studentCount = 20;
int top = -1;

// File Handling
void saveToFile() {
    ofstream file("students.dat", ios::binary);
    if (!file) {
        cout << "Error saving data!\n";
        return;
    }
    file.write((char*)students, sizeof(students));
    file.write((char*)&studentCount, sizeof(studentCount));
    file.close();
}
void loadFromFile() {
    ifstream file("students.dat", ios::binary);
    if (!file) {
        cout << "No existing data found. Starting fresh.\n";
        return;
    }
    file.read((char*)students, sizeof(students));
    file.read((char*)&studentCount, sizeof(studentCount));
    file.close();
    top = studentCount - 1;
}

// Add new function to display inactive students
void displayInactiveStudents() {
    cout << "\n--- Inactive Students ---\n";
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (!students[i].isActive) {
            found = true;
            cout << "ID: " << students[i].id << "\n "
                 << "Name: " << students[i].name << "\n "
                 << "Faculty: " << students[i].faculty << "\n "
                 << "Department: " << students[i].department << "\n "
                 << "Date of Birth: " << students[i].dob << "\n "
                 << "Year of joining: " << students[i].yearOfJoining << endl
                 << " (" << (students[i].isActive ? "Active" : "Inactive") << ")\n";
        }
    }
    if (!found) cout << "No inactive students found.\n";
}

// Update displayAll() to show only active students
void displayAll() {
    cout << "\n--- Active Students ---\n";
    for (int i = 0; i < studentCount; i++) {
        if (students[i].isActive) {
            cout << "ID:" << students[i].id << "\n "
                 << "Name: " << students[i].name << "\n "
                 << "Faculty: " << students[i].faculty << "\n "
                 << "Department: " << students[i].department << "\n "
                 << "Date of Birth: " << students[i].dob << "\n "
                 << "Year of joining: " << students[i].yearOfJoining << endl
                 << " (" << (students[i].isActive ? "Active" : "Inactive") << ")\n";
        }
    }
}

bool isDuplicateID(int id) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) return true;
    }
    return false;
}

bool isValidDOB(const char dob[]) {
    int day, month, year;
    if (sscanf(dob, "%d-%d-%d", &day, &month, &year) != 3) return false;
    time_t t = time(NULL); // ? compatible with older compilers
    tm* now = localtime(&t);
    int currentYear = now->tm_year + 1900;
    return (year <= currentYear);
}

void registerStudents() {
    int range;
    cout << "\nHow many students to register? (Max: " << (MAX_STUDENTS - studentCount) << "): ";
    cin >> range;
    if (range < 1 || studentCount + range > MAX_STUDENTS) {
        cout << "Invalid number.\n";
        return;
    }
    for (int i = 0; i < range; i++) {
    	    if (cin.fail()) {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Invalid ID input. Registration cancelled.\n";
            return;
        }
        cout << "\n--- Student " << (studentCount + 1) << " ---\n"; 
		       
        int tempID;
        do {
            cout << "ID: ";
            cin >> tempID;
            if (isDuplicateID(tempID)) {
                cout << "This ID is already taken! Enter a unique ID.\n";
            }
        } while (isDuplicateID(tempID));
        students[studentCount].id = tempID;
        
        cout << "Name: "; cin >> students[studentCount].name;
        cout << "Faculty: "; cin >> students[studentCount].faculty;
        cout << "Department: "; cin >> students[studentCount].department;
        	do {
            cout << "DOB (dd-mm-yyyy): ";
            cin >> students[studentCount].dob;
            if (!isValidDOB(students[studentCount].dob)) {
                cout << "Invalid or future date! Please re-enter a valid DOB.\n";
            }
        } while (!isValidDOB(students[studentCount].dob));
        cout << "Year of Joining: "; cin >> students[studentCount].yearOfJoining;
        students[studentCount].isActive = true;
        studentCount++;
        top++;
    }
    saveToFile();
}

bool askQuestions() {
    string ans1, ans2, ans3;
    cout << "\nAnswer these 3 questions:\n";
    cout << "\nAnswer these 3 university-based questions:\n";
    cout << "1. What is the name of your faculty? "; cin >> ans1;
    cout << "2. What year did you join the university? "; cin >> ans2;
    cout << "3. What is the name of your department? "; cin >> ans3;
    return (ans1.length() >= 2 && ans2.length() >= 2 && ans3.length() >= 2);
}

void deactivateStudent() {
    int id;
    cout << "\nEnter ID to deactivate: ";
    cin >> id;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id && students[i].isActive) {
            if (askQuestions()) {
                students[i].isActive = false;
                cout << "Student deactivated.\n";
                saveToFile();
            } else {
                cout << "Security check failed.\n";
            }
            return;
        }
    }
    cout << "Student not found or already inactive.\n";
}

void activateStudent() {
    int id;
    cout << "\nEnter ID to activate: ";
    cin >> id;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id && !students[i].isActive) {
            if (askQuestions()) {
                students[i].isActive = true;
                cout << "Student activated.\n";
                saveToFile();
            } else {
                cout << "Security check failed.\n";
            }
            return;
        }
    }
    cout << "Student not found or already active.\n";
}

void searchByID() {
    int id;
    cout << "\nEnter ID to search: ";
    cin >> id;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << " Found:" <<"ID: " <<students[i].id <<"\n " <<"Name: " << students[i].name << "\n " <<"Faculty: " << students[i].faculty << "\n " <<"Department: " << students[i].department <<"\n " <<"Date of Birth: "<<students[i].dob <<"\n "<<"Year of joining: " <<students[i].yearOfJoining << endl;
            return;
        }
    }
    cout << "ID not found.\n";
}

void searchByName() {
    char name[30];
    cout << "\nEnter name to search: ";
    cin >> name;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].name, name) == 0) {
            cout << " Found:" <<"ID: " <<students[i].id <<"\n " <<"Name: " << students[i].name << "\n " <<"Faculty: " << students[i].faculty << "\n " <<"Department: " << students[i].department <<"\n " <<"Date of Birth: "<<students[i].dob <<"\n "<<"Year of joining: " <<students[i].yearOfJoining << endl;
            return;
        }
    }
    cout << "Name not found.\n";
}

void searchByYear() {
    int year;
    cout << "\nEnter year to search: ";
    cin >> year;
    bool found = false;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].yearOfJoining == year) {
            cout << students[i].name << " (ID: " << students[i].id << ")\n";
            found = true;
        }
    }
    if (!found) cout << "No students found.\n";
}

void updateStudent() {
    int id;
    cout << "\nEnter ID to update: ";
    cin >> id;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            cout << "New name: "; cin >> students[i].name;
            cout << "New faculty: "; cin >> students[i].faculty;
            cout << "New department: "; cin >> students[i].department;
            cout << "New DOB: "; cin >> students[i].dob;
            cout << "Updated successfully.\n";
            saveToFile();
            return;
        }
    }
    cout << "ID not found.\n";
}

void removeStudent() {
    int id;
    cout << "\nEnter ID to remove: ";
    cin >> id;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            top--;
            cout << "Removed successfully.\n";
            saveToFile();
            return;
        }
    }
    cout << "ID not found.\n";
}




void menu() {
    int choice;
    do {
        cout << "\n=========== MENU ===========\n";
        cout << "1. Register Students\n";
        cout << "2. Deactivate Student\n";
        cout << "3. Activate Student\n";
        cout << "4. Search by ID\n";
        cout << "5. Search by Name\n";
        cout << "6. Search by Year\n";
        cout << "7. Update Student\n";
        cout << "8. Remove Student\n";
        cout << "9. Display active Students\n";
        cout << "10. Display Inactive Students\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: registerStudents(); break;
            case 2: deactivateStudent(); break;
            case 3: activateStudent(); break;
            case 4: searchByID(); break;
            case 5: searchByName(); break;
            case 6: searchByYear(); break;
            case 7: updateStudent(); break;
            case 8: removeStudent(); break;
            case 9: displayAll(); break;
            case 10: displayInactiveStudents(); break;
            case 11: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 11);
}

int main() {
    loadFromFile();
    menu();
    return 0;
}