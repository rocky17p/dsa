#include <iostream>
#include <string>
using namespace std;

class node {
public:
    string keyword;
    node* left;
    node* right;
    node(string k) : keyword(k), left(nullptr), right(nullptr) {}
};

class BST {
public:
    node* root;
    BST() : root(nullptr) {}

    node* insertNode(node* root, string key) {
        if (root == nullptr) {
            return new node(key);
        }
        if (key < root->keyword) {
            root->left = insertNode(root->left, key);
        } else if (key > root->keyword) {
            root->right = insertNode(root->right, key);
        }
        return root;
    }

    void insert(string key) {
        root = insertNode(root, key);
    }

    node* inorderSuccessor(node* node) {
        node* current = node;
        while (current && current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    node* deleteNode(node* root, string key) {
        if (root == nullptr) return root;

        if (key < root->keyword) {
            root->left = deleteNode(root->left, key);
        } else if (key > root->keyword) {
            root->right = deleteNode(root->right, key);
        } else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            } else if (root->left == nullptr) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                node* temp = root->left;
                delete root;
                return temp;
            } else {
                node* temp = inorderSuccessor(root->right);
                root->keyword = temp->keyword;
                root->right = deleteNode(root->right, temp->keyword);
            }
        }
        return root;
    }

    void deleteKeyword(string key) {
        root = deleteNode(root, key);
    }

    void inorder(node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->keyword << " ";
        inorder(root->right);
    }

    void display() {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST tree;
    int choice;
    string keyword;

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Insert Keyword\n";
        cout << "2. Delete Keyword\n";
        cout << "3. Display Keywords\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the keyword to insert: ";
            cin >> keyword;
            tree.insert(keyword);
            break;

        case 2:
            cout << "Enter the keyword to delete: ";
            cin >> keyword;
            tree.deleteKeyword(keyword);
            break;

        case 3:
            cout << "Keywords in the dictionary (in-order traversal):\n";
            tree.display();
            break;

        case 4:
            cout << "Exiting program.\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
