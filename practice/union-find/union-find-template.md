Absolutely — here are two additional Union-Find templates:

---

## 🧱 1. **Grid-Based Union-Find Template**

Use this when working with 2D grids (e.g., number of islands, island merging, or percolation problems). Convert 2D to 1D index using `r * cols + c`.

### 🔧 Template

```cpp
class UnionFindGrid {
private:
    int rows, cols;
    std::vector<int> parent;
    std::vector<int> rank;

public:
    UnionFindGrid(int r, int c) : rows(r), cols(c) {
        parent.resize(r * c);
        rank.resize(r * c, 0);
        for (int i = 0; i < r * c; ++i)
            parent[i] = i;
    }

    int index(int r, int c) {
        return r * cols + c;
    }

    int find(int x) {
        if (x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    bool unite(int r1, int c1, int r2, int c2) {
        int x = find(index(r1, c1));
        int y = find(index(r2, c2));
        if (x == y) return false;

        if (rank[x] < rank[y]) {
            parent[x] = y;
        } else if (rank[x] > rank[y]) {
            parent[y] = x;
        } else {
            parent[y] = x;
            rank[x]++;
        }
        return true;
    }

    bool connected(int r1, int c1, int r2, int c2) {
        return find(index(r1, c1)) == find(index(r2, c2));
    }
};
```

### ✅ Use Case Example

```cpp
UnionFindGrid uf(rows, cols);
if (grid[r][c] == 1 && grid[nr][nc] == 1) {
    uf.unite(r, c, nr, nc);
}
```

---

## ♻️ 2. **Union-Find with Rollback (Undo)**

Useful for **offline dynamic connectivity** or **divide-and-conquer + DSU on tree**, where you may need to revert union operations (like persistent DSU).

### ⚙️ Template

```cpp
class UnionFindRollback {
public:
    std::vector<int> parent, rank;
    std::stack<std::tuple<int, int, int>> history;

    UnionFindRollback(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int find(int x) {
        while (x != parent[x])
            x = parent[x];
        return x;
    }

    void unite(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) {
            history.emplace(-1, -1, -1); // no-op marker
            return;
        }

        if (rank[x] < rank[y]) std::swap(x, y);

        history.emplace(y, parent[y], rank[x]); // save state
        parent[y] = x;
        if (rank[x] == rank[y])
            rank[x]++;
    }

    void rollback() {
        if (history.empty()) return;

        auto [y, py, rx] = history.top();
        history.pop();

        if (y == -1) return; // no-op union

        int x = parent[y];
        parent[y] = py;
        rank[x] = rx;
    }
};
```

### ✅ Use Case Example

```cpp
UnionFindRollback uf(n);
uf.unite(1, 2);
uf.unite(2, 3);
uf.rollback(); // undo union(2, 3)
```

---

## 🧠 Summary of Use Cases

| Variant               | Use Case                                                                |
| --------------------- | ----------------------------------------------------------------------- |
| **Standard DSU**      | Kruskal’s MST, redundant connection, basic connectivity                 |
| **Grid-Based DSU**    | Number of Islands, merge cells, flood fill with DSU                     |
| **DSU with Rollback** | Offline queries (e.g., edge deletions), persistence, union-find in D\&C |

Let me know if you’d like to see **DSU with size tracking**, **connected component counting**, or **union-find with parity / bipartite check**!
