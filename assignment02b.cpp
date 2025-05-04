#include <iostream>
using namespace std;

class Node {
public:
    string key, meaning;
    Node* left, * right;
    Node(string k, string m) {
        key = k;
        meaning = m;
        left = nullptr;
        right = nullptr;
    }
};

class BST {
public:
    Node* root;
    BST() {
        root = nullptr;
    }

    void insert(string k, string m) {
        Node* newNode = new Node(k, m);
        if (root == nullptr) {
            root = newNode;
            return;
        }
        Node* current = root;
        while (true) {
            if (k < current->key) {
                if (current->left == nullptr) {
                    current->left = newNode;
                    return;
                } else {
                    current = current->left;
                }
            } else if (k > current->key) {
                if (current->right == nullptr) {
                    current->right = newNode;
                    return;
                } else {
                    current = current->right;
                }
            } else {
                current->meaning = m;
                return;
            }
        }
    }

    void inorder(Node* root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->key << " : " << root->meaning << endl;
        inorder(root->right);
    }

    bool search(Node* root, string k) {
        if (root == nullptr) return false;
        if (root->key == k) return true;
        if (k < root->key) return search(root->left, k);
        return search(root->right, k);
    }

    Node* findMin(Node* root) {
        while (root && root->left != nullptr) root = root->left;
        return root;
    }

    Node* deleteNode(Node* root, string k) {
        if (root == nullptr) return root;

        if (k < root->key) root->left = deleteNode(root->left, k);
        else if (k > root->key) root->right = deleteNode(root->right, k);
        else {
            if (root->left == nullptr && root->right == nullptr) {
                delete root;
                return nullptr;
            }
            else if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
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

    int longest(Node* root) {
        if (root == nullptr) return 0;
        int lmax = longest(root->left);
        int rmax = longest(root->right);
        return 1 + max(lmax, rmax);
    }

    void mirror(Node* root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }
};

int main() {
    BST tree;
    int choice;
    string keyword, meaning;

    do {
        cout << "\nBinary Search Tree Menu:\n";
        cout << "1. Insert Keyword\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Search Keyword\n";
        cout << "4. Find Minimum Keyword\n";
        cout << "5. Find Maximum Keyword\n";
        cout << "6. Find Height\n";
        cout << "7. Mirror Tree\n";
        cout << "8. Delete Keyword\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: ";
                cin >> keyword;
                cout << "Enter meaning: ";
                cin >> meaning;
                tree.insert(keyword, meaning);
                break;

            case 2:
                cout << "Inorder Traversal: \n";
                tree.inorder(tree.root);
                break;

            case 3:
                cout << "Enter keyword to search: ";
                cin >> keyword;
                if (tree.search(tree.root, keyword)) cout << "Found\n";
                else cout << "Not Found\n";
                break;

            case 4:
                cout << "Minimum keyword: " << tree.findMin(tree.root)->key << endl;
                break;

            case 5:
                cout << "Maximum keyword: " << tree.findMin(tree.root)->key << endl;
                break;

            case 6:
                cout << "Height of tree: " << tree.longest(tree.root) << endl;
                break;

            case 7:
                tree.mirror(tree.root);
                cout << "Tree mirrored!\n";
                break;

            case 8:
                cout << "Enter keyword to delete: ";
                cin >> keyword;
                tree.root = tree.deleteNode(tree.root, keyword);
                cout << "Deleted successfully!\n";
                break;

            case 9:
                cout << "Exiting program...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);

    return 0;
}
