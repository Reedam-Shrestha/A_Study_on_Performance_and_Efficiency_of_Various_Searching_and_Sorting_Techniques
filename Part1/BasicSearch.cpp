#include <iostream>
#include <cstdlib> // for random value
using namespace std;

// function to merge two halfs in merge sort
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    
    // create temp arrays
    int L[leftSize], R[rightSize];
    
    // copy data to temp arrays
    for (i = 0; i < leftSize; i++)
        L[i] = arr[left + i];
    for (j = 0; j < rightSize; j++)
        R[j] = arr[mid + 1 + j];
    
    // merge temp arrays back into arr[left..right]
    i = 0; // index for first subarray
    j = 0; // index for second subarray
    k = left; // index for merged array
    
    while (i < leftSize && j < rightSize) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // copy remaining elements of L[]
    while (i < leftSize) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // copy remaining elements of R[]
    while (j < rightSize) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

// recursive function to do merge sort
void mergesort(int arr[], int left, int right) {
    if (left < right) {
        // find middle point
        int middle = left + (right - left) / 2;
        
        // sort first and second halves
        mergesort(arr, left, middle);
        mergesort(arr, middle + 1, right);
        
        // merge the sorted halves
        merge(arr, left, middle, right);
    }
}

// function to do binary search
int binarySearch(int arr[], int size, int targetNum) {
    int left = 0;
    int right = size - 1;
    
    while (left <= right) {
        // find middle point
        int middle = (left + right) / 2;
        
        // check if target is at middle
        if (arr[middle] == targetNum) {
            return middle;
        }
        
        // if target is greater, ignore left half
        if (arr[middle] < targetNum) {
            left = middle + 1;
        } 
        // if target is smaller, ignore right half
        else {
            right = middle - 1;
        }
    }
    
    return -1; // not found :(
}

// print array function
void printMyArray(int arr[], int size) {
    cout << "Array: ";
    for (int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int arraySize;
    
    // ask user for array size
    cout << "Enter the size of array: ";
    cin >> arraySize;
    
    // make the array 
    int* myNums = new int[arraySize];
    
    // Add option to choose between random or manual input
    int inputChoice;
    cout << "\nHow would you like to input values?" << endl;
    cout << "1. Random values" << endl;
    cout << "2. Manual entry" << endl;
    cout << "Enter your choice: ";
    cin >> inputChoice;
    
    if (inputChoice == 1) {
        // Initialize random seed
        srand(time(NULL));
        
        // Generate random values (between 1 and 100000)
        cout << "Generating " << arraySize << " random numbers..." << endl;
        for (int i = 0; i < arraySize; i++) {
            myNums[i] = rand() % 100000 + 1;
        }
    } else {
        // Original manual input code
        cout << "Enter " << arraySize << " integers:" << endl;
        for (int i = 0; i < arraySize; i++) {
            cout << "Enter number " << (i+1) << ": ";
            cin >> myNums[i];
        }
    }
    
    // print original array
    cout << "Original ";
    printMyArray(myNums, arraySize);
    
    // Sort array using merge sort (binary search needs sorted array)
    mergesort(myNums, 0, arraySize - 1);
    cout << "\nSorted ";
    printMyArray(myNums, arraySize);
    
    while (true) {
        int searchNumber;
        cout << "\nEnter a number to search for (or -1 to quit): ";
        cin >> searchNumber;
        
        if (searchNumber == -1) { // FIXED THE CONDITION HERE
            break;
        }
        
        int result = binarySearch(myNums, arraySize, searchNumber);
        
        if (result != -1) {
            cout << "Number found at position " << result << endl;
        } else {
            cout << "Number not found in array" << endl;
        }
    }
    
    // clean up
    delete[] myNums;
    
    cout << "Program ended. Thank you!" << endl;
    return 0;
}
