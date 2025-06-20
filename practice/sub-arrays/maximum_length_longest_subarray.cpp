#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


int optimal_solution(const std::vector<int>& array)
{
    int pos_len {0};
    int neg_len {0};
    int max_len {0};

    for (const auto num : array)
    {
        if (num == 0)
        {
            pos_len = 0;
            neg_len = 0;
        }


        else if (num > 0)
        {
            pos_len++;
            neg_len = (neg_len > 0)? neg_len + 1 : 0;
        }
        else
        {
            int prev_pos = pos_len;
            pos_len = (neg_len > 0)?  neg_len + 1 : 0;
            neg_len = prev_pos + 1;
        }

        max_len = std::max(max_len, pos_len);
    }

    return max_len;
}

int main(int argc, char* argv[])
{
    std::cout << "Maximum Length of SubArray with Positive Product "<< optimal_solution({1,-2,-3,4}) << std::endl;
    std::cout << "Maximum Length of SubArray with Positive Product "<< optimal_solution({0,1,-2,-3,-4}) << std::endl;
    std::cout << "Maximum Length of SubArray with Positive Product "<< optimal_solution({-1,-2,-3,0,1}) << std::endl;

    return 0;
}