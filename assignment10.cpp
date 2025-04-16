#include <iostream>
using namespace std;

void heapify(int arr[], int n, int i) {
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

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void printArray(int arr[], int n) {
    if (n == 0) {
        cout << "Array is empty.\n";
        return;
    }
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int* arr = nullptr;
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

            arr = new int[n];  // allocate memory

            cout << "Enter " << n << " elements:\n";
            for (int i = 0; i < n; i++)
                cin >> arr[i];
            break;

        case 2:
            cout << "Array: ";
            printArray(arr, n);
            break;

        case 3:
            if (n == 0 || arr == nullptr) {
                cout << "Please enter array first.\n";
                break;
            }
            heapSort(arr, n);
            cout << "Sorted array: ";
            printArray(arr, n);
            break;

        case 4:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    // No delete[] used here intentionally
    return 0;
}
