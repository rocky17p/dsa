#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

class OBST {
    int n;
    vector<string> keys;
    vector<float> p, q;
    vector<vector<float>> e, w;
    vector<vector<int>> root;

public:
    void input();
    void buildOBST();
    void displayCostMatrix();
};

void OBST::input() {
    cout << "Enter number of keys: ";
    cin >> n;
    keys.resize(n + 1);
    p.resize(n + 1);
    q.resize(n + 1);

    cout << "Enter sorted keys:\n";
    for (int i = 1; i <= n; ++i) {
        cout << "Key " << i << ": ";
        cin >> keys[i];
    }

    cout << "Enter successful search probabilities p[i]:\n";
    for (int i = 1; i <= n; ++i) {
        cout << "p[" << i << "]: ";
        cin >> p[i];
    }

    cout << "Enter unsuccessful search probabilities q[i] (including q[0]):\n";
    for (int i = 0; i <= n; ++i) {
        cout << "q[" << i << "]: ";
        cin >> q[i];
    }
}

void OBST::buildOBST() {
    e.assign(n + 2, vector<float>(n + 1, 0));
    w.assign(n + 2, vector<float>(n + 1, 0));
    root.assign(n + 1, vector<int>(n + 1, 0));

    for (int i = 0; i <= n; ++i) {
        e[i + 1][i] = q[i];
        w[i + 1][i] = q[i];
    }

    for (int l = 1; l <= n; ++l) {
        for (int i = 1; i <= n - l + 1; ++i) {
            int j = i + l - 1;
            e[i][j] = 1e9;
            w[i][j] = w[i][j - 1] + p[j] + q[j];

            for (int r = i; r <= j; ++r) {
                float t = e[i][r - 1] + e[r + 1][j] + w[i][j];
                if (t < e[i][j]) {
                    e[i][j] = t;
                    root[i][j] = r;
                }
            }
        }
    }

    cout << "\nMinimum expected search cost: " << e[1][n] << endl;
}

void OBST::displayCostMatrix() {
    cout << "\nCost matrix e[i][j]:\n";
    for (int i = 1; i <= n + 1; ++i) {
        for (int j = 0; j <= n; ++j) {
            cout << setw(6) << e[i][j] << " ";
        }
        cout << endl;
    }

    cout << "\nRoot matrix root[i][j]:\n";
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j <= n; ++j) {
            cout << "root[" << i << "][" << j << "] = " << root[i][j] << endl;
        }
    }
}

int main() {
    OBST tree;
    int choice;

    do {
        cout << "\n--- Optimal Binary Search Tree Menu ---\n";
        cout << "1. Input keys and probabilities\n";
        cout << "2. Build OBST and show minimum cost\n";
        cout << "3. Display cost and root matrices\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            tree.input();
            break;
        case 2:
            tree.buildOBST();
            break;
        case 3:
            tree.displayCostMatrix();
            break;
        case 0:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
