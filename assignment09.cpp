#include <iostream>
using namespace std;

class Node {
public:
    string key;     // keyword
    string value;   // meaning
    int height;
    Node* left;
    Node* right;

    Node(string k, string v) {
        key = k;
        value = v;
        height = 1;
        left = nullptr;
        right = nullptr;
    }
};

class AVLTree {
    Node* root = nullptr;

    int getHeight(Node* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    void updateHeight(Node* node) {
        int lh = getHeight(node->left);
        int rh = getHeight(node->right);
        node->height = max(lh, rh) + 1;
    }

    int getBalanceFactor(Node* node) {
        if (node == nullptr) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* leftLeftRotation(Node* node) {
        Node* child = node->left;
        Node* transfer = child->right;

        child->right = node;
        node->left = transfer;

        updateHeight(node);
        updateHeight(child);

        return child;
    }

    Node* rightRightRotation(Node* node) {
        Node* child = node->right;
        Node* transfer = child->left;

        child->left = node;
        node->right = transfer;

        updateHeight(node);
        updateHeight(child);

        return child;
    }

    Node* leftRightRotation(Node* node) {
        node->left = rightRightRotation(node->left);
        return leftLeftRotation(node);
    }

    Node* rightLeftRotation(Node* node) {
        node->right = leftLeftRotation(node->right);
        return rightRightRotation(node);
    }

    Node* balance(Node* node) {
        updateHeight(node);
        int bf = getBalanceFactor(node);

        if (bf > 1) {
            if (getBalanceFactor(node->left) < 0) {
                node = leftRightRotation(node);
            } else {
                node = leftLeftRotation(node);
            }
        } else if (bf < -1) {
            if (getBalanceFactor(node->right) > 0) {
                node = rightLeftRotation(node);
            } else {
                node = rightRightRotation(node);
            }
        }
        return node;
    }

    Node* insertHelper(Node* node, string key, string value) {
        if (node == nullptr) {
            return new Node(key, value);
        }

        if (key < node->key) {
            node->left = insertHelper(node->left, key, value);
        } else if (key > node->key) {
            node->right = insertHelper(node->right, key, value);
        } else {
            node->value = value; // update value if key exists
            return node;
        }

        return balance(node);
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->key << " : " << node->value << endl;
        inorderTraversal(node->right);
    }

    void reverseInorderTraversal(Node* node) {
        if (node == nullptr) return;
        reverseInorderTraversal(node->right);
        cout << node->key << " : " << node->value << endl;
        reverseInorderTraversal(node->left);
    }

public:
    void insert(string key, string value) {
        root = insertHelper(root, key, value);
    }

    void displayAscending() {
        cout << "\nAscending Order:\n";
        inorderTraversal(root);
    }

    void displayDescending() {
        cout << "\nDescending Order:\n";
        reverseInorderTraversal(root);
    }

    int getMaxComparisons() {
        return getHeight(root);
    }
};

int main() {
    AVLTree dict;
    int choice;
    string key, value;

    do {
        cout << "\n--- Dictionary Menu ---\n";
        cout << "1. Insert new word\n";
        cout << "2. Display dictionary in ascending order\n";
        cout << "3. Display dictionary in descending order\n";
        cout << "4. Display max comparisons needed\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  // ignore newline after choice input

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, value);
                dict.insert(key, value);
                cout << "Inserted successfully.\n";
                break;

            case 2:
                dict.displayAscending();
                break;

            case 3:
                dict.displayDescending();
                break;

            case 4:
                cout << "\nMax comparisons needed for search: " << dict.getMaxComparisons() << endl;
                break;

            case 5:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
