#include <iostream>
#include <stack>
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

    int calculateHeight(Node* node) {
        if (node == nullptr) return -1;
        int leftHeight = calculateHeight(node->left);
        int rightHeight = calculateHeight(node->right);
        return 1 + max(leftHeight, rightHeight);
    }

    int countLeaves(Node* node) {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return countLeaves(node->left) + countLeaves(node->right);
    }

    int countInternalNodes(Node* node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) return 0;
        return 1 + countInternalNodes(node->left) + countInternalNodes(node->right);
    }

    void swapSubtrees(Node* node) {
        if (node == nullptr) return;
        swap(node->left, node->right);
        swapSubtrees(node->left);
        swapSubtrees(node->right);
    }

    void eraseTreeRecursive(Node*& node) {
        if (node == nullptr) return;
        eraseTreeRecursive(node->left);
        eraseTreeRecursive(node->right);
        delete node;
        node = nullptr;
    }

    void eraseTreeIterative(Node*& node) {
        if (node == nullptr) return;
        stack<Node*> stk;
        stk.push(node);

        while (!stk.empty()) {
            Node* current = stk.top();
            stk.pop();

            if (current->left) stk.push(current->left);
            if (current->right) stk.push(current->right);

            delete current;
        }

        node = nullptr;
    }

    Node* copyTree(Node* node) {
        if (node == nullptr) return nullptr;
        Node* newNode = new Node(node->data);
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

    BinaryTree& operator=(const BinaryTree& other) {
        if (this == &other) return *this;
        eraseTreeRecursive(root);
        root = copyTree(other.root);
        return *this;
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
        BinaryTree copiedTree;

        do {
            cout << "\n==== Binary Tree Menu ====\n";
            cout << "1. Insert Node\n";
            cout << "2. Inorder Traversal\n";
            cout << "3. Preorder Traversal\n";
            cout << "4. Postorder Traversal\n";
            cout << "5. Calculate Height\n";
            cout << "6. Count Leaves\n";
            cout << "7. Count Internal Nodes\n";
            cout << "8. Swap Left and Right Subtrees\n";
            cout << "9. Erase Tree (Recursive)\n";
            cout << "10. Erase Tree (Iterative)\n";
            cout << "11. Copy Tree\n";
            cout << "12. Exit\n";
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
                    int height = calculateHeight(root);
                    cout << "Height of the tree: " << height << endl;
                    break;
                }
                case 6: {
                    int leaves = countLeaves(root);
                    cout << "Number of leaves: " << leaves << endl;
                    break;
                }
                case 7: {
                    int internalNodes = countInternalNodes(root);
                    cout << "Number of internal nodes: " << internalNodes << endl;
                    break;
                }
                case 8: {
                    swapSubtrees(root);
                    cout << "Subtrees swapped." << endl;
                    break;
                }
                case 9: {
                    eraseTreeRecursive(root);
                    cout << "Tree erased (recursive)." << endl;
                    break;
                }
                case 10: {
                    eraseTreeIterative(root);
                    cout << "Tree erased (iterative)." << endl;
                    break;
                }
                case 11: {
                    copiedTree = *this;
                    cout << "Tree copied to another tree. Inorder of copied tree: ";
                    copiedTree.inorderTraversal(copiedTree.root);
                    cout << endl;
                    break;
                }
                case 12: {
                    cout << "Exiting..." << endl;
                    break;
                }
                default: {
                    cout << "Invalid choice! Please try again." << endl;
                    break;
                }
            }
        } while (choice != 12);
    }
};

int main() {
    BinaryTree tree;
    tree.menu();
    return 0;
}
