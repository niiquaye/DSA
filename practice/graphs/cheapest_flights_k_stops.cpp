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
#include <limits>

typedef struct Flight
{
    int node;
    int cost;
    int stops = 0;
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
        return a.cost > b.cost;
    };
    std::priority_queue<Flight, std::vector<Flight>, decltype(comparator)> p_queue(comparator);

    auto djikstra = [&]() -> int 
    {
        std::vector<int> running_stops(n, std::numeric_limits<int>::max());
        std::vector<int> running_cost(n, std::numeric_limits<int>::max());

        p_queue.push({.node = src, .cost = 0, .stops = 0});

        while (!p_queue.empty())
        {
            auto top = p_queue.top();
            p_queue.pop();

            if (top.node == dst)
            {
                return top.cost;
            }

            if (top.stops > k) continue;
            if ( top.cost >= running_cost[top.node]  && top.stops >= running_stops[top.node]) continue;

            running_cost[top.node] = std::min(running_cost[top.node], top.cost);
            running_stops[top.node] = std::min(running_stops[top.node], top.stops);

            for (const auto& nei : map[top.node])
            {
                p_queue.push({.node = nei.node, .cost = (top.cost + nei.cost), .stops = (top.stops + 1 ), });
            }
        }
        return -1;
    };

    int res = djikstra();
    return res;
}

int solution_bellman_ford(int n, const std::vector<std::vector<int>>& flight, int src, int dst, int k)
{
    std::vector<int> distances(n, std::numeric_limits<int>::max());

    // set distance[src] = 0 & everything else to to INT_MAX
    distances[src] = 0;

    // no more than k stops which is really k + 1 edges as we traverse the edges in graph
    for (size_t i = 0; i <= k; i++)
    {
        std::vector<int> ndist = distances; // copy
        for (const auto& f : flight)
        {
            int u = f[0] /*from*/, v = f[1] /*to*/, w = f[2] /*cost*/;
            if (ndist[v] != std::numeric_limits<int>::max())
            {
                // do we take new distance with added cost or keep old distance
                ndist[v] = std::min(ndist[v], distances[u] + w);
            }
        }
        distances.swap(ndist);
    }

    return (distances[dst] == std::numeric_limits<int>::max())?  -1 : distances[dst];
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0;
}