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


int solution_bfs(const std::vector<std::vector<char>>& grid)
{
    if (grid.empty()) return 0;

    std::queue<std::pair<int, int>> queue {};

    std::vector<std::pair<int, int>> DIRECTIONS = {{1,0}, {0,1}, {-1, 0}, {0, -1}};

    int rows = grid.size();
    int cols = grid[0].size();

    std::vector<std::vector<bool>> visited (rows, std::vector<bool>(cols, false)); // visited array

    auto check_bounds_and_not_visited = [&](int r, int c) -> bool {
        if (r < rows && c < cols && r >= 0 && c >= 0 && visited[r][c] == false && grid[r][c] == '1')
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    auto bfs = [&](const int r, const int c) -> void {
        
        visited[r][c] = true;

        queue.push({r,c});

        while(!queue.empty())
        {
            const auto [r,c] = queue.front();
            queue.pop();

            for (const auto& [row, col] : DIRECTIONS)
            {
                int new_row = r + row;
                int new_col = c + col;

                if (check_bounds_and_not_visited(new_row, new_col))
                {
                    visited[new_row][new_col] = true;
                    queue.push({new_row, new_col});
                }
            }
        }
    };

    int islands {0};

    for(int r = 0; r < rows; r++)
    {
        for (int c = 0; c < cols; c++)
        {
            if (grid[r][c] == '1' && visited[r][c] == false)
            {
                bfs(r, c);
                islands++;
            }
        }
    }
    return islands;
}

int main(int argc, char* argv[])
{
    std::cout << solution_bfs(
        {
            {'1','1','1','1','0'},
            {'1','1','0','1','0'},
            {'1','1','0','0','0'},
            {'0','0','0','0','0'}
        }
    ) << std::endl;
}