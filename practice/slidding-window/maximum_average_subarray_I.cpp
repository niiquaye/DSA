#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate

//prefix sum solution
double solution(const std::vector<int>& array, int k)
{
    std::vector<int> prefix_sum = [&]() -> std::vector<int> {
        std::vector<int> prefix_sum(array.size()+1, 0);

        for (int i = 0; i < array.size(); i++)
        {
            prefix_sum[i+1] = array[i] + prefix_sum[i];
        }
        return prefix_sum;
    } ();

    std::vector<int> window_sum = [&]() -> std::vector<int> {
        std::vector <int> window_sum(array.size()-k+1, 0);
        
        for (int i = 0; i < window_sum.size(); i++)
        {
            window_sum[i] = prefix_sum[i+k] - prefix_sum[i];
        }
        return window_sum;
    } ();

    std::transform(window_sum.begin(), window_sum.end(), window_sum.begin(),
        [&](const int& n){
            return (double)n/k;
        });

    return *std::max_element(window_sum.begin(), window_sum.end());
}

double sliding_window_solution(const std::vector<int>& array, const int k)
{
    if (array.empty()) return 0;

    double sum = std::accumulate(array.begin(), array.begin()+k, 0);

    double max_avg = sum;

    for (int i = k; i < array.size(); i++)
    {
        // update window
        sum -= array[i-k]; // remove old element from window size k
        sum += array[i]; // add new element to window size k

        max_avg = std::max(max_avg, sum);
    }
    return max_avg/static_cast<double>(k);
}

int main(int argv, char* argc[])
{
    std::cout << "Maximum Average Subarray I: " << sliding_window_solution({1,12,-5,-6,50,3},4) << std::endl;
    std::cout << "Maximum Average Subarray I: " << sliding_window_solution({5},1) << std::endl;
    return 0;
}