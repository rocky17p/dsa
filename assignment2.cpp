#include <iostream>
#include <stack>
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

class bt {
public:
    node *root;

    bt() {
        root = nullptr;
    }

    void insert(int d) {
        if (root == nullptr) {
            root = new node(d);
        } else {
            char direction;
            node *temp = root;
            while (true) {
                cout << "Enter the direction to move (l/r): ";
                cin >> direction;
                if (direction == 'l') {
                    if (temp->left == nullptr) {
                        temp->left = new node(d);
                        break;
                    } else {
                        temp = temp->left;
                    }
                } else if (direction == 'r') {
                    if (temp->right == nullptr) {
                        temp->right = new node(d);
                        break;
                    } else {
                        temp = temp->right;
                    }
                } else {
                    cout << "Invalid direction" << endl;
                }
            }
        }
    }

    void preorder(node *root) {
        if (root == nullptr) return;
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }

    void inorder(node *root) {
        if (root == nullptr) return;
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }

    void postorder(node *root) {
        if (root == nullptr) return;
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }

    // Iterative Traversals
    void iterativeInorder(node *root) {
        stack<node *> st;
        node *current = root;
        while (current != nullptr || !st.empty()) {
            while (current != nullptr) {
                st.push(current);
                current = current->left;
            }
            current = st.top();
            st.pop();
            cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }

    void iterativePreorder(node *root) {
        if (root == nullptr) return;
        stack<node *> st;
        st.push(root);
        while (!st.empty()) {
            node *current = st.top();
            st.pop();
            cout << current->data << " ";
            if (current->right) st.push(current->right);
            if (current->left) st.push(current->left);
        }
        cout << endl;
    }

    void iterativePostorder(node *root) {
        if (root == nullptr) return;
        stack<node *> st1, st2;
        st1.push(root);
        while (!st1.empty()) {
            node *current = st1.top();
            st1.pop();
            st2.push(current);
            if (current->left) st1.push(current->left);
            if (current->right) st1.push(current->right);
        }
        while (!st2.empty()) {
            cout << st2.top()->data << " ";
            st2.pop();
        }
        cout << endl;
    }

    int height(node *root) {
        if (root == nullptr) return -1;
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        return 1 + max(leftHeight, rightHeight);
    }

    int countLeaves(node *root) {
        if (root == nullptr) return 0;
        if (root->left == nullptr && root->right == nullptr) return 1;
        return countLeaves(root->left) + countLeaves(root->right);
    }

    int countInternalNodes(node *root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) return 0;
        return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
    }

    void swapSubtrees(node *root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        swapSubtrees(root->left);
        swapSubtrees(root->right);
    }

    void eraserecursive(node *&root) {
        if (root == nullptr) return;
        eraserecursive(root->left);
        eraserecursive(root->right);
        delete root;
        root = nullptr;
    }
};

int main() {
    bt tree;
    int choice, val;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert Node\n";
        cout << "2. Recursive Inorder Traversal\n";
        cout << "3. Recursive Preorder Traversal\n";
        cout << "4. Recursive Postorder Traversal\n";
        cout << "5. Iterative Inorder Traversal\n";
        cout << "6. Iterative Preorder Traversal\n";
        cout << "7. Iterative Postorder Traversal\n";
        cout << "8. Height of Tree\n";
        cout << "9. Count of Leaf Nodes\n";
        cout << "10. Count of Internal Nodes\n";
        cout << "11. Swap Subtrees\n";
        cout << "12. Erase Tree\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> val;
            tree.insert(val);
            break;
        case 2:
            cout << "Recursive Inorder Traversal: ";
            tree.inorder(tree.root);
            cout << endl;
            break;
        case 3:
            cout << "Recursive Preorder Traversal: ";
            tree.preorder(tree.root);
            cout << endl;
            break;
        case 4:
            cout << "Recursive Postorder Traversal: ";
            tree.postorder(tree.root);
            cout << endl;
            break;
        case 5:
            cout << "Iterative Inorder Traversal: ";
            tree.iterativeInorder(tree.root);
            break;
        case 6:
            cout << "Iterative Preorder Traversal: ";
            tree.iterativePreorder(tree.root);
            break;
        case 7:
            cout << "Iterative Postorder Traversal: ";
            tree.iterativePostorder(tree.root);
            break;
        case 8:
            cout << "Height of Tree: " << tree.height(tree.root) << endl;
            break;
        case 9:
            cout << "Count of Leaf Nodes: " << tree.countLeaves(tree.root) << endl;
            break;
        case 10:
            cout << "Count of Internal Nodes: " << tree.countInternalNodes(tree.root) << endl;
            break;
        case 11:
            tree.swapSubtrees(tree.root);
            cout << "Subtrees swapped.\n";
            break;
        case 12:
            tree.eraserecursive(tree.root);
            cout << "Tree erased.\n";
            break;
        case 13:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 13);

    return 0;
}
