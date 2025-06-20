#include <iostream>
#include <vector>
#include <algorithm>

int brute_force_maximum_subarray(const std::vector<int>& array)
{

    int best_sum {0};

    for (int i = 0; i < array.size(); i++)
    {
        int sum {0};
        for(int j = i; j < array.size(); j++)
        {
            sum += array[j];
            best_sum =  std::max(sum, best_sum);    
                    
        }

    }

    return best_sum; 

}
// kadane's algorithm 
int optimal_algo(const std::vector<int>& array)
{

    int best_sum {array[0]};
    int runnin_sum {array[0]};

    for (int i = 1; i < array.size(); i++)
    {
        runnin_sum = std::max(array[i] + runnin_sum, array[i]);
        best_sum = std::max(best_sum, runnin_sum);
    }
    return best_sum;
}

int main(int argc, char* argv[])
{
    std::cout << "Best Subarray Sum: " << brute_force_maximum_subarray({2, 3, -2, 1, 2}) << std::endl;
    return 0;
}