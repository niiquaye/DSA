Absolutely — here's a comprehensive guide for detecting cycles in **both undirected and directed graphs** using **BFS and DFS**, including:

* 🧠 Conceptual explanations
* ✅ Use cases
* 💡 C++ templates for each

---

## 🟢 UNDIRECTED GRAPH

---

### ✅ 1. DFS for Undirected Graph Cycle Detection

#### 🧠 Idea:

* DFS visits nodes recursively.
* If a visited neighbor is **not the parent**, a **cycle exists**.
* Tracks parent because undirected edges go both ways.

#### 🔧 C++ Template:

```cpp
bool hasCycleDFS_Undirected(int node, int parent,
                            const std::unordered_map<int, std::vector<int>>& graph,
                            std::vector<bool>& visited) {
    visited[node] = true;

    for (int neighbor : graph.at(node)) {
        if (!visited[neighbor]) {
            if (hasCycleDFS_Undirected(neighbor, node, graph, visited))
                return true;
        } else if (neighbor != parent) {
            return true;  // Cycle detected
        }
    }

    return false;
}
```

---

### ✅ 2. BFS (Modified Kahn's) for Undirected Graph Cycle Detection

#### 🧠 Idea:

* BFS simulates removing leaf nodes (degree 1).
* Decrement both node and neighbor degrees.
* If nodes remain or are revisited → cycle exists.

#### 🔧 C++ Template:

```cpp
bool hasCycleBFS_Undirected(int n, const std::vector<std::vector<int>>& edges) {
    std::unordered_map<int, std::vector<int>> graph;
    std::vector<int> degree(n, 0);
    std::vector<bool> visited(n, false);

    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        graph[edge[1]].push_back(edge[0]);
        degree[edge[0]]++;
        degree[edge[1]]++;
    }

    std::queue<int> q;

    for (int i = 0; i < n; ++i) {
        if (degree[i] == 1) {
            q.push(i);
            visited[i] = true;
        }
    }

    int count = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        count++;

        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                degree[neighbor]--;
                if (degree[neighbor] == 1) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
    }

    return count != n;  // if we couldn't visit all → cycle exists
}
```

---

## 🔵 DIRECTED GRAPH

---

### ✅ 3. DFS for Directed Graph Cycle Detection

#### 🧠 Idea:

* Use two arrays:

  * `visited[]`: permanently marks completed nodes
  * `rec_path[]`: marks nodes in current DFS call stack
* If you revisit a node on the call stack → **cycle detected**

#### 🔧 C++ Template:

```cpp
bool hasCycleDFS_Directed(int node,
                          const std::unordered_map<int, std::vector<int>>& graph,
                          std::vector<bool>& visited,
                          std::vector<bool>& rec_path) {
    visited[node] = true;
    rec_path[node] = true;

    for (int neighbor : graph.at(node)) {
        if (!visited[neighbor]) {
            if (hasCycleDFS_Directed(neighbor, graph, visited, rec_path))
                return true;
        } else if (rec_path[neighbor]) {
            return true;  // Cycle detected (back edge)
        }
    }

    rec_path[node] = false;
    return false;
}
```

---

### ✅ 4. BFS (Kahn’s Algorithm) for Directed Graph Cycle Detection

#### 🧠 Idea:

* Count in-degrees of all nodes.
* Start from nodes with `in-degree = 0`.
* If not all nodes are processed → **cycle exists**

#### 🔧 C++ Template:

```cpp
bool hasCycleBFS_Directed(int n, const std::vector<std::vector<int>>& edges) {
    std::unordered_map<int, std::vector<int>> graph;
    std::vector<int> in_degree(n, 0);

    for (const auto& edge : edges) {
        graph[edge[0]].push_back(edge[1]);
        in_degree[edge[1]]++;
    }

    std::queue<int> q;
    for (int i = 0; i < n; ++i) {
        if (in_degree[i] == 0)
            q.push(i);
    }

    int count = 0;
    while (!q.empty()) {
        int node = q.front(); q.pop();
        count++;

        for (int neighbor : graph[node]) {
            if (--in_degree[neighbor] == 0)
                q.push(neighbor);
        }
    }

    return count != n;  // If we didn’t visit all nodes → cycle exists
}
```

---

## 📌 When to Use Which

| Graph Type | Method     | Use When...                                  | Pros                        |
| ---------- | ---------- | -------------------------------------------- | --------------------------- |
| Undirected | DFS        | Simple structure, small graph                | Easy to implement           |
| Undirected | BFS (Kahn) | You want to process from leaves inward       | Good for pruning approaches |
| Directed   | DFS        | Topological sort, back edge detection needed | Detects cycles & ordering   |
| Directed   | BFS (Kahn) | Want to ensure full acyclic traversal        | Efficient and clean         |

---

Let me know if you'd like a `main()` wrapper to test each of these or an example graph to run them on.
