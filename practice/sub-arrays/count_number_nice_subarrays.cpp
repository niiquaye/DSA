#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

void generate_subarrays_helper(const std::vector<int>& array, std::vector<std::vector<int>>& result, int start, int end)
{
    if (array.size() == end)
        return;

    if (start > end)
    {
        generate_subarrays_helper(array, result, 0, end+1);
    }
    else 
    {
        std::vector<int> subarray {};
        for (int i = start; i <= end; i++)
        {
            subarray.push_back(array[i]);
        }
        result.push_back(subarray);

        generate_subarrays_helper(array, result, start+1, end);
    }
}

std::vector<std::vector<int>> generate_subarrays(const std::vector<int>& array)
{

    std::vector<std::vector<int>> res {};
    generate_subarrays_helper(array, res, 0, 0);

    return res;
}

int brute_force_solution(const std::vector<int>& array, int k)
{
    std::vector<std::vector<int>> res = generate_subarrays(array);
    int nice {0};
    for (const auto sub : res)
    {
        int odd_count {0};
        for (const auto elem : sub)
        {

            if (!(elem % 2 == 0))
            {
                odd_count++;
            }
        }
        if (odd_count == k)
        {
            nice++;
        }
    }
    return nice;

}


// prefix sum + Hash Map
int optimal_solution(const std::vector<int>& array, int k)
{

    std::unordered_map<int, int> map {};
    map.insert({0, 1}); // add 0 in map because when prefix_sum - k == 0 for the 1st index
    int nice {0};

    std::vector<int> prefix_sum_odd_numbers = [](const std::vector<int>& arr){
        int sum {0};
        std::vector<int> res {};
        for (const auto elem : arr)
        {
            sum += elem % 2; // only count odd numbers
            res.push_back(sum);
        }
        return res;
    }(array);


    for (const auto elem : prefix_sum_odd_numbers)
    {
        nice += map[elem-k];
        map[elem]++;
    }

    return nice;
}

int main(int argv, char* argc[])
{
    std::cout << "Brute Force Solution Count Number of Nice Subarrays: " << brute_force_solution({1,1,2,1,1}, 3) << std::endl;
    std::cout << "Brute Force Solution Count Number of Nice Subarrays: " << brute_force_solution({2,4,6}, 1) << std::endl;
    std::cout << "Brute Force Solution Count Number of Nice Subarrays: " << brute_force_solution({2,2,2,1,2,2,1,2,2,2}, 2) << std::endl;

    std::cout << "Optimal Solution Count Number of Nice Subarrays: " << optimal_solution({2,1,2,1,1}, 2) << std::endl;
    std::cout << "Optimal Solution Count Number of Nice Subarrays: " << optimal_solution({1,1,2,1,1}, 3) << std::endl;
    std::cout << "Optimal Solution Count Number of Nice Subarrays: " << optimal_solution({2,4,6}, 1) << std::endl;
    std::cout << "Optimal Solution Count Number of Nice Subarrays: " << optimal_solution({2,2,2,1,2,2,1,2,2,2}, 2) << std::endl;
}