#include <iostream>
#include <vector>
#include <climits>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class OBST {
private:
    vector<int> keys, freq;
    int n;
    vector<vector<int>> cost, rootIndex;
    Node* root;

    Node* buildTree(int i, int j) {
        if (i > j) return nullptr;
        int r = rootIndex[i][j];
        Node* node = new Node(keys[r]);
        node->left = buildTree(i, r - 1);
        node->right = buildTree(r + 1, j);
        return node;
    }

public:
    OBST() : root(nullptr), n(0) {}

    void input() {
        cout << "Enter number of keys: ";
        cin >> n;
        keys.resize(n);
        freq.resize(n);

        cout << "Enter keys (sorted): ";
        for (int i = 0; i < n; i++) cin >> keys[i];

        cout << "Enter corresponding frequencies: ";
        for (int i = 0; i < n; i++) cin >> freq[i];
    }

    void build() {
        cost.assign(n, vector<int>(n));
        rootIndex.assign(n, vector<int>(n));

        for (int i = 0; i < n; i++) {
            cost[i][i] = freq[i];
            rootIndex[i][i] = i;
        }

        for (int len = 2; len <= n; len++) {
            for (int i = 0; i <= n - len; i++) {
                int j = i + len - 1;
                cost[i][j] = INT_MAX;
                int sum = 0;
                for (int s = i; s <= j; s++) sum += freq[s];

                for (int k = i; k <= j; k++) {
                    int c = sum;
                    if (k > i) c += cost[i][k - 1];
                    if (k < j) c += cost[k + 1][j];
                    if (c < cost[i][j]) {
                        cost[i][j] = c;
                        rootIndex[i][j] = k;
                    }
                }
            }
        }

        root = buildTree(0, n - 1);
        cout << "OBST built successfully.\n";
    }

    void inorder(Node* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }

    void preorder(Node* node) {
        if (!node) return;
        cout << node->key << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void showInorder() {
        if (!root) {
            cout << "Tree not built.\n";
            return;
        }
        inorder(root);
        cout << endl;
    }

    void showPreorder() {
        if (!root) {
            cout << "Tree not built.\n";
            return;
        }
        preorder(root);
        cout << endl;
    }

    void showMinCost() {
        if (cost.empty()) {
            cout << "Tree not built.\n";
            return;
        }
        cout << "Minimum Search Cost: " << cost[0][n - 1] << endl;
    }
};

int main() {
    OBST tree;
    int choice;

    do {
        cout << "\n--- Optimal BST Menu ---\n";
        cout << "1. Input Keys and Frequencies\n";
        cout << "2. Build Optimal BST\n";
        cout << "3. Inorder Traversal\n";
        cout << "4. Preorder Traversal\n";
        cout << "5. Show Minimum Search Cost\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: tree.input(); break;
            case 2: tree.build(); break;
            case 3: tree.showInorder(); break;
            case 4: tree.showPreorder(); break;
            case 5: tree.showMinCost(); break;
            case 6: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n"; break;
        }
    } while (choice != 6);

    return 0;
}
