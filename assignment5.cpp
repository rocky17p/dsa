#include <iostream>
#include <vector>
using namespace std;

class Node
{
public:
    int key, value;
    Node *next;
    Node(int k, int v) : key(k), value(v), next(nullptr) {}
};

class HashTable
{
private:
    int TABLE_SIZE;
    vector<Node *> table;

    int hashFunc(int key)
    {
        return key % TABLE_SIZE;
    }

public:
    HashTable(int size) : TABLE_SIZE(size), table(size, nullptr) {}

    void insert(int key, int value)
    {
        int idx = hashFunc(key);
        Node *newNode = new Node(key, value);

        if (!table[idx])
        {
            table[idx] = newNode;
        }
        else
        {
            Node *temp = table[idx];
            while (temp->next)
                temp = temp->next;
            temp->next = newNode;
        }
        cout << "Inserted (" << key << ", " << value << ")" << endl;
    }

    bool search(int key, int value)
{
    Node *temp = table[hashFunc(key)];

    while (temp)
    {
        if (temp->key == key && temp->value == value)
            return true;
        temp = temp->next;
    }
    return false;
}


    void remove(int key)
    {
        int idx = hashFunc(key);
        Node *temp = table[idx], *prev = nullptr;

        while (temp && temp->key != key)
        {
            prev = temp;
            temp = temp->next;
        }

        if (!temp)
        {
            cout << "Key not found!" << endl;
            return;
        }

        if (!prev)
            table[idx] = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout << "Key " << key << " deleted." << endl;
    }

    void display()
    {
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            cout << "Bucket " << i << ": ";
            for (Node *temp = table[i]; temp; temp = temp->next)
                cout << "(" << temp->key << ", " << temp->value << ") -> ";
            cout << "NULL\n";
        }
    }
};

int main()
{
    int size, choice, key, value;
    cout << "Enter hash table size: ";
    cin >> size;
    HashTable ht(size);

    while (true)
    {
        cout << "\n1. Insert\n2. Search\n3. Delete\n4. Display\n5. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter key and value: ";
            cin >> key >> value;
            ht.insert(key, value);
            break;
        case 2:
            cout << "Enter key to search: ";
            cin >> key;
            value = ht.search(key);
            cout << (value != -1 ? "Value: " + to_string(value) : "Key not found!") << endl;
            break;
        case 3:
            cout << "Enter key to delete: ";
            cin >> key;
            ht.remove(key);
            break;
        case 4:
            ht.display();
            break;
        case 5:
            return 0;
        default:
            cout << "Invalid choice!" << endl;
        }
    }
}
