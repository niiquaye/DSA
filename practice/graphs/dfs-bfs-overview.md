Absolutely — here's a clean, structured set of **C++ templates for BFS and DFS** on **graphs**, **trees**, and **2D grids**, with inline notes and gotchas. You can copy-paste these for review or use in contests/interviews.

---

## 🔁 BFS Templates (Breadth-First Search)

### 1. ✅ **Graph BFS (Adjacency List)**

```cpp
void bfs_graph(int start, const std::vector<std::vector<int>>& adj) {
    std::queue<int> q;
    std::vector<bool> visited(adj.size(), false);

    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        int node = q.front(); q.pop();
        // process(node);

        for (int neighbor : adj[node]) {
            if (!visited[neighbor]) {
                q.push(neighbor);
                visited[neighbor] = true;
            }
        }
    }
}
```

---

### 2. ✅ **Tree BFS (Level Order Traversal)**

```cpp
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
};

void bfs_tree(TreeNode* root) {
    if (!root) return;

    std::queue<TreeNode*> q;
    q.push(root);

    while (!q.empty()) {
        TreeNode* node = q.front(); q.pop();
        // process(node->val);

        if (node->left) q.push(node->left);
        if (node->right) q.push(node->right);
    }
}
```

---

### 3. ✅ **2D Grid BFS (e.g. Islands, Rotting Oranges, Shortest Path)**

```cpp
void bfs_grid(int start_r, int start_c, std::vector<std::vector<int>>& grid) {
    int rows = grid.size(), cols = grid[0].size();
    std::queue<std::pair<int, int>> q;
    std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));
    std::vector<std::pair<int, int>> directions = {{0,1},{1,0},{-1,0},{0,-1}}; // 4-dir

    q.push({start_r, start_c});
    visited[start_r][start_c] = true;

    while (!q.empty()) {
        auto [r, c] = q.front(); q.pop();
        // process(r, c);

        for (auto [dr, dc] : directions) {
            int nr = r + dr, nc = c + dc;
            if (nr >= 0 && nr < rows && nc >= 0 && nc < cols &&
                !visited[nr][nc] /* && grid[nr][nc] == condition */) {
                visited[nr][nc] = true;
                q.push({nr, nc});
            }
        }
    }
}
```

---

## 🔂 DFS Templates (Depth-First Search)

### 1. ✅ **Graph DFS (Adjacency List)**

```cpp
void dfs_graph(int node, const std::vector<std::vector<int>>& adj, std::vector<bool>& visited) {
    visited[node] = true;
    // process(node);

    for (int neighbor : adj[node]) {
        if (!visited[neighbor]) {
            dfs_graph(neighbor, adj, visited);
        }
    }
}
```

---

### 2. ✅ **Tree DFS (Recursive)**

```cpp
void dfs_tree(TreeNode* node) {
    if (!node) return;
    // process(node->val);

    dfs_tree(node->left);
    dfs_tree(node->right);
}
```

---

### 3. ✅ **2D Grid DFS (e.g. Islands, Maze)**

```cpp
void dfs_grid(int r, int c, std::vector<std::vector<int>>& grid, std::vector<std::vector<bool>>& visited) {
    int rows = grid.size(), cols = grid[0].size();
    if (r < 0 || r >= rows || c < 0 || c >= cols || visited[r][c] /* || grid[r][c] == wall */)
        return;

    visited[r][c] = true;
    // process(r, c);

    std::vector<std::pair<int, int>> directions = {{0,1},{1,0},{-1,0},{0,-1}};
    for (auto [dr, dc] : directions) {
        dfs_grid(r + dr, c + dc, grid, visited);
    }
}
```

---

## 🧠 Common BFS & DFS Gotchas

| Gotcha                       | Description                                                                           |
| ---------------------------- | ------------------------------------------------------------------------------------- |
| 🔁 Infinite loops            | Caused by missing `visited[node] = true` in BFS/DFS.                                  |
| 📏 Grid bounds               | Always check `r >= 0 && r < rows && c >= 0 && c < cols` for 2D grid traversal.        |
| 📦 Use `queue.size()` in BFS | For level-by-level processing (e.g., minutes in 994 Rotting Oranges).                 |
| 🔄 Graph cycles              | DFS must use a visited set to prevent revisiting and recursion stack overflow.        |
| 🔙 Mutable state             | Be careful when modifying shared state (e.g., `grid[r][c] = value`) inside recursion. |

---

## 🛠 Common Use Cases

| Use Case                                 | BFS        | DFS            |
| ---------------------------------------- | ---------- | -------------- |
| Shortest Path (Unweighted)               | ✅          | ❌              |
| Level Order Traversal (Tree)             | ✅          | ❌              |
| Connected Components (Graph/Grid)        | ✅/✅        | ✅/✅            |
| Maze Solving (All Paths)                 | ❌          | ✅              |
| Backtracking (e.g. Permutations, Sudoku) | ❌          | ✅              |
| Topological Sort                         | ✅ (Kahn's) | ✅ (Post-order) |
| Flood Fill / Island Counting             | ✅          | ✅              |

---

Let me know if you want Union-Find or Dijkstra templates as well — those often pair with graphs in advanced problems.
