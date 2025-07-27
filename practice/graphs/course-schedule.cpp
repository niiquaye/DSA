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

bool solution_bfs(int num_courses, const std::vector<std::vector<int>>& prerequsites)
{
    if (prerequsites.empty()) return true;
    // Kahn's algorithm -> modified BFS

    std::unordered_map<int, std::vector<int>> map {};
    std::queue<int> queue {};

    std::vector<int> topological_order {};

    // determine indegrees
    std::vector<int> indegrees(num_courses, 0);

    // [1,0] -> to take course 1 you should take course 0 first 0 -> 1
    // construct adj list
    for (int i = 0; i < prerequsites.size(); i++)
    {
        map[prerequsites[i][1]].push_back(prerequsites[i][0]);
        indegrees[prerequsites[i][0]]++;
    }


    for (int i = 0; i < num_courses; i++)
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

        topological_order.push_back(top);

        for (const auto nei : map[top])
        {   
            indegrees[nei]--;
            if (indegrees[nei] == 0)
            {
                queue.push(nei);
            }
        }

    }

    return topological_order.size() == num_courses;
}

int solution_dfs(int num_courses, const std::vector<std::vector<int>>& prerequisites)
{
    if (prerequisites.empty() || num_courses < 0) return true;

    std::unordered_map<int, std::vector<int>> map {};

    // [1,0] -> must take course 0 before course 1 ... 0 -> 1 
    for (int i = 0; i < prerequisites.size(); i++)
    {
        auto edges = prerequisites[i];

        map[edges[1]].push_back(edges[0]);
    }

    std::vector<bool> visited(num_courses, false);
    std::vector<bool> rec_path(num_courses, false);
    std::vector<int> topological_sort {};

    std::function<bool(int)> detect_cycle = [&](int course) -> bool 
    {
        if (rec_path[course] == true) return true; // if we are revisiting a node that is currently in process
        if (visited[course] == true) return false; // a node is completely processed 

        visited[course] = true;
        rec_path[course] = true;

        for (const auto nei : map[course])
        {
            if(detect_cycle(nei))
            {
                return true;
            }
        }

        rec_path[course] = false; // back track
        topological_sort.push_back(course); // post-order topological sort
        return false;
    };

    for (int i = 0; i < num_courses; i++)
    {
        if (visited[i] == false)
        {
            if(detect_cycle(i))
            {
                return false;
            }
        }
    }

    return true;

}

int main(int argc, char* argv[])
{
    std::cout << "Hello World!" << std::endl;
    return 0;
}