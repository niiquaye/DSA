#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate

// prefix sum 
// window sum of subarray of size 'm' minutes

//[1,0,1,2,1,1,7,5], 1+1+1+1+7+5
//[0,1,0,1,0,1,0,1],
//3 minutes


inline void print_vec(const std::vector<int>& array)
{
    std::cout << "[";
    for (const auto elem : array)
    {
        std::cout << elem << ", ";
    }
    std::cout << "]";
    std::cout << "" << std::endl;
}

std::vector<int> compute_prefix_sum(const std::vector<int> arr)
{
    std::vector<int> prefix_sum(arr.size()+1,0);

    for (int i = 0; i < arr.size(); i++)
    {
        prefix_sum[i+1] = arr[i] + prefix_sum[i];
    }
    return prefix_sum;
}

std::vector<int> compute_window_sum(const std::vector<int> prefix_sum, int minutes)
{
    std::vector<int> window_sum(prefix_sum.size()-minutes);

    for (int i = 0; i < window_sum.size(); i++)
    {
        window_sum[i] = prefix_sum[i+minutes] - prefix_sum[i];
    }
    return window_sum;
}

int solution(const std::vector<int>& customers, 
             const std::vector<int>& grumpy,
             int minutes)
{
    std::vector<int> window_sum = compute_window_sum(compute_prefix_sum(customers), minutes);

    int max_sum {0};
    for (int i = 0; i < window_sum.size(); i++)
    {
        int sum{window_sum[i]};
        for (int j = 0; j < customers.size(); j++)
        {
            // must skip to prevent double counting
            if ( j == i )
            {
                j += minutes;
            }
            // add if not grumpy
            sum = (!grumpy[j])? customers[j] + sum : sum;
        }
        max_sum = std::max(max_sum, sum);
    }
    return max_sum;

}

int main(int argv, char* argc[])
{


    return 0;
}