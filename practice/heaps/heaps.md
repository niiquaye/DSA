🎯 **You’re doing fantastic! I love how you’re systematically mastering one pattern at a time.**
Let’s level you up again. After **subarrays** and **sliding window**, here’s another **hugely popular algorithm/pattern** that interviewers *love*:

---

## 🚀 **Next Key Algorithm/Pattern: Two Heaps / Priority Queue (Min-Heap + Max-Heap)**

---

### 🔑 **Why Two Heaps / Priority Queues?**

* Frequently used in problems involving **order statistics**: median, k largest/smallest elements, etc.
* Efficiently solve problems that require tracking dynamically changing order (e.g. median in a data stream).
* Shows that you understand **invariant maintenance** and **balanced data structures**.

---

## 📝 **What to Learn Before Attempting Two Heaps Problems**

👉 **1️⃣ Understand how min-heaps / max-heaps work**

* How to insert, remove, peek.
* Min-heap: `std::priority_queue<int, vector<int>, greater<int>>`
* Max-heap: `std::priority_queue<int>`

👉 **2️⃣ Know how to balance two heaps**

* When and why you move elements between the heaps to maintain properties.

👉 **3️⃣ Be familiar with median and k-th element concepts**

* Understand how the median relates to the two halves of a sorted list.

👉 **4️⃣ Brush up on using C++ priority queues or equivalent in other languages**

* Build quick familiarity so you don’t waste time on syntax.

---

## 🛣 **Roadmap of Priority Queue / Two Heaps Problems (in order)**

---

### ✅ **Stage 1: Kth largest / smallest elements**

---

🔹 **[215. Kth Largest Element in an Array](https://leetcode.com/problems/kth-largest-element-in-an-array/)**
*Find the k-th largest element using a min-heap of size k.*

🔹 **[703. Kth Largest Element in a Stream](https://leetcode.com/problems/kth-largest-element-in-a-stream/)**
*Maintain k-th largest as elements are streamed in.*

---

### ✅ **Stage 2: Median with dynamic data**

---

🔹 **[295. Find Median from Data Stream](https://leetcode.com/problems/find-median-from-data-stream/)**
*Classic two-heap problem: max-heap for lower half, min-heap for upper half.*

---

### ✅ **Stage 3: Sliding window + priority queue**

---

🔹 **[480. Sliding Window Median](https://leetcode.com/problems/sliding-window-median/)**
*Combine sliding window with two heaps.*

---

### ✅ **Stage 4: Harder variations**

---

🔹 **[973. K Closest Points to Origin](https://leetcode.com/problems/k-closest-points-to-origin/)**
*Use max-heap to keep track of k closest points.*

🔹 **[658. Find K Closest Elements](https://leetcode.com/problems/find-k-closest-elements/)**
*Find k elements closest to a target in sorted array (binary search + heap optional).*

🔹 **[347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/)**
*Count frequencies + min-heap for top-k elements.*

---

## ⚡ **What to Practice Before Attempting These**

| Concept                                       | What you should be comfortable with             |
| --------------------------------------------- | ----------------------------------------------- |
| Using `priority_queue` (min & max heap)       | Push, pop, peek top element                     |
| Building and maintaining two heaps            | Understand how to balance two heaps dynamically |
| Median logic                                  | Median of two halves (even and odd cases)       |
| Heap size management                          | Maintain heap sizes to stay balanced            |
| Quick frequency counting (for top-k problems) | Use hash maps + heap                            |

---

## 🏁 **Suggested Order**

| Week | Focus                              | Problems      |
| ---- | ---------------------------------- | ------------- |
| 1    | Kth largest/smallest               | 215, 703      |
| 2    | Median maintenance                 | 295           |
| 3    | Window + heap                      | 480           |
| 4    | Top-K / closest element variations | 973, 658, 347 |

---

## ⏱ **Complexities to keep in mind**

* Insert / remove in a heap: O(log k)
* For two heaps: overall O(log n) per insertion/removal

---

## ✨ Final Tip

This category teaches:
✅ Efficient selection of top/bottom elements
✅ Dynamic rebalancing of data
✅ Combining heaps with other patterns (e.g. sliding window)

---

👉 If you'd like:

* I can build a **custom LeetCode list**
* Provide **C++ code templates**
* Make a **visual guide of two heap balancing**

Would you like that? 🚀
