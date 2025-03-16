#include <iostream>
#include <random>
#include <chrono>
#include <iomanip> 

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

// Interpolation search function
int interpolationSearch(int arr[], int n, int target) {
    int low = 0, high = n - 1;
    
    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target)
                return low;
            return -1;
        }
        
        // Probing the position with keeping uniform distribution in mind
        int pos = low + ((double)(high - low) / (arr[high] - arr[low])) * (target - arr[low]);
        
        // Condition of target found
        if (arr[pos] == target)
            return pos;
        
        // If target is larger, target is in right sub array
        if (arr[pos] < target)
            low = pos + 1;
        // If target is smaller, target is in left sub array
        else
            high = pos - 1;
    }
    return -1; // Element not found
}

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    
    // Generate random array once
    int* arr = new int[size];
    int* unsorted_arr = new int[size];
    std::uniform_int_distribution<> dis(1, 100000);
    
    // Fill both arrays with the same random values
    for (int i = 0; i < size; i++) {
        int value = dis(gen);
        arr[i] = value;
        unsorted_arr[i] = value;  // Manual copy instead of using std::copy
    }
    
    // Sort the first array using merge sort
    mergeSort(arr, 0, size - 1);
    
    // Test interpolation search on an unsorted array first (worst case)
    int target = unsorted_arr[size / 2]; // Pick a value that exists in the array
    
    std::cout << "Testing Interpolation Search on unsorted array (worst case):\n";
    auto start = std::chrono::high_resolution_clock::now();
    int result = interpolationSearch(unsorted_arr, size, target);
    auto end = std::chrono::high_resolution_clock::now();
    double unsorted_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000.0;
    std::cout << "Worst Case (Unsorted Array): " << std::fixed << std::setprecision(6) << unsorted_duration << " ms\n\n";
    
    std::cout << "Running Interpolation Search 10 times for sorted array of size " << size << "...\n\n";
    std::cout << "Run\tTime (ms)\n";
    std::cout << "------------------------------\n";
    
    // Prepare to calculate average time
    double total_time = 0.0;
    
    // Perform 10 runs on sorted array
    for (int run = 1; run <= 10; run++) {
        // Generate a random target
        int target = dis(gen);
        
        // Measure execution time
        auto start = std::chrono::high_resolution_clock::now();
        int result = interpolationSearch(arr, size, target);
        auto end = std::chrono::high_resolution_clock::now();
        
        // Calculate duration in milliseconds with 6 decimal places
        double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count() / 1000000.0;
        
        // Add to total time for average calculation
        total_time += duration;
        
        // Output result with 6 decimal places
        std::cout << run << "\t" << std::fixed << std::setprecision(6) << duration << " ms\n";
    }
    
    // Calculate and display average time
    double average_time = total_time / 10.0;
    std::cout << "------------------------------\n";
    std::cout << "Average time: " << std::fixed << std::setprecision(6) << average_time << " ms\n";
    
    // clear memory
    delete[] arr;
    delete[] unsorted_arr;
    
    return 0;
}
