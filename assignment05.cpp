//============================================================================
// Name        : assignment5.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <vector>
using namespace std;

class node {
public:
    int key, value;
    node *next;
    node(int k, int v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class hashtable {
public:
    vector<node *> table;
    int table_size;

    hashtable(int size) {
        table_size = size;
        table.resize(size, nullptr);
    }

    int hashfunc(int key) {
        return key % table_size;
    }

    void insert(int key, int value) {
        int index = hashfunc(key);
        node *newnode = new node(key, value);

        if (!table[index]) {
            table[index] = newnode;
        } else {
            node *temp = table[index];
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newnode;
        }
        cout << "Inserted (" << key << ", " << value << ")" << endl;
    }

    bool search(int key) {
        int index = hashfunc(key);
        node *temp = table[index];

        while (temp) {
            if (temp->key == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void remove(int key,) {
        int index = hashfunc(key);
        node *temp = table[index], *prev = nullptr;

        while (temp) {
            if (temp->key == key) {
                if (!prev)
                    table[index] = temp->next;
                else
                    prev->next = temp->next;

                delete temp;
                cout << "Deleted (" << key << ", " << value << ")" << endl;
                return;
            }
            prev = temp;
            temp = temp->next;
        }
        cout << "Key-Value pair (" << key << ", " << value << ") not found!" << endl;
    }

    void display() {
        for (int i = 0; i < table_size; i++) {
            cout << "Bucket " << i << ": ";
            for (auto temp = table[i]; temp; temp = temp->next) {
                cout << "(" << temp->key << ", " << temp->value << ") -> ";
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    int size;
    cout << "Enter hash table size: ";
    cin >> size;
    hashtable ht(size);

    while (true) {
        cout << "\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
        int choice, key, value;
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key and value: ";
            cin >> key >> value;
            ht.insert(key, value);
            break;

        case 2:
            cout << "Enter key and value to search: ";
            cin >> key >> value;
            cout << (ht.search(key, value) ? "Key-Value pair found!" : "Not found!") << endl;
            break;

        case 3:
            cout << "Enter key and value to delete: ";
            cin >> key >> value;
            ht.remove(key, value);
            break;

        case 4:
            ht.display();
            break;

        case 5:
            cout << "Exiting program." << endl;
            return 0;

        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
}
