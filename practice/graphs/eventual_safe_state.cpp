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
#include <queue>
#include <memory>

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

std::vector<int> solution_dfs(const std::vector<std::vector<int>>& graph)
{
    // 0 - unvisited,  1 - visiting, 2 - safe (no cycle)
    std::vector<int> state(graph.size(), 0); // Graph colouring problem 

    std::vector<int> result {};
    std::unordered_map<int, std::vector<int>> map {};

    for (int i = 0; i < graph.size(); i++)
    {
        for (const auto edge : graph[i])
        {
            map[i].push_back(edge);
        }
    }

    std::function<bool(int)> dfs_colouring = [&](int node) -> bool 
    {


        if (state[node] != 0 ) return state[node] == 2; // already visited node - check if it is safe

        state[node] = 1; // visiting node

        for (const auto nei : map[node])
        {
            if (state[nei] == 1 || dfs_colouring(nei) == false)
            {
               return false;
            }
        }

        state[node] = 2; // marking it as safe/done
        return true;

    };



    for (int i = 0; i < graph.size(); i++)
    {
        if (dfs_colouring(i) && state[i] == 2) result.push_back(i);
    }

    return result;
    
}

int main(int argc, char* argv[])
{
    print_vec( solution_dfs( {{1,2},{2,3},{5},{0},{5},{},{}} ) );
    return 0;
}