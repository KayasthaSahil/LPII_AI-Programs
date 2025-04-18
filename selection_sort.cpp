#include <iostream>
using namespace std;

// Function to take input from the user
void inputArray(int arr[], int size) {
    cout << "Enter " << size << " elements of the array: ";
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
}

// Function to display the array
void displayArray(int arr[], int size) {
    cout << "Sorted array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Function to implement Selection Sort
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        int minIndex = i;  // Assume the current index has the smallest element

        // Find the index of the smallest element in the remaining array
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Swap the found minimum element with the first element of the unsorted part
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// Main function
int main() {
    int size;
    
    // Taking array size as input
    cout << "Enter the number of elements: ";
    cin >> size;
    
    int arr[size];

    // Input the array
    inputArray(arr, size);

    // Sorting the array
    selectionSort(arr, size);

    // Displaying the sorted array
    displayArray(arr, size);

    return 0;
}
