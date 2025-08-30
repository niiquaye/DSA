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

typedef struct Flight
{
    int node;
    int cost;
}Flight;


int solution(int n, const std::vector<std::vector<int>>& flight, int src, int dst, int k)
{
    std::unordered_map<int, std::vector<Flight>> map {};

    for (const auto& edge : flight)
    {
        auto from = edge[0];
        auto to = edge[1];
        auto cost = edge[2];

        map[from].push_back({.node = to, .cost = cost});
    }

    auto comparator = [](const Flight& a, const Flight& b) -> bool 
    {
        return a.cost < b.cost;
    };
    std::priority_queue<Flight, std::vector<Flight>, decltype(comparator)> p_queue(comparator);

    auto djikstra = [&]() -> int 
    {
        int stops = k;
        p_queue.push({.node = src, .cost = 0});

        while(!p_queue.empty() && stops--)
        {
            auto top = p_queue.top();
            p_queue.pop();

            if (top.node == dst)
            {
                return top.cost; // return running cost
            }

            for (const auto& nei : map[top.node])
            {
                p_queue.push({.node = nei, .cost = nei.cost + top.cost});
            }
        }
        return -1;
    };

    int res = djikstra();
    return res;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0;
}