#include <iostream>
using namespace std;

class Node
{
public:
    int info;
    Node *left, *right;
    bool lthread, rthread;
    Node(int val) : info(val), left(NULL), right(NULL), lthread(true), rthread(true) {} // Initially true threads
};

class ThreadedBST
{
    Node *root;

public:
    ThreadedBST() { root = NULL; }

    void insert(int ikey)
    {
        Node *ptr = root, *par = NULL;
        while (ptr != NULL)
        {
            if (ikey == ptr->info)
            {
                cout << "Duplicate Key" << endl;
                return;
            }
            par = ptr;
            if (ikey < ptr->info)
            {
                if (!ptr->lthread)
                    ptr = ptr->left; // Go left if the thread is false
                else
                    break;
            }
            else
            {
                if (!ptr->rthread)
                    ptr = ptr->right; // Go right if the thread is false
                else
                    break;
            }
        }

        Node *tmp = new Node(ikey);
        if (par == NULL)
        {
            root = tmp; // If the tree is empty, the new node becomes the root
        }
        else if (ikey < par->info)
        {
            tmp->left = par->left;
            tmp->right = par;
            par->lthread = false; // After adding a left child, change lthread to false
            par->left = tmp;
        }
        else
        {
            tmp->left = par;
            tmp->right = par->right;
            par->rthread = false; // After adding a right child, change rthread to false
            par->right = tmp;
        }
    }

    Node *inorderSuccessor(Node *ptr)
    {
        if (ptr->rthread)
            return ptr->right;
        ptr = ptr->right;
        while (!ptr->lthread)
            ptr = ptr->left;
        return ptr;
    }

    void inorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        Node *ptr = root;
        while (!ptr->lthread)
            ptr = ptr->left; // Traverse to the leftmost node
        while (ptr != NULL)
        {
            cout << ptr->info << " ";
            ptr = inorderSuccessor(ptr); // Get the next inorder successor
        }
        cout << endl;
    }

    void preorder()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        Node *ptr = root;
        while (ptr != NULL)
        {
            cout << ptr->info << " ";
            if (!ptr->lthread) // Follow the left child if lthread is false
                ptr = ptr->left;
            else if (!ptr->rthread) // Follow the right child if rthread is false
                ptr = ptr->right;
            else
            {
                while (ptr != NULL && ptr->rthread) // Move to the right if rthread is true
                    ptr = ptr->right;
                if (ptr != NULL)
                    ptr = ptr->right;
            }
        }
        cout << endl;
    }
};

int main()
{
    ThreadedBST tbst;
    int choice;
    do
    {
        cout << "\nMenu:\n";
        cout << "1. Insert\n";
        cout << "2. Inorder Traversal\n";
        cout << "3. Preorder Traversal\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            int value;
            cout << "Enter value to insert: ";
            cin >> value;
            tbst.insert(value);
            break;
        case 2:
            cout << "Inorder Traversal: ";
            tbst.inorder();
            break;
        case 3:
            cout << "Preorder Traversal: ";
            tbst.preorder();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice, try again." << endl;
        }
    } while (choice != 4);
    return 0;
}
