#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

int brute_force_solution(const std::vector<int>& array, int k)
{
    int max_len {0};

    for (int i = 0; i < array.size(); i++)
    {
        int sum {0};
        int sub_max_len{0};
        for (int j = i; j < array.size(); j++)
        {
            sum += array.at(j);
            sub_max_len = (sum == k)? j - i + 1 : sub_max_len;
            max_len = std::max(max_len, sub_max_len);
        }
    }
    return max_len;
}


int optimal_solution(const std::vector<int>& array, int k)
{
    std::unordered_map<int, int> map {};
    map.insert({0,-1}); // -1 needed because we do (i - previous index) so if i == 0 then 0 - (-1) == 1
    int max_len {0};

    std::vector<int> prefix_sum = [](const std::vector<int>& arr){
        int sum{0};
        std::vector<int> res {};
        for (const auto elem : arr)
        {
            sum += elem;
            res.push_back(sum);
        }
        return res;
    }(array);

    for (int i = 0; i < prefix_sum.size(); i++)
    {
        auto elem = prefix_sum[i];

        if (map.find(elem - k) != map.end())
        {
            int length = i - map[elem-k];
            max_len = std::max(max_len, length);
        }

        // only store earliest occurence of where prefix sum occured
        if (map.find(elem) == map.end())
        {
            map.insert({elem, i});
        }
    }
    return max_len;
}

int main(int argv, char* argc[])
{
    std::cout << "BF Solution Maximum Size Subarray Sum Equals K: " << brute_force_solution({1, -1, 5, -2, 3}, 3) << std::endl;
    std::cout << "BF Solution Maximum Size Subarray Sum Equals K: " << brute_force_solution({-2, -1, 2, 1}, 1) << std::endl;

    std::cout << "OPtimal Solution Maximum Size Subarray Sum Equals K: " << optimal_solution({1, -1, 5, -2, 3}, 3) << std::endl;
    std::cout << "Optimal Solution Maximum Size Subarray Sum Equals K: " << optimal_solution({-2, -1, 2, 1}, 1) << std::endl;
    return 0;
}