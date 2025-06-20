#include <iostream>
#include <vector>
#include <algorithm>

// Custom multi_max
template <typename T>
T multi_max(T a) {
    return a;
}

template <typename T, typename... Args>
T multi_max(T a, Args... args) {
    return std::max(a, multi_max(args...));
}

// Custom multi_min
template <typename T>
T multi_min(T a) {
    return a;
}

template <typename T, typename... Args>
T multi_min(T a, Args... args) {
    return std::min(a, multi_min(args...));
}

int brute_force_maximum_subarray(const std::vector<int>& array)
{

    int best_product {1};

    for (int i = 0; i < array.size(); i++)
    {
        int product {1};
        for(int j = i; j < array.size(); j++)
        {
            product *= array[j];
            best_product =  std::max(product, best_product);    
                    
        }

    }

    return best_product; 

}


int optimal_solution(const std::vector<int>& array)
{
    int best_product {array[0]};
    int running_max {array[0]};
    int running_min {array[0]};

    for (int i = 1; i < array.size(); i++)
    {
        
        int current = array[i];

        // if (current < 0)
        // {
        //     std::swap(running_max, running_min);
        // }
        
        int prev_max = running_max;
        int prev_min = running_min;

        // for min/max kandane algo tracking 
        // either A) extend running sub array, B) start new sub array C) extend previous sub array because of potential sign flip 
        running_max = multi_max<int>(current*running_max, current, current*prev_min);
        running_min = multi_min<int>(current*running_min, current, current*prev_max);

        best_product = std::max(best_product, running_max);

    }

    return best_product;
}

int main(int argc, char* argv[])
{
    std::cout << "Best Subarray Product Brute Force: " << brute_force_maximum_subarray({2, 3, -2, 1, 2}) << std::endl;
    std::cout << "Best Subarray Product Optimal: " << optimal_solution({-4, -3, -2}) << std::endl;

    return 0;
}
