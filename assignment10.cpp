#include <iostream>
#include <vector>
using namespace std;

class HeapSort {
public:
    vector<int> arr;

    void heapify(int n, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(n, largest);
        }
    }

    void enterArray() {
        int n;
        cout << "Enter number of elements: ";
        cin >> n;
        
        arr.resize(n);
        cout << "Enter " << n << " elements:\n";
        for (int i = 0; i < n; ++i)
            cin >> arr[i];
    }

    void displayArray() const {
        if (arr.empty()) {
            cout << "Array is empty.\n";
            return;
        }

        for (int num : arr)
            cout << num << " ";
        cout << endl;
    }

    void sort() {
        int n = arr.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(n, i);

        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(i, 0);
        }

        cout << "Sorted array: ";
        displayArray();
    }
};

int main() {
    HeapSort hs;
    int choice;

    do {
        cout << "\n=== HEAP SORT MENU ===\n";
        cout << "1. Enter Array\n";
        cout << "2. Display Array\n";
        cout << "3. Heap Sort\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            hs.enterArray();
            break;
        case 2:
            hs.displayArray();
            break;
        case 3:
            hs.sort();
            break;
        case 4:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
