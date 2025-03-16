#include <iostream>
#include <random>
#include <chrono>
#include <iomanip>

void selectionSort(int arr[], int n) {
    // we need to do n-1 passes cause the last element is automatically in place
    for (int i = 0; i < n - 1; i++) {
        // Find minimum element in unsorted part
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            // check if we found a smaller element
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        // Swap the found minimum element with the first element
        if (min_idx != i) {
            // classic swap 
            int temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
}

int main() {
    std::random_device rd; 
    std::mt19937 gen(rd());
    
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;
    
    std::cout << "Running Selection Sort 10 times for array of size " << size << "...\n\n";
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
        selectionSort(arr, size);
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
        
        //clean up
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
