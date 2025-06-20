
## 🚀 **Subarray Algorithms Roadmap for LeetCode**

### 📘 **Stage 1: Fundamentals – Kadane’s Algorithm & Prefix Sum**

> **Goal:** Build strong foundations in subarray sums, products, and simple dynamic programming.

#### 🔹 Problems:

1. **[53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/)**

   * 🧠 *Algorithm*: Kadane’s Algorithm (greedy + local/global max)
   * 🔁 *Concepts to review*: Array traversal, dynamic max tracking

2. **[152. Maximum Product Subarray](https://leetcode.com/problems/maximum-product-subarray/)**

   * 🧠 *Algorithm*: Modified Kadane’s with min/max tracking
   * 🔁 *Review*: Sign handling, dynamic state tracking

3. **[1749. Maximum Absolute Sum of Any Subarray](https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/)**

   * 🧠 *Algorithm*: Run Kadane’s twice (max and min subarray sum)
   * 🔁 *Review*: Absolute values, dual tracking

4. **[560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/)**

   * 🧠 *Algorithm*: Prefix Sum + HashMap
   * 🔁 *Review*: Prefix sums, frequency maps

---

### 📙 **Stage 2: Intermediate – Lengths, Circular Arrays, and Constraints**

> **Goal:** Apply subarray ideas with more conditions like circular wrapping or size constraints.

#### 🔹 Problems:

5. **[1567. Maximum Length of Subarray With Positive Product](https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/)**

   * 🧠 *Algorithm*: Two-pass product sign tracking
   * 🔁 *Review*: Positive/negative transitions, max-length tracking

6. **[918. Maximum Sum Circular Subarray](https://leetcode.com/problems/maximum-sum-circular-subarray/)**

   * 🧠 *Algorithm*: Kadane’s + total sum - min subarray
   * 🔁 *Review*: Wraparound logic, dual Kadane

7. **[1248. Count Number of Nice Subarrays](https://leetcode.com/problems/count-number-of-nice-subarrays/)**

   * 🧠 *Algorithm*: Prefix sum or sliding window
   * 🔁 *Review*: Map-based counts, counting subarrays with conditions

8. **[325. Maximum Size Subarray Sum Equals k](https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/)**

   * 🧠 *Algorithm*: Prefix sum + earliest index tracking
   * 🔁 *Review*: Longest subarray variant, hash maps

---

### 📗 **Stage 3: Advanced – Optimization, Multiple Windows, Edge Cases**

> **Goal:** Tackle problems with multiple subarrays, more state, and edge case-heavy logic.

#### 🔹 Problems:

9. **[689. Maximum Sum of 3 Non-Overlapping Subarrays](https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/)**

   * 🧠 *Algorithm*: Sliding window + DP
   * 🔁 *Review*: Max value windows, storing index results

10. **[1052. Grumpy Bookstore Owner](https://leetcode.com/problems/grumpy-bookstore-owner/)**

* 🧠 *Algorithm*: Sliding window + greedy
* 🔁 *Review*: Optimize a fixed-size window to improve total result

---

### 📕 **Bonus – Related Concepts & Combo Patterns**

> For depth and mastery, explore subarray-related patterns in different disguises.

#### 🔹 Problems:

11. **[42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/)**

* 🧠 *Algorithm*: Two pointers + left/right max precomputation
* 🔁 *Review*: Thinking in subarrays bounded by constraints

12. **[123. Best Time to Buy and Sell Stock III](https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/)**

* 🧠 *Algorithm*: DP with up to two transactions
* 🔁 *Review*: Multiple subarray profits, stateful DP

---

## 📚 Algorithms to Review (Before/Along the Roadmap)

| Algorithm / Concept          | Use Case                                  | Where Needed       |
| ---------------------------- | ----------------------------------------- | ------------------ |
| **Kadane's Algorithm**       | Max subarray sum/product                  | 53, 152, 918, 1749 |
| **Prefix Sum**               | Fast subarray sum queries                 | 560, 325, 1248     |
| **Sliding Window**           | Constrained subarrays (size, count, etc.) | 1052, 689, 1248    |
| **Greedy Choices**           | Making optimal local decisions            | 53, 918, 1052      |
| **Dynamic Programming (1D)** | Multiple subarrays or transitions         | 123, 689           |
| **Hash Map with Prefix Sum** | Find sum or count of subarrays            | 560, 325           |
| **Min/Max Tracking**         | Max product, absolute values              | 152, 1749, 918     |
| **Two Pointers**             | Optimizing subarray boundaries            | 1248, 1052         |

---

## 🗓️ Suggested Practice Timeline (Optional)

| Week | Focus                         | Key Problems                  |
| ---- | ----------------------------- | ----------------------------- |
| 1    | Kadane & max/min subarray     | 53, 152, 1749                 |
| 2    | Prefix sums and maps          | 560, 325                      |
| 3    | Length-based and circular     | 1567, 918                     |
| 4    | Window and counting problems  | 1248, 1052                    |
| 5    | Multi-subarray & combo logic  | 689, 123                      |
| 6    | Mixed review & challenge week | Re-attempt all or unseen ones |

---

Let me know if you'd like this exported as a printable sheet, Notion planner, or if you want a curated **LeetCode study list link** to save your progress!

---

[Sub Array Problems With Prefix Sum + Hashmap](https://www.geeksforgeeks.org/dsa/longest-sub-array-sum-k/)