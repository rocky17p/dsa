#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;

class Student {
public:
    string rollNo, name, division, address;

    Student() {}
    Student(string r, string n, string d, string a)
        : rollNo(r), name(n), division(d), address(a) {}

    string serialize() const {
        return rollNo + "-" + name + " " + division + " " + address;
    }

    static Student deserialize(const string &line) {
        stringstream ss(line);
        string r, n, d, a;
        getline(ss, r, '-');
        getline(ss, n, ' ');
        getline(ss, d, ' ');
        getline(ss, a);
        return Student(r, n, d, a);
    }

    void display() const {
        cout << "Roll No: " << rollNo << "\nName: " << name
             << "\nDivision: " << division << "\nAddress: " << address << endl;
    }
};

void addStudent(const string &filename) {
    ofstream file(filename, ios::app);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    string r, n, d, a;
    cout << "Enter Roll No: "; cin >> r;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, n);
    cout << "Enter Division: "; getline(cin, d);
    cout << "Enter Address: "; getline(cin, a);

    Student s(r, n, d, a);
    file << s.serialize() << endl;
    cout << "Student added.\n";
}

void displayStudent(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    string roll, line;
    cout << "Enter Roll No to search: "; cin >> roll;
    bool found = false;

    while (getline(file, line)) {
        Student s = Student::deserialize(line);
        if (s.rollNo == roll) {
            cout << "\nStudent found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student not found.\n";
}

void deleteStudent(const string &filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Error opening file.\n";
        return;
    }

    string roll, line;
    cout << "Enter Roll No to delete: "; cin >> roll;
    vector<string> records;
    bool found = false;

    while (getline(file, line)) {
        Student s = Student::deserialize(line);
        if (s.rollNo != roll)
            records.push_back(line);
        else
            found = true;
    }
    file.close();

    if (found) {
        ofstream outFile(filename, ios::trunc);
        for (const auto &rec : records)
            outFile << rec << endl;
        cout << "Student deleted.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void menu() {
    string file = "students.txt";
    int ch;
    while (true) {
        cout << "\n1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: addStudent(file); break;
            case 2: displayStudent(file); break;
            case 3: deleteStudent(file); break;
            case 4: return;
            default: cout << "Invalid choice.\n";
        }
    }
}

int main() {
    menu();
    return 0;
}
