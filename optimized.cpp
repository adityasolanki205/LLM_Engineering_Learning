
#include <iostream>
#include <vector>
#include <chrono>
#include <limits>

// Linear congruential generator function
uint32_t lcg(uint32_t& seed, uint32_t a = 1664525, uint32_t c = 1013904223, uint32_t m = 4294967296) {
    seed = (a * seed + c) % m;
    return seed;
}

// Maximum Subarray Sum using a variation of Kadane's Algorithm
int64_t max_subarray_sum(size_t n, uint32_t seed, int32_t min_val, int32_t max_val) {
    std::vector<int32_t> random_numbers;
    random_numbers.reserve(n);

    for (size_t i = 0; i < n; ++i) {
        uint32_t rng = lcg(seed);
        random_numbers.push_back(rng % (max_val - min_val + 1) + min_val);
    }

    int64_t max_sum = std::numeric_limits<int64_t>::min();
    int64_t current_sum = 0;

    for (size_t i = 0; i < n; ++i) {
        current_sum = 0;
        for (size_t j = i; j < n; ++j) {
            current_sum += random_numbers[j];
            if (current_sum > max_sum) {
                max_sum = current_sum;
            }
        }
    }
    return max_sum;
}

// Total function over 20 runs
int64_t total_max_subarray_sum(size_t n, uint32_t initial_seed, int32_t min_val, int32_t max_val) {
    int64_t total_sum = 0;
    
    for (int i = 0; i < 20; ++i) {
        lcg(initial_seed); // new seed for each run
        total_sum += max_subarray_sum(n, initial_seed, min_val, max_val);
    }
    
    return total_sum;
}

int main() {
    size_t n = 10000;
    uint32_t initial_seed = 42;
    int32_t min_val = -10;
    int32_t max_val = 10;

    auto start_time = std::chrono::high_resolution_clock::now();
    int64_t result = total_max_subarray_sum(n, initial_seed, min_val, max_val);
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed_time = end_time - start_time;

    std::cout << "Total Maximum Subarray Sum (20 runs): " << result << "\n";
    std::cout << "Execution Time: " << elapsed_time.count() << " seconds" << std::endl;

    return 0;
}
