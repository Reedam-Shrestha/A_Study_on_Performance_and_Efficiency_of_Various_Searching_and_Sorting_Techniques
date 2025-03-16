#include <iostream>
#include <random>
#include <chrono>
#include <iomanip> 

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1; // size of first subarray
    int n2 = right - mid;    // size of second subarray
    
    // Create temporary arrays 
    int* L = new int[n1];
    int* R = new int[n2];
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    // Merge the temporary arrays back into arr 
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
    
    // Copy the remaining elements of L[] 
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    // Copy the remaining elements of R[] -dont forget
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    //clear memory
    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    // recursive function for merge sort
    if (left < right) {
        // Same as (left+right)/2, but avoida overflow 
        int mid = left + (right - left) / 2;
        
        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        
        // Merge the sorted halves
        merge(arr, left, mid, right);
    }
    // no else because we just return if left >= right (base case)
}

int main() {
    std::random_device rd; 
    std::mt19937 gen(rd());
    
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    
    std::cout << "Running Merge Sort 10 times for array of size " << size << "...\n\n";
    std::cout << "Run" << "\t" << "Time (ms)" << "\n";
    std::cout << "------------------------------\n";
    
    // Variable to store total execution time for average calculation
    double total_duration = 0.0;
    
    // Perform 10 runs 
    for (int run = 1; run <= 10; run++) {
        // Generate random array
        int* arr = new int[size]; 
        std::uniform_int_distribution<> dis(1, 10000);
        for (int i = 0; i < size; i++) {
            arr[i] = dis(gen);
        }
        
        // Measure execution time
        auto start = std::chrono::high_resolution_clock::now();
        mergeSort(arr, 0, size - 1);
        auto end = std::chrono::high_resolution_clock::now();
        
        // Calculate duration in milliseconds with decimal precision
        double duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000.0;
        
        // Add to total for average calculation
        total_duration += duration;
        
        // Output result with 5 decimal places for small times
        if (duration < 0.1) {
            std::cout << run << "\t" << std::fixed << std::setprecision(6) << duration << " ms\n";
        } else {
            std::cout << run << "\t" << std::fixed << std::setprecision(2) << duration << " ms\n";
        }
        
        // clear memory
        delete[] arr;
    }
    
    // Calculate and display average time
    double average_duration = total_duration / 10.0;
    
    std::cout << "------------------------------\n";
    // Use same precision logic for average
    if (average_duration < 0.1) {
        std::cout << "Average: " << std::fixed << std::setprecision(6) << average_duration << " ms\n";
    } else {
        std::cout << "Average: " << std::fixed << std::setprecision(2) << average_duration << " ms\n";
    }
    
    return 0;
}
