Absolutely — here's a **Union Find (Disjoint Set Union - DSU)** template in C++, along with notes, variations, and common use cases — all formatted like the BFS/DFS templates for consistency.

---

## 🔗 Union-Find / DSU Template in C++

### ✅ **Basic DSU with Path Compression + Union by Rank**

```cpp
class UnionFind {
private:
    std::vector<int> parent;
    std::vector<int> rank; // Optional: used to keep the tree flat

public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        // Initially, each node is its own parent
        for (int i = 0; i < n; ++i)
            parent[i] = i;
    }

    // Find with path compression
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]); // compress path
        return parent[x];
    }

    // Union by rank
    bool unite(int x, int y) {
        int xr = find(x);
        int yr = find(y);

        if (xr == yr) return false; // already connected

        if (rank[xr] < rank[yr]) {
            parent[xr] = yr;
        } else if (rank[xr] > rank[yr]) {
            parent[yr] = xr;
        } else {
            parent[yr] = xr;
            rank[xr]++;
        }
        return true;
    }

    // Check if two nodes are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
```

---

## 📚 Common DSU Use Cases

| Problem Type                         | Use Union-Find? |
| ------------------------------------ | --------------- |
| Connected components (graph/grid)    | ✅               |
| Kruskal’s Minimum Spanning Tree      | ✅               |
| Cycle detection in undirected graph  | ✅               |
| Percolation / dynamic connectivity   | ✅               |
| Redundant connections (Leetcode 684) | ✅               |
| Equations possible (Leetcode 990)    | ✅               |
| Count islands (union-find style)     | ✅               |

---

## 🧠 Gotchas and Tips

| Gotcha                          | Tip                                                              |
| ------------------------------- | ---------------------------------------------------------------- |
| ❌ Forgetting path compression   | Causes O(n) time instead of nearly O(1)                          |
| ❌ Not using `find` before union | Always use `find` before uniting                                 |
| 🧱 Watch for off-by-one errors  | Indexing starts at 0 vs 1 — make sure your problem agrees        |
| 🧮 Count connected components   | Track `count--` whenever you do a `union` between different sets |
| 🧬 Grid to DSU                  | Use `id = r * cols + c` to map 2D → 1D index                     |

---

## 🧪 Example Usage

```cpp
int n = 10;
UnionFind uf(n);

uf.unite(1, 2);
uf.unite(2, 3);
std::cout << uf.connected(1, 3); // true
std::cout << uf.connected(1, 4); // false
```

---

Let me know if you'd like the **grid-based Union-Find** version or examples of **union-find with rollback / undo** (used in advanced dynamic connectivity problems).


🎉 **You’re doing an amazing job! You’re building a powerful interview toolkit, one pattern at a time.**
Since you’ve now got **subarrays**, **sliding window**, and **priority queues / heaps** under your belt, let’s tackle another *classic* that is **extremely popular in interviews** — one you’ll find in most FAANG/Big Tech screens.

---

## 🚀 **Next Must-Know Pattern: Union-Find (Disjoint Set Union / DSU)**

---

### 🔑 **Why Union-Find?**

* It efficiently answers *connectivity* queries in a collection of elements: “Are these in the same group?”
* Handles **dynamic grouping**, great for network connectivity, islands, friends circles, and Kruskal’s MST.
* Underpins many graph algorithms and problems with equivalence relations.

---

## 📝 **What you should know before trying DSU problems**

👉 **1️⃣ Understand the core DSU operations**

* `find(x)`: determine which group element `x` belongs to (returns root / parent)
* `union(x, y)`: merge the groups of `x` and `y`

👉 **2️⃣ Path compression**

* When `find` walks up the tree, make it point directly to the root for efficiency.

👉 **3️⃣ Union by rank / size**

* When merging two sets, attach the smaller one under the larger one to keep the tree shallow.

👉 **4️⃣ Basic graph representation**

* Familiarize with edges, nodes, adjacency — many union-find problems are graph-based.

👉 **5️⃣ Recognize when DSU applies**

* When the problem involves *merging sets*, *checking connectivity*, *components*, or *equivalence*.

---

## 🛣 **Roadmap of Union-Find Problems (in order)**

---

### ✅ **Stage 1: Connectivity / Components**

---

🔹 **[547. Number of Provinces (formerly Friends Circle)](https://leetcode.com/problems/number-of-provinces/)**
*Count connected components in an adjacency matrix.*

🔹 **[1319. Number of Operations to Make Network Connected](https://leetcode.com/problems/number-of-operations-to-make-network-connected/)**
*Minimum operations to connect all nodes in a network.*

---

### ✅ **Stage 2: Islands and dynamic groups**

---

🔹 **[200. Number of Islands](https://leetcode.com/problems/number-of-islands/)**
*You can solve this with DFS or DSU — DSU is elegant.*

🔹 **[305. Number of Islands II](https://leetcode.com/problems/number-of-islands-ii/)**
*Dynamic version: as you add land, track island counts (classic DSU).*

---

### ✅ **Stage 3: Advanced DSU applications**

---

🔹 **[399. Evaluate Division](https://leetcode.com/problems/evaluate-division/)**
*Union-Find with weights to represent equations and ratios.*

🔹 **[721. Accounts Merge](https://leetcode.com/problems/accounts-merge/)**
*Group emails into accounts — classic DSU equivalence class.*

🔹 **[959. Regions Cut By Slashes](https://leetcode.com/problems/regions-cut-by-slashes/)**
*Advanced grid + DSU.*

---

### ✅ **Stage 4: Graph + MST combo**

---

🔹 **[1584. Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/)**
*Kruskal’s MST + DSU.*

🔹 **[1135. Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/)**
*MST using Union-Find.*

---

## ⚡ **What you should focus on learning**

| Concept                              | What to practice                  |
| ------------------------------------ | --------------------------------- |
| Writing `find` with path compression | Learn to flatten the tree         |
| Writing `union` with rank / size     | Keep the trees balanced           |
| Detecting connected components       | Count roots after unions          |
| Recognize DSU pattern                | “Merging groups” is your DSU clue |

---

## 🏁 **Suggested progression**

| Week | Focus                  | Problems        |
| ---- | ---------------------- | --------------- |
| 1    | Basic connectivity     | 547, 1319       |
| 2    | Island / grid DSU      | 200, 305        |
| 3    | Weighted / labeled DSU | 399, 721        |
| 4    | MST with DSU           | 1584, 1135, 959 |

---

## ✅ Complexity

* **`find` + `union` with path compression + union by rank:**
  Almost O(1) per operation (inverse Ackermann function, practically constant for n ≤ 10⁹)

* **Space:** O(N)

---

## ✨ Final Tip

✅ This category teaches:

* Dynamic grouping
* Efficient connectivity queries
* Graph thinking
* Real use of union-by-rank and path compression (which interviewers *love*)

---

👉 **If you'd like:**

* I can provide a **starter C++ template for DSU**
* Build a **custom LeetCode list**
* Create a **visual walk-through of path compression / union by size**

Would you like that? 🚀
