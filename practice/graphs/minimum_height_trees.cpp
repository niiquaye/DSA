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
#include <map>
#include <memory>

std::vector<int> solution_bfs(int n, const std::vector<std::vector<int>>& edges)
{
    std::unordered_map<int, std::vector<int>> map {};
    std::queue<int> queue {};
    std::vector<int> indegree(n, 0);
    // undirected graph
    for (const auto& edge : edges)
    {
        map[edge[0]].push_back(edge[1]);
        map[edge[1]].push_back(edge[0]);

        // for modififed Kahn's algo
        indegree[edge[0]]++;
        indegree[edge[1]]++;
    }





    auto bfs = [&]() -> void 
    {
        for (int i = 0; i < n; i++)
        {
            if (indegree[i] == 1)
            {
                queue.push(i);
            }
        }

        int remaining_leafs = n; // prunning leafs via bfs with modified kahns

        // check for 2 since if odd number of nodes means there will be on central node and even number of node means two central nodes
        while (remaining_leafs > 2) // instead of checking queue empty check how many leaves left
        {
            int node_level = queue.size();
            remaining_leafs -= node_level;

            for (int i = 0; i < node_level; i++)
            {
                auto top = queue.front();
                queue.pop();

                for (const auto nei : map[top])
                {
                    indegree[nei]--; // prune leaf
                    if (indegree[nei] == 1)
                    {
                        queue.push(nei);
                    }
                }
            }
        }
    };

    bfs();

    std::vector<int> res {};
    // leaves left over in queue are nodes with minimum height that survivded prunning 
    while(!queue.empty())
    {
        res.push_back(queue.front()); //should invoke move constructor 
        queue.pop();
    }
    return res;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0;
}