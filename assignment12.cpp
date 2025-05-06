#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

const char* FILE_NAME = "direct_access_file.dat";
const int MAX_RECORDS = 100;

class Record {
public:
    int id;
    char name[20];
    int age;

    Record() {
        id = -1;
        strcpy(name, "");
        age = 0;
    }
};

class RecordFile {
public:
    RecordFile() {
        fstream file(FILE_NAME, ios::out | ios::binary);
        Record empty;
        for (int i = 0; i < MAX_RECORDS; i++)
            file.write((char*)&empty, sizeof(empty));
        file.close();
    }

    void insertRecord(int index, int id, const char* name, int age) {
        if (index < 0 || index >= MAX_RECORDS) {
            cout << "Invalid index!\n";
            return;
        }

        fstream file(FILE_NAME, ios::in | ios::out | ios::binary);
        Record rec;

        file.seekg(index * sizeof(Record));
        file.read((char*)&rec, sizeof(rec));

        if (rec.id != -1) {
            cout << "Record already exists at index " << index << ".\n";
        } else {
            rec.id = id;
            strncpy(rec.name, name, sizeof(rec.name) - 1);
            rec.age = age;

            file.seekp(index * sizeof(Record));
            file.write((char*)&rec, sizeof(rec));
            cout << "Inserted successfully.\n";
        }

        file.close();
    }

    void deleteRecord(int index) {
        if (index < 0 || index >= MAX_RECORDS) {
            cout << "Invalid index!\n";
            return;
        }

        fstream file(FILE_NAME, ios::in | ios::out | ios::binary);
        Record empty;

        file.seekp(index * sizeof(Record));
        file.write((char*)&empty, sizeof(empty));
        cout << "Deleted successfully.\n";

        file.close();
    }

    void displayRecords() {
        fstream file(FILE_NAME, ios::in | ios::binary);
        Record rec;

        for (int i = 0; i < MAX_RECORDS; i++) {
            file.read((char*)&rec, sizeof(rec));
            cout << "Index " << i << ": ";
            if (rec.id == -1)
                cout << "[Empty]\n";
            else
                cout << "ID: " << rec.id << ", Name: " << rec.name << ", Age: " << rec.age << "\n";
        }

        file.close();
    }
};

int main() {
    RecordFile rf;
    int choice, index, id, age;
    char name[20];

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Insert Record\n";
        cout << "2. Delete Record\n";
        cout << "3. Display All Records\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter index (0-" << MAX_RECORDS - 1 << "): ";
                cin >> index;
                cout << "Enter ID, Name, Age: ";
                cin >> id >> name >> age;
                rf.insertRecord(index, id, name, age);
                break;

            case 2:
                cout << "Enter index to delete: ";
                cin >> index;
                rf.deleteRecord(index);
                break;

            case 3:
                rf.displayRecords();
                break;

            case 0:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice.\n";
        }
    }
}
