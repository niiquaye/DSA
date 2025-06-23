#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate


typedef struct SubArray {
    std::vector<int> vector;
    int start;
    int end;

    // needed for vector
    bool operator<(const SubArray& other) const {
        if (start != other.start) return start < other.start;
        if (end != other.end) return end < other.end;
    }
} SubArray;



bool ranges_overlap(const SubArray& X, const SubArray& Y) {
    return !(X.end < Y.start || Y.end < X.start);
}

bool check_if_overlap(const SubArray& A, const SubArray& B, const SubArray& C)
{
    // Check all pairs
    if (ranges_overlap(A, B)) return true;
    if (ranges_overlap(A, C)) return true;
    if (ranges_overlap(B, C)) return true;

    return false;
}

void generate_subarrays_helper(const std::vector<int>& arr, 
    std::vector<SubArray>& res, 
    int start, 
    int end)
{
    if (end == arr.size()){ // we have computed all subarrays
        return;
    }

    if (start > end) // revector start end indices - since subarrays for previous index have all been generated 
    {
        generate_subarrays_helper(arr, res, 0, end+1);
    }
    else
    {
        std::vector<int> subarray {};
        for (int i = start; i <= end; i++)
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


void generate_permutations_helper(const std::vector<SubArray>& input,
                           int start,
                           int k,
                           std::vector<int>& current,
                           std::vector<std::vector<SubArray>>& res)
{


    if (current.size() == k)
    {
        std::vector<SubArray> combin {};
        for (auto index : current)
        {
            combin.push_back(input[index]);
        }

        res.push_back(combin);
        return;
    }

    else {
        for (int i = start; i < input.size(); i++)
        {
            current.push_back(i);
            generate_permutations_helper(input, i+1, k, current, res);
            current.pop_back();
        }
    }
}

std::vector<std::vector<SubArray>> generate_permutations(const std::vector<SubArray>& subarrays)
{
    int k = 3; // N choose 3
    std::vector<int> current {};
    std::vector<std::vector<SubArray>> res {};
    generate_permutations_helper(subarrays, 0, k, current, res);
    return res;
}

int brute_force(const std::vector<int>& array, int k)
{

    if (array.empty()) return 0;

    std::vector<SubArray> subarrays = generate_subarrays(array);

    std::vector<std::vector<SubArray>> res =  generate_permutations(subarrays);

    int max_sum {res.at(0).at(0).vector.at(0)}; // assumes there is at least one element available

    for (const auto combination : res)
    {
        // only 3 subarrays
        if (!check_if_overlap(combination.at(0), combination.at(1), combination.at(2)))
        {
            int first_interval {std::accumulate(combination.at(0).vector.begin(),
                                                combination.at(0).vector.end(),
                                                0)};

            int second_interval {std::accumulate(combination.at(1).vector.begin(),
                                                combination.at(1).vector.end(),
                                                0)};

            int third_interval {std::accumulate(combination.at(2).vector.begin(),
                                                combination.at(2).vector.end(),
                                                0)};
            max_sum = std::max(max_sum, first_interval + second_interval + third_interval);
        }
    }

    return max_sum;
}


std::vector<int> optimal_solution(const std::vector<int>& array, int k)
{
    std::vector<int> prefix_sum = [](const std::vector<int>& arr) -> std::vector<int>{
        std::vector<int> p_sum(arr.size()+1, 0);
        for (int i = 0; i < arr.size(); i++)
        {
            p_sum[i+1] = p_sum[i] + arr[i]; 
        }
        return p_sum;
    } (array);

    // prefix sum of length k subarrays 
    std::vector<int> windowSum = [](const std::vector<int>& arr, int k) -> std::vector<int>{
        // [2,4,5,6,6,2] & k =2 .... means 5 subarrays of length 2 .... n-k+1
        std::vector<int> window_sum (arr.size()-k+1);
        for (int i = 0; i < arr.size() - k; i++)
        {
            window_sum[i] = arr[i+k] - arr[i];
        }
        return window_sum;
    } (prefix_sum, k);

    // compute best left indices
    std::vector<int> best_left_index = [](const std::vector<int>& arr, int k) -> std::vector<int> { 
        int best_left {0};
        std::vector<int> best_left_vec {};
        for (int i = 0; i < arr.size(); i++)
        {
            best_left = (arr[i] > arr[best_left])? i : best_left;
            best_left_vec.push_back(best_left);
        }
        return best_left_vec;
    } (windowSum, k);

    // compute best right indices
    std::vector<int> best_right_index = [](const std::vector<int>& arr, int k) -> std::vector<int> { 
        int best_right {arr.size()-1};
        std::vector<int> best_right_vec (arr.size());
        for (int i = arr.size()-1; i >= 0; i--)
        {
            best_right = (arr[i] >= arr[best_right])? i : best_right;
            best_right_vec.at(i) = (best_right);
        }
        return best_right_vec;
    } (windowSum, k);


    int max_sum {std::numeric_limits<int>::min()};
    std::vector<int> res(3,-1);
    for (int i = k; i <= windowSum.size()-k-1; i++)
    {
        int mid_win = windowSum[i];
        int best_left = best_left_index[i-k]; // -k to have no overlap
        int best_right = best_right_index[i+k]; // +k to have no overlap

        int total = mid_win + windowSum[best_left] + windowSum[best_right];

        if (total > max_sum)
        {
            res.at(0) = best_left; res.at(1) = i; res.at(2) = best_right;
            max_sum = total;
        }
    }
    return res;
}

int main (int argv, char* argc[])
{
    std::cout << "Brute Force Solution Maximum Sum 3 Non Overlapping Subarrays: " << brute_force({1,2,3,4,14},3) << std::endl;
}