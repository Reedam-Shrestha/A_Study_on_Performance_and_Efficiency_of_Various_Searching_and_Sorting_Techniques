#include <iostream>
#include <random>
#include <chrono>
#include <iomanip> 

using namespace std;
using namespace chrono;

// Function to merge two subarrays
void merge(int arr[], int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;
    
    // Create temp arrays
    int* L = new int[n1];
    int* R = new int[n2];
    
    // Copy data to temp arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[middle + 1 + j];
    
    // Merge the temp arrays back into arr[left..right]
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

// Merge sort function
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        // Find the middle point
        int middle = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, middle);
        mergeSort(arr, middle + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, middle, right);
    }
}

// Linear search function
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1; // Element not found
}

int main() {
    random_device rd;
    mt19937 gen(rd());
    
    int size;
    cout << "Enter the size of the array: ";
    cin >> size;
    
    // Generate random array once
    int* arr = new int[size];
    uniform_int_distribution<> dis(1, 100000);
    for (int i = 0; i < size; i++) {
        arr[i] = dis(gen);
    }
    
    // Sort the array using merge sort
    mergeSort(arr, 0, size - 1);
    
    cout << "Running Basic Search for array of size " << size << "...\n\n";
    
    // Best case: search for the first element
    auto start = high_resolution_clock::now();
    int result = linearSearch(arr, size, arr[0]);
    auto end = high_resolution_clock::now();
    double best_case_duration = duration_cast<nanoseconds>(end - start).count() / 1000000.0;
    
    // Worst case: search for the last element
    start = high_resolution_clock::now();
    result = linearSearch(arr, size, arr[size-1]);
    end = high_resolution_clock::now();
    double worst_case_duration = duration_cast<nanoseconds>(end - start).count() / 1000000.0;
    
    cout << "Best Case (First Element): " << fixed << setprecision(6) << best_case_duration << " ms\n";
    cout << "Worst Case (Last Element): " << fixed << setprecision(6) << worst_case_duration << " ms\n\n";
    
    cout << "Running 10 Random Searches:\n";
    cout << "Run\tTime (ms)\n";
    cout << "------------------------------\n";
    
    double total_duration = 0.0;
    double durations[10]; // Array to store all durations
    
    // Perform 10 runs with random targets
    for (int run = 1; run <= 10; run++) {
        // Generate a random target
        int target = dis(gen);
        
        // Measure execution time
        start = high_resolution_clock::now();
        result = linearSearch(arr, size, target);
        end = high_resolution_clock::now();
        
        // Calculate duration in milliseconds with 6 decimal places
        double duration = duration_cast<nanoseconds>(end - start).count() / 1000000.0;
        durations[run-1] = duration; // Store duration in array
        total_duration += duration;   // Add to total
        
        // Output result with 6 decimal places
        cout << run << "\t" << fixed << setprecision(6) << duration << " ms\n";
    }
    
    // Calculate and display average
    double average_duration = total_duration / 10.0;
    cout << "------------------------------\n";
    cout << "Average: " << fixed << setprecision(6) << average_duration << " ms\n";
    
    // clear  memory
    delete[] arr;
    
    return 0;
}
