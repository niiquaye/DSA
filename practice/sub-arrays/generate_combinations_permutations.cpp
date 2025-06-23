#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <vector>
#include <utility>
#include <numeric>  // required for std::accumulate


inline void print_vec(const std::vector<int>& array)
{
    std::cout << "[";
    for (const auto elem : array)
    {
        std::cout << elem << ", ";
    }
    std::cout << "]";
    std::cout << "" << std::endl;
}

// generates all combinations of an array - i.e. 'N choose K'
void generate_combinations(const std::vector<int>& vec, 
                           std::vector<int>& comb,
                           int start, 
                           std::vector<std::vector<int>>& res)
{
    if (!comb.empty())
    {
        res.push_back(comb);
    }

    for (int i = start; i < vec.size(); i++)
    {
        comb.push_back(vec[i]);
        generate_combinations(vec, comb, i+1, res);
        comb.pop_back();
    }
}

void generate_permutations(const std::vector<int>& vec, 
                           std::vector<int>& comb,
                           int start, 
                           std::vector<std::vector<int>>& res)
{
    if (start == vec.size())
    {
        res.push_back(comb);
        return;
    }
    
    for (int i = start; i < vec.size(); i++)
    {
        std::cout << "Swapping " << comb[start] << " with " << comb[i] << " at level " << start << "\n";
        std::swap(comb[i], comb[start]);
        generate_permutations(vec, comb, start+1, res);
        std::swap(comb[i], comb[start]);
    }

}

int main(int argv, char* argc[])
{

    std::vector<int> cmb{};
    std::vector<std::vector<int>> res{};
    generate_combinations({1,2,4,5,6}, cmb,0, res);

    for (const auto& vec : res)
    {
        print_vec(vec);
    }

    cmb.clear(); res.clear();
    cmb = std::vector<int>{1,2,4,5,6};
    std::cout << "---------------------" << std::endl;
    generate_permutations({1,2,4,5,6}, cmb,0, res);

    for (const auto& vec : res)
    {
        print_vec(vec);
    }
    return 0;
}