#include <iostream>
#include <vector>
#include <string>
using namespace std;

class hashtablewithrep {
public:
    vector<pair<string, string>> table;
    int size;

    hashtablewithrep(int size) {
        this->size = size;
        table.resize(size, {"", ""});
    }

    int hashfunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % size;
    }

    void insertrep(const string& key, const string& phonenumber) {
        int index = hashfunction(key);
        int startindex = index;

        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % size;
            if (index == startindex) return;
        }

        table[index] = {key, phonenumber};
    }

    void insert(const string& key, const string& phonenumber) {
        int index = hashfunction(key);
        int startindex = index;

        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % size;
            if (index == startindex) return;
        }

        if (table[index].first == "") {
            table[index] = {key, phonenumber};
        }
    }

    string search(const string& key) {
        int index = hashfunction(key);
        int startindex = index;

        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % size;
            if (index == startindex) return "Not Found";
        }

        if (table[index].first == key)
            return table[index].second;
        return "Not Found";
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << i << ": ";
            if (table[i].first != "") {
                cout << table[i].first << " - " << table[i].second << endl;
            } else {
                cout << "empty" << endl;
            }
        }
    }
};

int main() {
    int size;
    cout << "Enter the size of the hash table: ";
    cin >> size;

    hashtablewithrep ht(size);
    int choice;
    string name, number;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert with replacement\n";
        cout << "2. Insert without replacement\n";
        cout << "3. Search\n";
        cout << "4. Print Hash Table\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> number;
                ht.insertrep(name, number);
                break;

            case 2:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> number;
                ht.insert(name, number);
                break;

            case 3:
                cout << "Enter name to search: ";
                cin >> name;
                cout << "Phone Number: " << ht.search(name) << endl;
                break;

            case 4:
                cout << "Hash Table:\n";
                ht.print();
                break;

            case 5:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }

    } while (choice != 5);

    return 0;
}
