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

int solution_bfs(std::vector<std::vector<int>> grid)
{
    if (grid.empty()) return 0;

    int row = grid.size();
    int col = grid[0].size();

    std::vector<std::vector<bool>> visited(row, std::vector<bool>(col,false)); // keep track of visited cells

    std::queue<std::pair<int, int>> queue {};

    std::vector<std::vector<int>> DIRECTIONS = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}}; // directions to visit

    //insert ALL rotten oranges into queue to begin search - kick off BFS with all marked rotten oranges
    int fresh {0};
    for (int r = 0; r < row; r++)
    {
        for(int c = 0; c < col; c++)
        {
            if (grid[r][c] == 1)
            {
                fresh++;
            }
            else if (grid[r][c] == 2)
            {
                queue.push({r,c});
                visited[r][c] = true;
            }
        }
    }

    auto is_not_visited_and_in_bounds_and_fresh = [&](int r, int c) -> bool {
        if (r < grid.size() && c < grid[0].size() && r >= 0 && c >= 0 && visited[r][c] == false && grid[r][c] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    };

    int minutes {0}; // LEVEL!! iterations in bfs

    while(!queue.empty() && fresh > 0)
    {
        minutes++;

        // level by level - bfs - levels in bfs determined by queue size
        int NUM_LEVELS {queue.size()};
        for (int level = 0; level < NUM_LEVELS; level++)
        {
            const auto [r,c] = queue.front();
            queue.pop();



            visited[r][c] = true; // visit node/cell


            for (const auto& coordinates : DIRECTIONS)
            {
                int new_r = coordinates[0] + r;
                int new_c = coordinates[1] + c;

                if (is_not_visited_and_in_bounds_and_fresh(new_r, new_c))
                {
                    grid[new_r][new_c] = 2; // it is now rotten
                    queue.push({new_r, new_c});
                    fresh--;
                }

            }
        }

    }

    return fresh == 0 ? minutes : -1;
}

int main(int argc, char* argv[])
{
    std::cout << solution_bfs({{2,1,1},{1,1,0}, {0,1,1}}) << std::endl;
    std::cout << solution_bfs({{2,1,1},{0,1,1},{1,0,1}}) << std::endl;
    std::cout << solution_bfs({{0,2}}) << std::endl;

    return 0;
}