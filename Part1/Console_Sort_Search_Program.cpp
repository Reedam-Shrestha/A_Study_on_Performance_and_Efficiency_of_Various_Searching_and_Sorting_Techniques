#include <iostream>
#include <cstdlib> // for random number input
using namespace std;

// function to do easy selection sort
void selectionSort(int arr[], int size) {
    // go through the whole array
    for (int i = 0; i < size - 1; i++) {
        // find the smallest element
        int smallest_indx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[smallest_indx]) {
                smallest_indx = j;
            }
        }
        // swap the smallest integer found with current position
        int temp = arr[i];
        arr[i] = arr[smallest_indx];
        arr[smallest_indx] = temp;
    }
}

// fuction to merge two halfs in merge sort
void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int leftSize = mid - left + 1;
    int rightSize = right - mid;
    
    // create temporary arrays
    int L[leftSize], R[rightSize];
    
    // copy data to these temporary arrays
    for (i = 0; i < leftSize; i++)
        L[i] = arr[left + i];
    for (j = 0; j < rightSize; j++)
        R[j] = arr[mid + 1 + j];
    
    // merge temporary arrays back into arr[left..right]
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
    
    // copy remaining elements of Left array
    while (i < leftSize) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // copy remaining elements of Right araay
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

// normal search to check every element
int basicSearch(int arr[], int size, int targetNum) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == targetNum) {
            return i; // found it!
        }
    }
    return -1; // not found :(
}

// fancy interpolation search for sorted arrays
int interpolation_srch(int arr[], int size, int target) {
    // need low and high values to start with
    int low = 0;
    int high = size - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        // Calculate position with this formula
        int pos = low + ((target - arr[low]) * (high - low)) / (arr[high] - arr[low]);
        
        // Check if found
        if (arr[pos] == target) {
            return pos;
        }
        
        // If target is bigger, search higher part
        if (arr[pos] < target) {
            low = pos + 1;
        } else {
            // If smaller, search lower part
            high = pos - 1;
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
    
    // NEW CODE: Add option to choose between random or manual input
    int inputChoice;
    cout << "\nHow would you like to input values?" << endl;
    cout << "1. Random values" << endl;
    cout << "2. Manual entry" << endl;
    cout << "Enter your choice: ";
    cin >> inputChoice;
    
    if (inputChoice == 1) {
        // Initialize random seed
        srand(time(NULL));
        
        // Generate random values (between 1 and 100)
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
    
    // sorting part
    int sortChoice;
    
    while (true) {
        cout << "\nChoose sorting method:" << endl;
        cout << "1. Selection Sort" << endl;
        cout << "2. Merge Sort" << endl;
        cout << "3. End Program" << endl;
        cout << "Enter your choice: ";
        cin >> sortChoice;
        
        if (sortChoice == 1) {
            selectionSort(myNums, arraySize);
            cout << "After Selection Sort: ";
            printMyArray(myNums, arraySize);
            break;
        } else if (sortChoice == 2) {
            mergesort(myNums, 0, arraySize - 1);
            cout << "After Merge Sort: ";
            printMyArray(myNums, arraySize);
            break;
        } else if (sortChoice == 3) {
            delete[] myNums; //clean up memory.
            return 0;
        } else {
            cout << "Invalid choice. Try again!" << endl;
        }
    }
    
    // searching part
    int searchChoice;
    
    while (true) {
        cout << "\nChoose search method:" << endl;
        cout << "1. Basic Search" << endl;
        cout << "2. Interpolation Search" << endl;
        cout << "3. End Program" << endl;
        cout << "Enter your choice: ";
        cin >> searchChoice;
        
        if (searchChoice == 1 || searchChoice == 2) {
            int lookFor;
            cout << "Enter number to search for: ";
            cin >> lookFor;
            
            int result;
            if (searchChoice == 1) {
                result = basicSearch(myNums, arraySize, lookFor);
            } else {
                result = interpolation_srch(myNums, arraySize, lookFor);
            }
            
            if (result != -1) {
                cout << "Number found at position " << result << endl;
            } else {
                cout << "Number not found in array" << endl;
            }
            break;
        } else if (searchChoice == 3) {
            break;
        } else {
            cout << "Invalid choice. Try again!" << endl;
        }
    }
    
    // clean up
    delete[] myNums;
    
    cout << "Program ended. Thank you for using!" << endl;
    return 0;
}
