#include <iostream>
#include <vector>
#include <string>
using namespace std;

class HashTable {
public:
    vector<pair<string, string>> table;
    int size;

    HashTable(int size) {
        this->size = size;
        table.resize(size, {"", ""});
    }

    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch;
        }
        return hash % size;
    }

    void insertWithReplacement(const string& key, const string& phoneNumber) {
        int index = hashFunction(key);
        int startIndex = index;
        
        if (table[index].first == "") {
            table[index] = {key, phoneNumber};
            return;
        }

        int existingHash = hashFunction(table[index].first);
        if (existingHash != index) {
            swap(table[index], make_pair(key, phoneNumber));
            key = table[index].first;
            phoneNumber = table[index].second;
        }

        index = (index + 1) % size;
        while (table[index].first != "") {
            index = (index + 1) % size;
            if (index == startIndex) return;
        }
        table[index] = {key, phoneNumber};
    }

    void insertWithoutReplacement(const string& key, const string& phoneNumber) {
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % size;
            if (index == startIndex) return;
        }
        table[index] = {key, phoneNumber};
    }

    string search(const string& key, int &comparisons) {
        int index = hashFunction(key);
        int startIndex = index;
        comparisons = 0;

        while (table[index].first != "" && table[index].first != key) {
            index = (index + 1) % size;
            comparisons++;
            if (index == startIndex) return "Not Found";
        }

        comparisons++;
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

    HashTable ht(size);
    int choice;
    string name, number;
    int comparisons = 0;

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
                ht.insertWithReplacement(name, number);
                break;

            case 2:
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> number;
                ht.insertWithoutReplacement(name, number);
                break;

            case 3:
                cout << "Enter name to search: ";
                cin >> name;
                cout << "Phone Number: " << ht.search(name, comparisons) << endl;
                cout << "Comparisons made: " << comparisons << endl;
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
