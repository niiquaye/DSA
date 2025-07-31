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

std::vector<int> solution_dfs(int n, const std::vector<std::vector<int>>& prerequisites)
{
    if (n <= 0 || prerequisites.empty() || prerequisites[0].empty()) return {};

    std::unordered_map<int, std::vector<int>> map {};
    std::vector<int> rev_topological_sort {};

    std::vector<bool> visited(n, false);
    std::vector<bool> on_path(n, false);

    for (const auto edge : prerequisites)
    {
        // u -> v
        int u = edge[1]; // b_i
        int v = edge[0]; // a_i
        
        map[u].push_back(v);
    }

    std::function<bool(int)> dfs_cycle_detect = [&](int node) -> bool 
    {
        if (on_path[node] == true) return true; // !!check if on_path is violated first!!
        if (visited[node] == true) return false;

        visited[node] = true;
        on_path[node] = true;

        for(const auto nei : map[node])
        {
            if (visited[nei] == false)
            {
                if(dfs_cycle_detect(nei))
                {
                    return true;
                }
            }
        }

        on_path[node] = false;
        rev_topological_sort.push_back(node);
        return false;
    };

    // must loop through to do dfs over potentially potentially disconneted components
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false && dfs_cycle_detect(i)) return {}; //cycle detected
    }

    std::reverse(rev_topological_sort.begin(), rev_topological_sort.end());
    return rev_topological_sort;
}

std::vector<int> solution_bfs(int n, const std::vector<std::vector<int>>& prerequisites)
{
    if (n <= 0 || prerequisites.empty() || prerequisites[0].empty()) return {};

    std::queue<int> queue{};
    std::unordered_map<int, std::vector<int>> map {};
    std::vector<int> indegrees(n, 0);
    std::vector<int> topological_sort {};

    for (const auto edge : prerequisites)
    {
        // u -> v
        int u = edge[1]; // b_i
        int v = edge[0]; // a_i
        
        map[u].push_back(v);
        indegrees[v]++;
    }

    auto kahn_algo = [&]() -> std::vector<int> 
    {
        for(int i = 0; i < n; i++)
        {
            if (indegrees[i] == 0)
            {
                queue.push(i);
            }
        }

        while(!queue.empty())
        {
            int top = queue.front();
            queue.pop();

            topological_sort.push_back(top);

            for (const auto nei : map[top])
            {
                indegrees[nei]--;
                if(indegrees[nei] == 0)
                {
                    queue.push(nei);
                }
            }
        }

        return topological_sort;

    };

    kahn_algo();

    return (topological_sort.size() == n) ? topological_sort : std::vector<int>(); 
}

int main(int argc, char* argv[])
{
    std::cout << "SOLUTION BFS" << std::endl;
    print_vec(solution_bfs(2, {{1,0}}));
    print_vec(solution_bfs(4, {{1,0}, {2,0}, {3,1}, {3,2}}));
    print_vec(solution_bfs(1, {{}}));

    std::cout << "SOLUTION DFS" << std::endl;
    print_vec(solution_dfs(2, {{1,0}}));
    print_vec(solution_dfs(4, {{1,0}, {2,0}, {3,1}, {3,2}}));
    print_vec(solution_dfs(1, {{}}));
    return 0;
}