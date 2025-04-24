#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

const int RECORD_SIZE = 100;
const string FILENAME = "data.daf";

string formatRecord(const string& data) {
    string result = data;
    result.resize(RECORD_SIZE, ' ');
    return result;
}

void writeRecords() {
    fstream daf(FILENAME, ios::out | ios::binary);
    if (!daf) {
        cerr << "Error creating file.\n";
        return;
    }

    string records[] = {
        "01, abc, 25, Engineer",
        "02, bcd, 30, Doctor",
        "03, cde, 22, Teacher",
        "04, def, 28, Designer"
    };

    for (auto& rec : records) {
        string padded = formatRecord(rec);
        daf.write(padded.c_str(), RECORD_SIZE);
    }

    daf.close();
    cout << "Records written successfully.\n";
}

void readRecord(int index) {
    fstream daf(FILENAME, ios::in | ios::binary);
    if (!daf) {
        cerr << "File not found.\n";
        return;
    }

    daf.seekg(index * RECORD_SIZE, ios::beg);
    char buffer[RECORD_SIZE];
    daf.read(buffer, RECORD_SIZE);
    daf.close();

    string record(buffer, RECORD_SIZE);

    if (record[0] == '#' || record.find_first_not_of(' ') == string::npos) {
        cout << "Record at index " << index << " is deleted or empty.\n";
    } else {
        cout << "Record at index " << index << ": " << record << "\n";
    }
}

void logicalDelete(int index) {
    fstream daf(FILENAME, ios::in | ios::out | ios::binary);
    if (!daf) {
        cerr << "File not found.\n";
        return;
    }

    daf.seekp(index * RECORD_SIZE, ios::beg);
    string deleted = "#";
    deleted.resize(RECORD_SIZE, ' ');
    daf.write(deleted.c_str(), RECORD_SIZE);
    daf.close();

    cout << "Logically deleted record at index " << index << ".\n";
}

void actualDelete(int index) {
    fstream daf(FILENAME, ios::in | ios::binary);
    if (!daf) {
        cerr << "File not found.\n";
        return;
    }

    vector<string> records;
    char buffer[RECORD_SIZE];
    while (daf.read(buffer, RECORD_SIZE)) {
        records.push_back(string(buffer, RECORD_SIZE));
    }
    daf.close();

    if (index < 0 || index >= records.size()) {
        cout << "Invalid index for deletion.\n";
        return;
    }

    records.erase(records.begin() + index);

    daf.open(FILENAME, ios::out | ios::binary | ios::trunc);
    for (auto& rec : records) {
        daf.write(rec.c_str(), RECORD_SIZE);
    }
    daf.close();

    cout << "Physically deleted record at index " << index << ".\n";
}

void displayAll() {
    fstream daf(FILENAME, ios::in | ios::binary);
    if (!daf) {
        cerr << "File not found.\n";
        return;
    }

    char buffer[RECORD_SIZE];
    int index = 0;

    while (daf.read(buffer, RECORD_SIZE)) {
        string record(buffer, RECORD_SIZE);
        if (record[0] != '#')
            cout << "Index " << index << ": " << record << "\n";
        else
            cout << "Index " << index << ": [Deleted]\n";
        ++index;
    }

    daf.close();
}

int main() {
    int choice, index;

    while (true) {
        cout << "\n----- Direct Access File Menu -----\n";
        cout << "1. Write Sample Records\n";
        cout << "2. Read Record\n";
        cout << "3. Logical Delete\n";
        cout << "4. Actual Delete\n";
        cout << "5. Display All Records\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                writeRecords();
                break;
            case 2:
                cout << "Enter index to read: ";
                cin >> index;
                readRecord(index);
                break;
            case 3:
                cout << "Enter index to logically delete: ";
                cin >> index;
                logicalDelete(index);
                break;
            case 4:
                cout << "Enter index to physically delete: ";
                cin >> index;
                actualDelete(index);
                break;
            case 5:
                displayAll();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
