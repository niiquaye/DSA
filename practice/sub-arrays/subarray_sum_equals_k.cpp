#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>


inline void print_vec(const std::vector<int>& array)
{
    std::cout << "[";
    for (int i = 0; i < array.size(); i++)
    {   
        int elem = array[i];

        auto trailing = (i == array.size() - 1)? "": ", ";

        std::cout << elem << trailing;
    }
    std::cout << "]";
    std::cout << "" << std::endl;
}


std::vector<int> generate_pre_fix_sum(const std::vector<int>& array)
{
    std::vector<int> sum {};

    int running_sum {0};
    for (int i = 0; i < array.size(); i++)
    {
        running_sum += array[i];
        sum.push_back(running_sum);
    }
    return sum;
}

int brute_force_subarray(const std::vector<int>& array, int k)
{

    int count {0};

    for (int i = 0; i < array.size(); i++)
    {
        int sum {0};
        for(int j = i; j < array.size(); j++)
        {
            sum += array[j];
            count =  (sum == k)? count+1 : count;    
                    
        }

    }

    return count; 

}

int optimal_soluton(const std::vector<int>& array, int k)
{
    if (array.empty()) return 0;

    int count {0};
    std::vector<int> prefix_sum = generate_pre_fix_sum(array);
    std::unordered_map<int, int> map {};

    map.insert({0, 1}); // when prefix sum equals k

    for (const auto elem : prefix_sum)
    {
        
        count = (map.find(elem-k) != map.end())? count+map[elem-k]: count;

        map[elem]++;
    }


    return count;
}

int main(int argc, char* argv[])
{
    std::cout << "BF - Sub Array Sum Equals K: " << brute_force_subarray({1,1,1}, 2) << std::endl;
    std::cout << "BF - Sub Array Sum Equals K: " << brute_force_subarray({1,2,3}, 3) << std::endl;
    std::cout << "Optimal Sub Array Sum Equals K: " << optimal_soluton({1,2,3}, 3) << std::endl;

    return 0;
}