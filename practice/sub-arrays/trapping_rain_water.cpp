#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate


// left/right max tracking solution 
int solution(const std::vector<int>& height)
{
    if(height.empty()) {return 0;}

    std::vector<int> left = [&]() -> std::vector<int> {
        std::vector<int> left_vec(height.size(),0);
        left_vec.at(0) = {height.at(0)};
        for (int i = 1; i < height.size(); i++)
        {
            // kind of like kadane's algo - either pick previous max or update it 
            left_vec[i] = std::max(left_vec[i-1], height[i]);
        }
        return left_vec;
    }();

    std::vector<int> right = [&]() -> std::vector<int> {
        std::vector<int> right_vec(height.size(),0);
        right_vec.at(height.size()-1) = {height.at(height.size()-1)};
        for (int i = height.size()-2; i >= 0; i--)
        {
            // kind of like kadane's algo - either pick previous max or update it
            // since we populate the right vector from right to left - the previous element is i+1 not i-1 
            right_vec[i] = std::max(right_vec[i+1], height[i]);
        }
        return right_vec;
    }();

    int water {0};
    for (int i = 0; i < height.size(); i++)
    {
        water += (std::min(left[i], right[i]) - height[i]);
    }

    return water;
}


int main(int argv, char* argc[])
{
    std::cout << "Trapping Rain Water (Precompute Letf & Right Max Solution): " << solution({0,1,0,2,1,0,1,3,2,1,2,1}) << std::endl;
    std::cout << "Trapping Rain Water (Precompute Letf & Right Max Solution): " << solution({4,2,0,3,2,5}) << std::endl;

}