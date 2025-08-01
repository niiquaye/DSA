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

bool solution_dfs(const std::vector<std::vector<int>>& graph)
{
    std::unordered_map<int, std::vector<int>> map {};

    for (int i = 0; i < graph.size(); i++)
    {
        for (const auto edge : graph[i])
        {
            map[i].push_back(edge);
        }
    }

    std::vector<int> colour (graph.size(), 0); // 0 - unvisited, 1 - colour A, 2 - colour B 

    std::function<bool(int)> dfs_colour = [&](int node) -> bool 
    {

        for (const auto nei : map[node])
        {
            if (colour[nei] == 0)
            {
                colour[nei] = (colour[node] == 1)? 2: 1;
                if (!dfs_colour(nei)) return false;
            } else if (colour[nei] == colour[node])
            {
                return false;
            }
        }

        return true;


    };

    for (int i = 0; i < graph.size(); i++)
    {
        if (colour[i] == 0)
        {   
            colour[i] = 1; 
            if (!dfs_colour(i)) return false;
        }
    }

    return true;
}

bool solution_bfs(const std::vector<std::vector<int>>& graph)
{
    std::unordered_map<int, std::vector<int>> map {};

    for (int i = 0; i < graph.size(); i++)
    {
        for (const auto edge : graph[i])
        {
            map[i].push_back(edge);
        }
    }

    std::queue<int> queue {};
    std::vector<int> colour (graph.size(), 0); // 0 - unvisited, 1 - colour A, 2 - colour B

    auto bfs_colouring = [&](int node) -> bool 
    {
        if (colour[node] != 0) return true;

        queue.push(node);
        colour[node] = 1;

        while(!queue.empty())
        {
            int top = queue.front();
            queue.pop();

            for (const auto nei : map[top])
            {
                if (colour[nei] == 0)
                {
                    colour[nei] = (colour[top] == 1)? 2 : 1;
                    queue.push(nei);
                } else if (colour[nei] == colour[top])
                {
                    return false;
                }
            }
        }

        return true;

    };

    for (int i = 0; i < graph.size(); i++)
    {
        if (!bfs_colouring(i)) return false; 
    }

    return true;
}

int main(int argc, char* argv[])
{
    std::cout << "BFS" << std::endl;

    std::cout << solution_bfs({ {1,2,3},{0,2},{0,1,3},{0,2} }) << std::endl;
    std::cout << solution_bfs({ {1,3},{0,2},{1,3},{0,2} }) << std::endl;

    std::cout << "DFS" << std::endl;

    std::cout << solution_dfs({ {1,2,3},{0,2},{0,1,3},{0,2} }) << std::endl;
    std::cout << solution_dfs({ {1,3},{0,2},{1,3},{0,2} }) << std::endl;

    return 0;
}