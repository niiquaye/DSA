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
#include <deque>

int solution(const std::vector<int>& nums, const int& k)
{
    if (nums.empty() || k < 0) return 0;

    auto at_most_k = [](const std::vector<int>& nums, int k) -> int {
        

        std::unordered_map<int, int> map {};
        int left {0};
        int result {0};

        for (int right = 0; right < nums.size(); right++)
        {
            int right_number = nums[right];

            if (map[right_number] == 0) // first check if right_number exists in map
            {
                k--; // if it does NOT decrement unique counter
            }
            map[right_number]++; // add it to map and increments its count

            while (k < 0)
            {
                int left_number = nums[left];
                map[left_number]--;
                if (map[left_number] == 0)
                {
                    k++;
                }
                left++;
            }

            result += right - left + 1;
        }
        return result;
    };

    return at_most_k(nums, k) - at_most_k(nums, k-1);
}

int main(int argc, char* argv[])
{
    std::cout << solution({1, 2, 1, 2, 3}, 2) << std::endl;
    return 0;
}