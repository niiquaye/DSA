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

bool solution(const std::vector<std::vector<char>>& grid, const std::string& word)
{
    if (grid.empty() || grid[0].empty() ||word.empty()) return false;
    int row = grid.size(), col = grid[0].size();
    std::vector<std::vector<bool>> visited(row, std::vector<bool>(col, false));

    std::function<bool(int, int, int)> dfs = [&](int r, int c, int pos) -> bool 
    {
        if (r < 0 || r > row || c < 0 || c > col) return false;
        if (visited[r][c] == true) return false; // already visited
        if (grid[r][c] != word[pos]) return false; // mismatched character

        if (pos == word.size() - 1) return true;
    
        visited[r][c] = true; // mark as visited
        bool res {};
        if (grid[r][c] == word[pos])
            res =  dfs(r+1, c, pos + 1) || 
                   dfs(r-1, c, pos + 1) || 
                   dfs(r, c+1, pos + 1) || 
                   dfs(r, c-1, pos + 1);
        visited[r][c] = false; // backtrack
        return res;
    };

    for (int i = 0; i < row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            if(dfs(i,j,0)) return true;
        }
    }
    return false;
}

int main(int argc, char* argv[])
{
    std::cout << "Hello World" << std::endl;
    return 0;
}