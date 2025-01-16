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

    // Iterative Inorder Traversal
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

    // Iterative Preorder Traversal
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

    // Iterative Postorder Traversal
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
};

int main() {
    bt tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(15);

    cout << "Iterative Inorder Traversal: ";
    tree.iterativeInorder(tree.root);

    cout << "Iterative Preorder Traversal: ";
    tree.iterativePreorder(tree.root);

    cout << "Iterative Postorder Traversal: ";
    tree.iterativePostorder(tree.root);

    return 0;
}
