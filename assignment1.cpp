#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* left;
    Node* right;

    Node(int val) {
        data = val;
        left = right = nullptr;
    }
};

class BinaryTree {
public:
    Node* root;

    BinaryTree() {
        root = nullptr;
    }

    void insert(int val) {
        if (root == nullptr) {
            root = new Node(val);
        } else {
            Node* current = root;
            char direction;
            while (true) {
                cout << "Insert left or right of " << current->data << " (l/r)? ";
                cin >> direction;

                if (direction == 'l') {
                    if (current->left == nullptr) {
                        current->left = new Node(val);
                        break;
                    } else {
                        current = current->left;
                    }
                } else if (direction == 'r') {
                    if (current->right == nullptr) {
                        current->right = new Node(val);
                        break;
                    } else {
                        current = current->right;
                    }
                } else {
                    cout << "Invalid direction. Enter 'l' or 'r': ";
                }
            }
        }
    }

    int calculateTreeProperties(Node* node, int& leaves, int& internalNodes) {
        if (node == nullptr) return -1;

        int leftHeight = calculateTreeProperties(node->left, leaves, internalNodes);
        int rightHeight = calculateTreeProperties(node->right, leaves, internalNodes);

        if (node->left == nullptr && node->right == nullptr) {
            leaves++;
        } else {
            internalNodes++;
        }

        return 1 + max(leftHeight, rightHeight);
    }

    void swapSubtrees(Node* node) {
        if (node == nullptr) return;
        swap(node->left, node->right);
        swapSubtrees(node->left);
        swapSubtrees(node->right);
    }

    void eraseTree(Node*& node) {
        if (node == nullptr) return;
        eraseTree(node->left);
        eraseTree(node->right);
        delete node;
        node = nullptr;
    }

    void inorderTraversal(Node* node) {
        if (node == nullptr) return;
        inorderTraversal(node->left);
        cout << node->data << " ";
        inorderTraversal(node->right);
    }

    void preorderTraversal(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }

    void postorderTraversal(Node* node) {
        if (node == nullptr) return;
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        cout << node->data << " ";
    }

    void menu() {
        int choice;
        do {
            cout << "\n==== Binary Tree Menu ====\n";
            cout << "1. Insert Node\n";
            cout << "2. Inorder Traversal\n";
            cout << "3. Preorder Traversal\n";
            cout << "4. Postorder Traversal\n";
            cout << "5. Calculate Height, Leaves, and Internal Nodes\n";
            cout << "6. Swap Left and Right Subtrees\n";
            cout << "7. Erase Tree\n";
            cout << "8. Exit\n";
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int val;
                    cout << "Enter value to insert: ";
                    cin >> val;
                    insert(val);
                    break;
                }
                case 2: {
                    cout << "Inorder Traversal: ";
                    inorderTraversal(root);
                    cout << endl;
                    break;
                }
                case 3: {
                    cout << "Preorder Traversal: ";
                    preorderTraversal(root);
                    cout << endl;
                    break;
                }
                case 4: {
                    cout << "Postorder Traversal: ";
                    postorderTraversal(root);
                    cout << endl;
                    break;
                }
                case 5: {
                    int leaves = 0, internalNodes = 0;
                    int height = calculateTreeProperties(root, leaves, internalNodes);
                    cout << "Height of the tree: " << height << endl;
                    cout << "Number of leaves: " << leaves << endl;
                    cout << "Number of internal nodes: " << internalNodes << endl;
                    break;
                }
                case 6: {
                    swapSubtrees(root);
                    cout << "Subtrees swapped." << endl;
                    break;
                }
                case 7: {
                    eraseTree(root);
                    cout << "Tree erased." << endl;
                    break;
                }
                case 8: {
                    cout << "Exiting..." << endl;
                    break;
                }
                default: {
                    cout << "Invalid choice! Please try again." << endl;
                    break;
                }
            }
        } while (choice != 8);
    }
};

int main() {
    BinaryTree tree;
    tree.menu();
    return 0;
}
