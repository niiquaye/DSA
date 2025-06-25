#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate
#include <string>
#include <unordered_set>

int brute_force(const int target, const std::vector<int>& nums)
{
    if (nums.empty()) return 0;

    std::vector<int> prefix_sum = [&](const std::vector<int>& array) -> std::vector<int> {
        std::vector<int> prefix_sum(array.size() + 1, 0);

        for (int i = 0; i < array.size(); i++)
        {
            prefix_sum[i+1] = array[i] + prefix_sum[i];
        }
        return prefix_sum;
    } (nums);

    auto compute_window = [&](const std::vector<int>& prefix_sum, const int target, const int size) -> int {
        
        std::vector<int> window_sum(nums.size()-size+1,0);

        for (int i = 0; i < window_sum.size(); i++)
        {
            window_sum[i] = prefix_sum[i+size] - prefix_sum[i];
        }
        
        std::transform(window_sum.begin(), window_sum.end(), window_sum.begin(), 
        [&](const int n){
            return (n >= target)? 1 : 0;
        });

        int is_greater_than_target = std::accumulate(window_sum.begin(), window_sum.end(), 0);

        return (is_greater_than_target > 0)? size : std::numeric_limits<int>::max();
    };


    int min{std::numeric_limits<int>::max()};
    // try all subarray size 
    for (int window_size = 1; window_size <= nums.size(); window_size++)
    {
        int running_min = compute_window(prefix_sum, target, window_size);
        min = std::min(running_min, min); // only update min when it is not 0
    }
    return (min == std::numeric_limits<int>::max()) ? 0 : min;
}

int main(int argc, char* argv[])
{
    std::cout << "Minimum Size Subarray Sum: " << brute_force(7, {2,3,1,2,4,3}) << std::endl;
    std::cout << "Minimum Size Subarray Sum: " << brute_force(4, {1,4,4}) << std::endl;
    std::cout << "Minimum Size Subarray Sum: " << brute_force(11, {1,1,1,1,1,1,1,1}) << std::endl;

    return 0;
}