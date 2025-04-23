#include <iostream>
#include <vector>
using namespace std;

void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(const vector<int>& arr) {
    if (arr.empty()) {
        cout << "Array is empty.\n";
        return;
    }
    for (int num : arr)
        cout << num << " ";
    cout << endl;
}

int main() {
    vector<int> arr;
    int n = 0;
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
            cout << "Enter number of elements: ";
            cin >> n;
            if (n <= 0) {
                cout << "Invalid size.\n";
                break;
            }

            arr.resize(n);
            cout << "Enter " << n << " elements:\n";
            for (int i = 0; i < n; i++)
                cin >> arr[i];
            break;

        case 2:
            cout << "Array: ";
            printArray(arr);
            break;

        case 3:
            if (arr.empty()) {
                cout << "Please enter array first.\n";
                break;
            }
            heapSort(arr);
            cout << "Sorted array: ";
            printArray(arr);
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
