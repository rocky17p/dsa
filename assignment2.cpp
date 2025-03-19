//============================================================================
// Name        : assignment2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    node *left;
    node *right;
    int data;
    node(int v) {
        data = v;
        left = nullptr;
        right = nullptr;
    }
};

class bst {
public:
    node *root;
    bst() {
        root = nullptr;
    }

    void insert(int data) {
        node *newnode = new node(data);
        if (root == nullptr) {
            root = newnode;
            return;
        }
        node *current = root;
        while (true) {
            if (current->data > data) {
                if (current->left == nullptr) {
                    current->left = newnode;
                    return;
                }
                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = newnode;
                    return;
                }
                current = current->right;
            }
        }
    }

    void inorder(node *root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    bool search(node *root, int key) {
        if (root == nullptr) return false;
        if (root->data == key) return true;
        if (root->data > key) return search(root->left, key);
        return search(root->right, key);
    }

    int longest(node *root) {
        if (root == nullptr) return 0;
        int lmax = longest(root->left);
        int rmax = longest(root->right);
        return 1 + max(lmax, rmax);
    }

    int mini(node *root) {
        if (root == nullptr) return -1;
        while (root->left) {
            root = root->left;
        }
        return root->data;
    }

    int maxi(node *root) {
        if (root == nullptr) return -1;
        while (root->right) {
            root = root->right;
        }
        return root->data;
    }

    void mirror(node *root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }

    node* findMin(node* root) {
        while (root->left != nullptr) root = root->left;
        return root;
    }

    node* deleteNode(node* root, int key) {
        if (root == nullptr) return root;
        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr) {
                node* temp = root->right;
                delete root;
                return temp;
            } else if (root->right == nullptr) {
                node* temp = root->left;
                delete root;
                return temp;
            }
            node* temp = findMin(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }
};

int main() {
    bst tree;
    int choice, value;

    do {
        cout << "\nBinary Search Tree Operations:\n";
        cout << "1. Insert\n2. Inorder Traversal\n3. Search\n4. Find Minimum\n5. Find Maximum\n";
        cout << "6. Find Height\n7. Mirror Tree\n8. Delete Node\n9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;
            case 2:
                cout << "Inorder Traversal: ";
                tree.inorder(tree.root);
                cout << endl;
                break;
            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                cout << (tree.search(tree.root, value) ? "Found" : "Not Found") << endl;
                break;
            case 4:
                cout << "Minimum Value: " << tree.mini(tree.root) << endl;
                break;
            case 5:
                cout << "Maximum Value: " << tree.maxi(tree.root) << endl;
                break;
            case 6:
                cout << "Height of Tree: " << tree.longest(tree.root) << endl;
                break;
            case 7:
                tree.mirror(tree.root);
                cout << "Tree mirrored.\n";
                break;
            case 8:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.root = tree.deleteNode(tree.root, value);
                break;
            case 9:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
