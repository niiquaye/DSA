Here’s a **graph coloring template in C++** using both **DFS and BFS**, along with an explanation of its structure, applications, and adaptability to real LeetCode problems.

---

## 🎯 What Is Graph Coloring?

Graph coloring is the process of assigning colors (labels) to vertices such that certain constraints are satisfied — often that no two adjacent nodes share the same color. It’s frequently used in:

### 🔧 Common Use Cases:

| Use Case                         | Description                                                                                                   |
| -------------------------------- | ------------------------------------------------------------------------------------------------------------- |
| ✅ **Bipartite Checking**         | Use 2 colors (0 and 1). If two adjacent nodes have the same color, it's not bipartite.                        |
| ✅ **Cycle Detection (Directed)** | DFS coloring: `0 = unvisited`, `1 = visiting`, `2 = processed`. If you visit a "visiting" node again → cycle. |
| ✅ **Component Labelling**        | Use different colors for each connected component (like flood-fill).                                          |
| ✅ **Constraint Satisfaction**    | Scheduling, map coloring, Sudoku, etc. (usually with >2 colors).                                              |

---

## ✅ 1. DFS-Based Graph Coloring Template (for Bipartite Checking)

```cpp
bool dfs_color(const std::vector<std::vector<int>>& graph, std::vector<int>& color, int node, int current_color) {
    color[node] = current_color;
    for (int neighbor : graph[node]) {
        if (color[neighbor] == -1) {
            if (!dfs_color(graph, color, neighbor, 1 - current_color)) return false;
        } else if (color[neighbor] == current_color) {
            return false; // Conflict: same color as neighbor
        }
    }
    return true;
}

bool isBipartiteDFS(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> color(n, -1); // -1 = unvisited

    for (int i = 0; i < n; ++i) {
        if (color[i] == -1) {
            if (!dfs_color(graph, color, i, 0)) return false;
        }
    }
    return true;
}
```

---

## ✅ 2. BFS-Based Graph Coloring Template (for Bipartite Checking)

```cpp
bool isBipartiteBFS(const std::vector<std::vector<int>>& graph) {
    int n = graph.size();
    std::vector<int> color(n, -1); // -1 = unvisited

    for (int start = 0; start < n; ++start) {
        if (color[start] != -1) continue;

        std::queue<int> q;
        q.push(start);
        color[start] = 0;

        while (!q.empty()) {
            int node = q.front(); q.pop();
            for (int neighbor : graph[node]) {
                if (color[neighbor] == -1) {
                    color[neighbor] = 1 - color[node];
                    q.push(neighbor);
                } else if (color[neighbor] == color[node]) {
                    return false;
                }
            }
        }
    }
    return true;
}
```

---

## 🧠 Key Design Concepts

| Element                 | Purpose                                     |
| ----------------------- | ------------------------------------------- |
| `color[node] == -1`     | Marks a node as unvisited                   |
| `color[node] == 0 or 1` | Marks color assignment (used for bipartite) |
| `1 - color[node]`       | Switches color (flip between 0 and 1)       |
| Queue vs Recursion      | BFS = iterative with queue; DFS = recursive |

---

## 🧪 When to Use Which

| Problem Type                       | Use BFS or DFS?                      | Example                    |
| ---------------------------------- | ------------------------------------ | -------------------------- |
| **Bipartite test**                 | Both work                            | LeetCode 785               |
| **Cycle detection (directed)**     | DFS with 3-state coloring (`0,1,2`)  | LeetCode 207, 802          |
| **Flood-fill / labeling**          | BFS preferred (iterative stack-safe) | Custom grids, islands      |
| **Color assignment with k-colors** | DFS with backtracking                | Graph k-coloring (NP-hard) |

---

## 🧩 Sample Usage (Graph as Adjacency List)

```cpp
int main() {
    std::vector<std::vector<int>> graph = {
        {1, 3},
        {0, 2},
        {1, 3},
        {0, 2}
    };

    std::cout << "Is Bipartite (DFS): " << isBipartiteDFS(graph) << "\n";
    std::cout << "Is Bipartite (BFS): " << isBipartiteBFS(graph) << "\n";
}
```

Expected output: `1` (true) – the graph is bipartite.

---

## 🧵 Wrap-Up

These templates help solve a **wide class of problems** in both competitive programming and interviews. You can:

* Modify for **directed acyclic graph (DAG)** cycle detection by using 3 states (`unvisited`, `visiting`, `safe`).
* Extend to **component-based coloring** by assigning colors > 2.
* Combine with **topological sorting** or **DSU** for more advanced applications.

Let me know if you want a template with full input parsing or edge-list conversion for contests.
