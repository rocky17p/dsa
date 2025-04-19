#include <iostream>
#include <stack>
using namespace std;

class node
{
public:
    char data;
    node *left;
    node *right;
    node(char d)
    {
        data = d;
        left = nullptr;
        right = nullptr;
    }
};

bool isoperator(char c)
{
    return (c == '+' || c == '-' || c == '/' || c == '*');
}

node *constructtree(string s)
{
    stack<node *> st;
    for (int i = s.length() - 1; i >= 0; i--)
    {
        node *newnode = new node(s[i]);
        if (isoperator(s[i]))
        {
            newnode->left = st.top();
            st.pop();
            newnode->right = st.top();
            st.pop();
        }
        st.push(newnode);
    }
    return st.top();
}

void count(node *root)
{
    if (root == nullptr)
        return;
    stack<node *> st;
    st.push(root);
    int op = 0, operand = 0;
    while (!st.empty())
    {
        node *temp = st.top();
        st.pop();
        if (isoperator(temp->data))
            op++;
        else if (isalnum(temp->data))
            operand++;
        if (temp->right)
            st.push(temp->right);
        if (temp->left)
            st.push(temp->left);
    }
    cout << "the number of operands = " << operand << endl;
    cout << "the number of operators = " << op << endl;
}

void postorder(node *root)
{
    if (root == nullptr)
        return;
    stack<node *> st1, st2;
    st1.push(root);
    while (!st1.empty())
    {
        node *temp = st1.top();
        st1.pop();
        st2.push(temp);
        if (temp->left)
            st1.push(temp->left);
        if (temp->right)
            st1.push(temp->right);
    }
    while (!st2.empty())
    {
        cout << st2.top()->data << " ";
        st2.pop();
    }
    cout << endl;
}

int main()
{
    string s;
    cout << "enter the prefix expression" << endl;
    cin >> s;
    node *root = constructtree(s);
    cout << "postorder traversal is" << endl;
    postorder(root);
    count(root);
    return 0;
}
