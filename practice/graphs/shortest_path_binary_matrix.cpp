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

typedef struct Coordinates
{
    int row;
    int col;
    int distance;
    // Coordinates(int x, int y, int level): x(x), y(y), distance(distance) {}
}Coordinates;

int fully_correct_solution(const std::vector<std::vector<int>>& grid)
{
    if (grid[0][0] == 1) return -1;

    size_t n = grid.size();
    std::queue<Coordinates> queue{};
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));

    std::vector<std::pair<int, int>> DIRECTIONS = {{0,1}, {1,0}, {-1,0}, {0, -1}, {1,1}, {-1,-1}, {1,-1}, {-1,1}};

    auto check_bounds_and_visited_and_0 = [&](int row, int col) -> bool 
    {
        if (col < n && col >= 0 && row < n && row >= 0 && visited[row][col] == false && grid[row][col] == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    auto bfs = [&]()-> int 
    {
        queue.push({.row = 0, .col= 0, .distance=1}); // push top left square & start by starting distance at 1
        visited[0][0] = true;

        while(!queue.empty())
        {
            size_t level = queue.size();
            for(int i = 0; i < level; i++)
            {
                auto top = queue.front();
                queue.pop();
                
                for (const auto& dir : DIRECTIONS)
                {
                    int new_row = dir.first + top.row;
                    int new_col = dir.second + top.col;

                    if (check_bounds_and_visited_and_0(new_row, new_col))
                    {
                        if (new_row == n - 1 && new_col == n - 1)
                        {
                            return top.distance; //  endpoint reached 
                        }
                        visited[new_row][new_col] = true;

                        queue.push({.row = new_row, .col = new_col, .distance = (top.distance + 1)});
                    }

                }

            }
        }
        return -1;
    };

    int res = bfs();
    return res;

}

int solution_bfs(const std::vector<std::vector<int>>& grid)
{
    if (grid[0][0] == 1) return -1;

    size_t n = grid.size();
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    std::queue<std::pair<int, int>> queue {};

    std::vector<std::pair<int, int>> DIRECTIONS = {{0,1}, {1,0}, {-1,0}, {0, -1}, {1,1}, {-1,-1}, {1,-1}, {-1,1}};

    auto check_bounds_and_visited_and_0 = [&](int col, int row) -> bool 
    {
        if (col < n && col >= 0 && row < n && row >= 0 && visited[col][row] == false && grid[col][row] == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    auto bfs = [&]() -> int 
    {
        queue.push({0,0}); // start bfs from top left corner
        visited[0][0] = true;

        int path_level {0};

        while(!queue.empty())
        {
            int level = queue.size();
            path_level++;
            
            // level order traversal via bfs 
            for(int i = 0; i < level; i++)
            {
                auto top = queue.front();
                queue.pop();

                for (const auto dir : DIRECTIONS)
                {
                    int new_col = dir.first + top.first;
                    int new_row = dir.second + top.second;
                    if (check_bounds_and_visited_and_0(new_col, new_row))
                    {
                        if (new_col == n - 1 && new_row == n - 1) return (path_level+1); // reached bottom right of grid
                        visited[new_col][new_row] = false;
                        queue.push({new_col, new_row});
                    }
                }
            }
        }
        return -1; // path does not exist for this grid
    };

    int shortest_path = bfs();
    return shortest_path;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0;
}