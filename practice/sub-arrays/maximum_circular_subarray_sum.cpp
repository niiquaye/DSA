#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


int optimal_solution(const std::vector<int>& array)
{
    if (array.empty()) return 0;

    int running_max_sum {array[0]};
    int running_min_sum {array[0]};
    int max_sum {array[0]}, min_sum{array[0]};

    int total_sum = [](const std::vector<int>& array) -> int {
        int sum {0};
        for (const auto elem : array)
            sum += elem;
        return sum;
    } (array);

    // Kadane's algo getting max/min tracking
    for (int i = 1; i < array.size(); i++)
    {
        int current = array[i];
        running_max_sum = std::max(running_max_sum + current, current);
        running_min_sum = std::min(running_min_sum + current, current);

        max_sum = std::max(running_max_sum, max_sum);
        min_sum = std::min(running_min_sum, min_sum);
    }

    // total sum less min sum will give max sum - because if it is not part of minimum subarray it could be part of maximum subarray
    // if max sum > 0 try checking if wrapping around will help else max sum is the highest score
    return (max_sum > 0)? std::max(max_sum, total_sum-min_sum) : max_sum;

}

int main(int argc, char* argv[])
{
    std::cout << "Maximum Circular Subarray Sum: " << optimal_solution({-3, -2, -3}) << std::endl;
    std::cout << "Maximum Circular Subarray Sum: " << optimal_solution({1,-2,3,-2}) << std::endl;
    std::cout << "Maximum Circular Subarray Sum: " << optimal_solution({5,-3,5}) << std::endl;
    return 0;
}