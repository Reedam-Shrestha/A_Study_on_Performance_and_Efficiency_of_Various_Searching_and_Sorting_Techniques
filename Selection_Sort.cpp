#include <iostream>
#include <cstdlib> // for random values
using namespace std;

// function to do easy selection sort 
void selectionSort(int arr[], int size) {
    // go through the whole array
    for (int i = 0; i <= size - 1; i++) {
        // find the smallest element
        int smallest_indx = i;
        for (int j = i + 1; j < size; j++) {
            if (arr[j] < arr[smallest_indx]) {
                smallest_indx = j;
            }
        }
        // swap the smallest with current position
        int temp = arr[i];
        arr[i] = arr[smallest_indx];
        arr[smallest_indx] = temp;
    }
}

// print array function
void printMyArray(int arr[], int size) {
    cout << "Array: ";
    for (int i = 0; i <= size; i++) {
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
    
    // Fix the mistake in printMyArray by correcting the call
    cout << "Original ";
    printMyArray(myNums, arraySize);
    
    // Sort the array
    selectionSort(myNums, arraySize);
    
    cout << "\n \n \n";
    cout << "After Selection Sort: ";
    printMyArray(myNums, arraySize);
    
    //clean up
    delete[] myNums;
    
    cout << "Program ended. Thank you!" << endl;
    return 0;
}
