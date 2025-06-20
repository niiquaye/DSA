#include <vector>
#include <iostream>
#include <algorithm>


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


void generate_subarrays(const std::vector<int>& array, std::vector<std::vector<int>>& result, int start, int end)
{
    if (array.size() == end)
    {
        return;
    }

    if (start > end)
    {
        generate_subarrays(array, result, 0, end+1);
    }
    else
    {
        std::vector<int> subarray {};
        for (int i = start; i <= end; i++)
        {
            subarray.push_back(array[i]);
        }

        // look at subarray
        print_vec(subarray);
        std::cout << " START: " << start << " END: " << end << std::endl;

        result.push_back(subarray);

        generate_subarrays(array, result, start+1, end);
    }
}


void generate_subarrays_iteratively(const std::vector<int>& array, std::vector<std::vector<int>>& result)
{

    for (int i = 0; i < array.size(); i++)
    {
        std::vector<int> subarray {};
        for (int j = i; j < array.size(); j++)
        {
            subarray.push_back(array[j]);
        }
        result.push_back(subarray);
    }
}

int main(int argc, char* argv[])
{
    
    std::vector<std::vector<int>> result {};

    generate_subarrays({1,2,3,5}, result, 0, 0);

    for (const auto& vec : result)
    {
        print_vec(vec);
    }

    result.clear();

    generate_subarrays_iteratively({1,2,3,5}, result);

    for (const auto& vec : result)
    {
        print_vec(vec);
    }

    return 0;
}
