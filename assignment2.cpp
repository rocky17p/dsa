#include <iostream>
#include <bits/stdc++.h>
using namespace std;

class node {
public:
    int data;
    node *left;
    node *right;
    node(int d) {
        data = d;
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

    void insert(int d) {
        if (root == nullptr) {
            node *newnode = new node(d);
            root = newnode;
        }
        else {
            node *current = root;
            while (true) {
                if (current->data > d) {
                    if (current->left == nullptr) {
                        node *newnode = new node(d);
                        current->left = newnode;
                        break;
                    }
                    else {
                        current = current->left;
                    }
                }
                else {
                    if (current->right == nullptr) {
                        node *newnode = new node(d);
                        current->right = newnode;
                        break;
                    }
                    else {
                        current = current->right;
                    }
                }
            }
        }
    }

    void inorder(node *root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    int nodes(node* root) {
        if (root == nullptr) return 0;
        int leftHeight = nodes(root->left);
        int rightHeight = nodes(root->right);
        return 1 + max(leftHeight, rightHeight);
    }

    int minimum(node *root) {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return -1;
        }
        if (root->left == nullptr) {
            return root->data;
        }
        return minimum(root->left);
    }

    int maximum(node *root) {
        if (root == nullptr) {
            cout << "Tree is empty." << endl;
            return -1;
        }
        if (root->right == nullptr) {
            return root->data;
        }
        return maximum(root->right);
    }

    void mirror(node *root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }

    int search(node *root, int target) {
        if (root == nullptr) return -1;
        if (root->data == target) return root->data;
        if (root->data > target) return search(root->left, target);
        return search(root->right, target);
    }

    void menu() {
        int choice, data, target,result;
        while (true) {
            cout << "\nMenu: \n";
            cout << "1. Insert Node\n";
            cout << "2. Inorder Traversal\n";
            cout << "3. Calculate Height\n";
            cout << "4. Minimum Value\n";
            cout << "5. Maximum Value\n";
            cout << "6. Search\n";
            cout << "7. Mirror the Tree\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                cout << "Enter the data to insert: ";
                cin >> data;
                insert(data);
                break;
            case 2:
                cout << "Inorder Traversal: ";
                inorder(root);
                cout << endl;
                break;
            case 3:
                cout << "Number of nodes in longest path: " << nodes(root) << endl;
                break;
            case 4:
                cout << "Minimum value in tree is: " << minimum(root) << endl;
                break;
            case 5:
                cout << "Maximum value in tree is: " << maximum(root) << endl;
                break;
            case 6:
                cout << "Enter the value to search for: ";
                cin >> target;
                result = search(root, target);
                if (result != -1) {
                    cout << "Found node with value: " << result << endl;
                } else {
                    cout << "Node not found in the tree." << endl;
                }
                break;
            case 7:
                mirror(root);
                cout << "Tree mirrored successfully." << endl;
                break;
            case 8:
                cout << "Exiting the program." << endl;
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
            }
        }
    }
};

int main() {
    bst tree;
    tree.menu();
    return 0;
}