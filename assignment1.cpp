#include <iostream>
#include <stack>
using namespace std;

class node {
public:
    int data;
    node *left, *right, *parent;

    node(int v) {
        data = v;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }
};

class bt {
public:
    node *root;

    bt() {
        root = nullptr;
    }

    void insert(int data) {
        node *newnode = new node(data);
        if (root == nullptr) {
            root = newnode;
            return;
        }

        node *temp = root;
        while (true) {
            char direction;
            cout << "Enter the direction you want to move (l/r): ";
            cin >> direction;

            if (direction == 'l') {
                if (temp->left == nullptr) {
                    temp->left = newnode;
                    newnode->parent = temp;
                    cout << "Value inserted to the left of " << temp->data << endl;
                    return;
                } else {
                    temp = temp->left;
                }
            } else if (direction == 'r') {
                if (temp->right == nullptr) {
                    temp->right = newnode;
                    newnode->parent = temp;
                    cout << "Value inserted to the right of " << temp->data << endl;
                    return;
                } else {
                    temp = temp->right;
                }
            } else {
                cout << "Invalid direction! Please enter 'l' or 'r'." << endl;
            }
        }
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
        int lmax = height(root->left);
        int rmax = height(root->right);
        return 1 + max(lmax, rmax);
    }

    int countLeaves(node *root) {
        if (root == nullptr) return 0;
        int count = 0;
        stack<node *> st;
        st.push(root);
        while (!st.empty()) {
            node *current = st.top();
            st.pop();
            if (current->left == nullptr && current->right == nullptr) {
                count++;
            }
            if (current->left) st.push(current->left);
            if (current->right) st.push(current->right);
        }
        return count;
    }

    int countNodes(node *root) {
        if (root == nullptr) return 0;
        int count = 0;
        stack<node *> st;
        st.push(root);
        while (!st.empty()) {
            node *current = st.top();
            st.pop();
            count++;
            if (current->left) st.push(current->left);
            if (current->right) st.push(current->right);
        }
        return count;
    }

    int countInternalNodes(node *root) {
        if (root == nullptr || (root->left == nullptr && root->right == nullptr)) return 0;
        return 1 + countInternalNodes(root->left) + countInternalNodes(root->right);
    }

    void mirror(node *root) {
        if (root == nullptr) return;
        swap(root->left, root->right);
        mirror(root->left);
        mirror(root->right);
    }

    void erase_recursive(node *node) {
        if (node != NULL) {
            erase_recursive(node->left);
            erase_recursive(node->right);
            delete node;
        }
    }

    void erase_non_recursive(node *nnode) {
        if (nnode != NULL) {
            stack<node *> st;
            st.push(nnode);
            while (!st.empty()) {
                node *temp = st.top();
                st.pop();

                if (temp->left) st.push(temp->left);
                if (temp->right) st.push(temp->right);

                delete temp;
            }
            root = NULL;
        }
    }

    node *copytree(node *copynode) {
        if (copynode != NULL) {
            node *temp = new node(copynode->data);
            temp->left = copytree(copynode->left);
            if (temp->left) temp->left->parent = temp;
            temp->right = copytree(copynode->right);
            if (temp->right) temp->right->parent = temp;
            return temp;
        }
        return NULL;
    }
};

int main() {
    bt tree;
    int choice, value;

    while (true) {
        cout << "\n------ Menu ------\n";
        cout << "1. Insert\n";
        cout << "2. Display Inorder (Iterative)\n";
        cout << "3. Display Preorder (Iterative)\n";
        cout << "4. Display Postorder (Iterative)\n";
        cout << "5. Height of Tree\n";
        cout << "6. Count Nodes\n";
        cout << "7. Count Leaf Nodes\n";
        cout << "8. Count Internal Nodes\n";
        cout << "9. Mirror Tree\n";
        cout << "10. Delete Tree (Recursive)\n";
        cout << "11. Delete Tree (Non-Recursive)\n";
        cout << "12. Copy Tree\n";
        cout << "13. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to insert: ";
            cin >> value;
            tree.insert(value);
            break;
        case 2:
            cout << "Inorder (Iterative): ";
            tree.iterativeInorder(tree.root);
            break;
        case 3:
            cout << "Preorder (Iterative): ";
            tree.iterativePreorder(tree.root);
            break;
        case 4:
            cout << "Postorder (Iterative): ";
            tree.iterativePostorder(tree.root);
            break;
        case 5:
            cout << "Height of Tree: " << tree.height(tree.root) << endl;
            break;
        case 6:
            cout << "Total Nodes: " << tree.countNodes(tree.root) << endl;
            break;
        case 7:
            cout << "Leaf Nodes: " << tree.countLeaves(tree.root) << endl;
            break;
        case 8:
            cout << "Internal Nodes: " << tree.countInternalNodes(tree.root) << endl;
            break;
        case 9:
            tree.mirror(tree.root);
            cout << "Tree mirrored.\n";
            break;
        case 10:
            tree.erase_recursive(tree.root);
            tree.root = nullptr;
            cout << "Tree deleted recursively.\n";
            break;
        case 11:
            tree.erase_non_recursive(tree.root);
            cout << "Tree deleted non-recursively.\n";
            break;
        case 12:
            cout << "Tree copied.\n";
            break;
        case 13:
            exit(0);
        default:
            cout << "Invalid choice! Try again.\n";
        }
    }
}
