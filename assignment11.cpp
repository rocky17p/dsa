#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

class Student {
public:
    int roll, div;
    char name[50], address[100];

    Student() {
        roll = div = 0;
        strcpy(name, "");
        strcpy(address, "");
    }

    void getData() {
        cin.ignore();
        cout << "Enter name: ";
        cin.getline(name, 50);
        cout << "Enter roll no: ";
        cin >> roll;
        cout << "Enter div: ";
        cin >> div;
        cin.ignore();
        cout << "Enter address: ";
        cin.getline(address, 100);
    }

    void display() const {
        cout << "Name: " << name
             << "\nRoll: " << roll
             << "\nDiv: " << div
             << "\nAddress: " << address << "\n\n";
    }

    int getRoll() const {
        return roll;
    }
};

class StudentFile {
public:
    char filename[30];

    StudentFile() {
        cout << "Enter filename: ";
        cin >> filename;
        fstream file(filename, ios::out | ios::binary);
        if (file)
            cout << "File created.\n";
    }

    void addRecord() {
        fstream file(filename, ios::app | ios::binary);
        Student s;
        s.getData();
        file.write((char*)&s, sizeof(s));
        cout << "Record added.\n";
    }

    void displayAll() {
        fstream file(filename, ios::in | ios::binary);
        Student s;
        bool found = false;
        while (file.read((char*)&s, sizeof(s))) {
            s.display();
            found = true;
        }
        if (!found)
            cout << "No records found.\n";
    }

    void deleteRecord(int rollno) {
        fstream file(filename, ios::in | ios::binary);
        fstream temp("temp", ios::out | ios::binary);
        Student s;
        bool found = false;

        while (file.read((char*)&s, sizeof(s))) {
            if (s.getRoll() == rollno) {
                cout << "Deleting:\n";
                s.display();
                found = true;
            } else {
                temp.write((char*)&s, sizeof(s));
            }
        }

        file.close();
        temp.close();

        remove(filename);
        rename("temp", filename);

        if (!found)
            cout << "Roll number not found.\n";
    }

    void searchRecord(int rollno) {
        fstream file(filename, ios::in | ios::binary);
        Student s;
        while (file.read((char*)&s, sizeof(s))) {
            if (s.getRoll() == rollno) {
                cout << "Record Found:\n";
                s.display();
                return;
            }
        }
        cout << "No record found for roll number " << rollno << ".\n";
    }
};

int main() {
    StudentFile sf;
    int choice, rollno;

    do {
        cout << "\n===== MENU =====\n"
             << "1. Add Record\n"
             << "2. Display All Records\n"
             << "3. Delete Record\n"
             << "4. Search Record\n"
             << "0. Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: sf.addRecord(); break;
            case 2: sf.displayAll(); break;
            case 3:
                cout << "Enter roll number to delete: ";
                cin >> rollno;
                sf.deleteRecord(rollno);
                break;
            case 4:
                cout << "Enter roll number to search: ";
                cin >> rollno;
                sf.searchRecord(rollno);
                break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}
