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

bool solution_bfs(int n, const std::vector<std::vector<int>>& edges)
{
    if (n < 0 || edges.empty()) return true;

    std::queue<int> queue {};
    std::vector<int> indegrees (n, 0);

    std::unordered_map<int, std::vector<int>> map {};
    std::vector<int> topological_sort {};

    for (const auto e : edges)
    {
        map[e[0]].push_back(e[1]);
        map[e[1]].push_back(e[0]);

        indegrees[e[0]]++;
        indegrees[e[1]]++;
    }

    for (int i = 0; i < n; i++)
    {
        if (indegrees[i] == 0)
        {
            queue.push(i);
        }
    }

    while(!queue.empty())
    {
        auto top = queue.front();
        queue.pop();

        topological_sort.push_back(top);

        for (const auto nei : map[top])
        {
            indegrees[nei]--;
            if (indegrees[nei] == 0)
            {
                queue.push(nei);
            }
        }
        
    }

    return topological_sort.size() == n;

}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}