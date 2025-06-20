#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <utility>

typedef struct SubArray {
    std::vector<int> vector;
    int start;
    int end;
} SubArray;


void generate_subarrays_helper(const std::vector<int>& arr, 
    std::vector<SubArray>& res, 
    int start, 
    int end)
{
    if (end == arr.size()){ // we have computed all subarrays
        return;
    }

    if (start > end) // reset start end indices - since subarrays for previous index have all been generated 
    {
        generate_subarrays_helper(arr, res, 0, end+1);
    }
    else
    {
        std::vector<int> subarray {};
        for (int i = start; i < end; i++)
        {
            subarray.push_back(arr[i]);
        }
        res.push_back({.vector = subarray, .start = start, .end = end});

        // increment start index
        generate_subarrays_helper(arr, res, start+1, end);
    }
}

std::vector<SubArray> generate_subarrays(const std::vector<int>& arr)
{
    std::vector<SubArray> res {};
    generate_subarrays_helper(arr, res, 0, 0);
    return res;
}

int brute_force(const std::vector<int>& array, int k)
{

    std::vector<SubArray> subarrays = generate_subarrays(array);

}