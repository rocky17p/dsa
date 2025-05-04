#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string key, meaning;
    Node* left;
    Node* right;
    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr) {}
};

class Dictionary {
public:
    Node* root;

    Dictionary() {
        root = nullptr;
    }

    Node* insert(Node* root, string k, string m) {
        if (root == nullptr) {
            return new Node(k, m);
        }

        if (k < root->key) {
            root->left = insert(root->left, k, m);
        } else if (k > root->key) {
            root->right = insert(root->right, k, m);
        } else {
            root->meaning = m;  // Update meaning if keyword already exists
        }

        return root;
    }

    bool search(Node* root, string k) {
        if (root == nullptr) {
            return false;
        }

        if (k == root->key) {
            return true;
        }

        if (k < root->key) {
            return search(root->left, k);
        } else {
            return search(root->right, k);
        }
    }

    Node* findMin(Node* root) {
        while (root && root->left != nullptr) {
            root = root->left;
        }
        return root;
    }

    Node* deleteNode(Node* root, string k) {
        if (root == nullptr) return root;

        if (k < root->key) {
            root->left = deleteNode(root->left, k);
        } else if (k > root->key) {
            root->right = deleteNode(root->right, k);
        } else {
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = findMin(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }

        return root;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->key << " : " << root->meaning << endl;
            inorder(root->right);
        }
    }

    void display(Node* root) {
        inorder(root);
    }
};

int main() {
    Dictionary dict;
    int choice;
    string keyword, meaning;

    while (true) {
        cout << "\n1. Add Keyword\n2. Search Keyword\n3. Delete Keyword\n4. Display All Keywords\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin >> meaning;
                dict.root = dict.insert(dict.root, keyword, meaning);
                break;

            case 2:
                cout << "Enter keyword to search: ";
                cin >> keyword;
                if (dict.search(dict.root, keyword)) {
                    cout << "Found: " << keyword << endl;
                } else {
                    cout << "Keyword not found!" << endl;
                }
                break;

            case 3:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                dict.root = dict.deleteNode(dict.root, keyword);
                cout << "Keyword deleted." << endl;
                break;

            case 4:
                cout << "Displaying all keywords:\n";
                dict.display(dict.root);
                break;

            case 5:
                cout << "Exiting program." << endl;
                return 0;

            default:
                cout << "Invalid choice! Try again." << endl;
        }
    }

    return 0;
}
