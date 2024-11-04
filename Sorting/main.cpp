#include <vector>
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <algorithm>

// The following code initializes all items in the values vector with random integers between 0 and max_value - 1, inclusive.
void fill_random(std::vector<int>& values, int max_value)
{
    std::srand(0);
    for (int i = 0; i < values.size(); ++i) {
        values.at(i) = std::rand() % (max_value + 1);
    }
}

// The following code initializes all items in the values vector with integers that go progressively upward from 0 to some value less than max_value.
void fill_incremental(std::vector<int>& values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = 0; i < values.size(); ++i) {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}

// The following code initializes all items in the values vector with integers that go progressively from some value less than max_value down to 0.
void fill_decremental(std::vector<int>& values, int max_value)
{
    double section = max_value / static_cast<double>(values.size());
    double current = 0.0;
    for (int i = values.size() - 1; i >= 0; --i) {
        values.at(i) = static_cast<int>(current);
        current += section;
    }
}

// Insertion Sort
void insertion_sort(std::vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        int key = values[i];
        int j = i - 1;
        while (j >= 0 && values[j] > key) {
            values[j + 1] = values[j];
            j = j - 1;
        }
        values[j + 1] = key;
    }
}

// Selection Sort
void selection_sort(std::vector<int>& values){
    for (int i = 0; i < (values.size() - 1); i++){
        int min_pos = i;
        for (int j = i + 1; j < values.size(); j++){
            if (values[j] < values[min_pos]){
                min_pos = j;
            }
        }
        if (min_pos != i){
            int temp = values[i];
            values[i] = values[min_pos];
            values[min_pos] =  temp;
        }
    }
}

// Testing
void test_sorting(void (*sort_func)(std::vector<int>&), std::vector<int>& values, const std::string& algorithm_name) {
    auto start = std::chrono::high_resolution_clock::now();
    sort_func(values);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    double total_time = duration.count() / 1'000'000.0;
    if (std::is_sorted(values.begin(), values.end())) {
        std::cout << algorithm_name << " successfully sorted the vector.\n";
    } else {
        std::cout << algorithm_name << " failed to sort the vector.\n";
    }
    std::cout << "Time taken by " << algorithm_name << ": " << total_time << " seconds.\n";
}

int main() {
    const int vector_size = 100;
    const int max_value = 999;
    std::vector<int> values(vector_size);

    // Test with random values
    fill_random(values, max_value);
    std::cout << "Testing Selection Sort on random values...\n";
    test_sorting(sortt, values, "Selectionion Sort");

    // Test with incremental values
    fill_incremental(values, max_value);
    std::cout << "Testing Selection Sort on incremental values...\n";
    test_sorting(sortt, values, "Selection Sort");

    // Test with decremental values
    fill_decremental(values, max_value);
    std::cout << "Testing Selection Sort on decremental values...\n";
    test_sorting(sortt, values, "Selection Sort");

    return 0;
}