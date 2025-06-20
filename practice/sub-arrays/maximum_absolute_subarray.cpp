#include <iostream>
#include <vector>
#include <algorithm>

// Custom multi_max
template <typename T>
T multi_max(T a) {
    return a;
}

template <typename T, typename... Args>
T multi_max(T a, Args... args) {
    return std::max(a, multi_max(args...));
}

// Custom multi_min
template <typename T>
T multi_min(T a) {
    return a;
}

template <typename T, typename... Args>
T multi_min(T a, Args... args) {
    return std::min(a, multi_min(args...));
}

int optimal_solution(const std::vector<int>& arrays)
{
    if (arrays.empty()) return 0;

    int running_max {arrays[0]};
    int running_min {arrays[0]};
    int best_sum {std::abs(arrays[0])};

    for (int i = 1; i < arrays.size(); i++)
    {
        int current = arrays[i];

        int prev_min = running_min;
        int prev_max = running_max;

        running_max = multi_max((running_max+current), (current), (prev_min+current));
        running_min = multi_min((running_min+current), (current), (prev_max+current));
        
        // compare ABS of all sub arrays here 
        best_sum = multi_max(std::abs(running_max), std::abs(best_sum), std::abs(running_min));
    }

    return best_sum;
}

int main(int argc, char* argv[])
{
    std::cout << "Best Absolute Subarray Sum: " << optimal_solution({2,-5,1,-4,3,-2}) << std::endl;
    std::cout << "Best Absolute Subarray Sum: " << optimal_solution({1,-3,2,3,-4}) << std::endl;

    return 0;
}