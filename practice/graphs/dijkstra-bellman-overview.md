Absolutely! Here's a study-friendly guide with annotated **C++ templates**, **use cases**, and **gotchas** for both:

---

# 🚦 Dijkstra's Algorithm

### ✅ Use Case

* **Single-source shortest path** in a graph with **non-negative weights**
* Optimal for **dense** or **sparse** graphs depending on implementation (priority queue = sparse)

---

## 🔧 Template (Min-Heap Version using `priority_queue`)

```cpp
#include <vector>
#include <queue>
#include <utility>
#include <climits>

using namespace std;

std::vector<int> dijkstra(int start, const vector<vector<pair<int, int>>>& adj, int n) {
    // adj[u] = vector of {v, weight}
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    using P = pair<int, int>; // {distance, node}
    priority_queue<P, vector<P>, greater<>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d > dist[u]) continue; // outdated entry

        for (auto [v, w] : adj[u]) {
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}
```

---

### 💡 Gotchas

* ❌ **Negative edge weights** will break Dijkstra
* ⏳ Don't forget `if (d > dist[u]) continue;` — helps skip outdated heap entries
* 🚫 Watch for unconnected nodes (`INT_MAX` remains)

---

### 🔁 Common Applications

* GPS / maps (fastest route)
* Network latency / routing
* Game AI (pathfinding)

---

# ⚖️ Bellman-Ford Algorithm

### ✅ Use Case

* Single-source shortest path in graphs with **negative weights**
* Can detect **negative weight cycles**

---

## 🔧 Template

```cpp
#include <vector>
#include <climits>

using namespace std;

vector<int> bellman_ford(int start, const vector<tuple<int, int, int>>& edges, int n) {
    // edges = vector of {u, v, weight}
    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    for (int i = 1; i < n; ++i) {
        for (auto [u, v, w] : edges) {
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
            }
        }
    }

    // Detect negative cycle
    for (auto [u, v, w] : edges) {
        if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
            throw runtime_error("Negative cycle detected");
        }
    }

    return dist;
}
```

---

### 💡 Gotchas

* 💣 Infinite loop if you forget to break early (optional optimization)
* ❌ Does not work well with large dense graphs — O(VE)
* 🌀 Always check for **negative cycle detection**

---

### 🔁 Common Applications

* Currency arbitrage (cycle detection)
* Networks with penalties (negative weights)
* All-pairs shortest path via Johnson’s algorithm (uses Bellman-Ford)

---

## 🧠 Dijkstra vs Bellman-Ford Summary

| Feature           | Dijkstra                 | Bellman-Ford                |
| ----------------- | ------------------------ | --------------------------- |
| Time Complexity   | O((V + E) log V) (w/ PQ) | O(VE)                       |
| Negative Weights? | ❌ Not allowed            | ✅ Supported                 |
| Cycle Detection   | ❌ No                     | ✅ Negative cycle detection  |
| Use in Practice   | Real-time systems, games | Financial modeling, offline |

---

Let me know if you'd like templates for:

* Dijkstra with **set-based** optimization (faster in dense graphs)
* Bellman-Ford for **all-pairs** or with **early termination**
* Shortest path **reconstruction** after computing distances

Happy studying 🚀
