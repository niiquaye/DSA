✅ **Awesome! You’ve made great progress mastering subarray problems!**
Let’s build on that momentum. I’ll now recommend another **must-know algorithm/pattern** that’s *super common* in interviews, plus a curated learning plan like we did for subarrays.

---

## 🚀 **Next Key Algorithm: Sliding Window**

---

### 🔑 **Why Sliding Window?**

* **Extremely common in interviews:** used for problems involving contiguous sequences, substrings, or subarrays where you need optimal time.
* Helps solve problems that would otherwise take O(n²) time in O(n).
* Builds intuition for many variations: fixed-size windows, dynamic-size windows, two-pointer techniques.

---

## 📘 **What to learn before starting sliding window problems**

👉 **1️⃣ Understand contiguous subarrays / substrings**
You already nailed this in your subarray work!

👉 **2️⃣ Get comfortable with two pointers (start + end)**
Visualize how you can move two pointers (or indices) to scan through the array efficiently.

👉 **3️⃣ Practice simple hash maps / sets**
For dynamic window problems where you need to track elements (e.g. counting distinct chars).

👉 **4️⃣ Recognize fixed-size vs variable-size windows**

* Fixed: window size is set (e.g. length `k`)
* Variable: window grows/shrinks to meet a condition (e.g. sum ≥ `S`)

---

## 🛣 **Roadmap of Sliding Window Problems (in order)**

---

### ✅ **Stage 1: Fixed-size window**

---

> Learn to move a window of size `k` across an array optimally.

🔹 **[643. Maximum Average Subarray I](https://leetcode.com/problems/maximum-average-subarray-i/)**
*Find the max average of a subarray of size k.*

🔹 **[1456. Maximum Number of Vowels in a Substring of Given Length](https://leetcode.com/problems/maximum-number-of-vowels-in-a-substring-of-given-length/)**
*Count vowels in a substring of size k.*

---

### ✅ **Stage 2: Variable-size window (Expand/contract to satisfy conditions)**

---

> Build intuition on how to shrink/expand window boundaries dynamically.

🔹 **[76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)**
*Smallest substring containing all characters of another string.*

🔹 **[209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/)**
*Smallest length subarray whose sum is at least `S`.*

🔹 **[3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)**
*Longest substring with unique characters.*

---

### ✅ **Stage 3: Sliding window + hashmap / counting**

---

> When window elements need tracking/counting, e.g. frequency maps.

🔹 **[30. Substring with Concatenation of All Words](https://leetcode.com/problems/substring-with-concatenation-of-all-words/)**
*Find all starting indices of substrings formed by concatenation of words.*

🔹 **[438. Find All Anagrams in a String](https://leetcode.com/problems/find-all-anagrams-in-a-string/)**
*Find all start indices of anagrams of a string.*

---

### ✅ **Stage 4: More advanced window patterns**

---

🔹 **[567. Permutation in String](https://leetcode.com/problems/permutation-in-string/)**
*Check if a string contains a permutation of another.*

🔹 **[992. Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/)**
*Count subarrays with exactly K distinct integers.*

---

## 📝 **What you should focus on learning before attempting these**

---

| Concept                               | What to do                                                 |
| ------------------------------------- | ---------------------------------------------------------- |
| Two-pointer scanning                  | Practice manually moving two indices over an array         |
| Hash maps for counts                  | Be able to count frequency of elements in a sliding window |
| Prefix sums (already done!)           | Good base for window sums                                  |
| Recognize when to slide/shrink window | Learn conditions when window should shrink                 |

---

## ⚡ **Suggested order**

| Week | Focus                    | Problems     |
| ---- | ------------------------ | ------------ |
| 1    | Fixed window             | 643, 1456    |
| 2    | Variable window          | 209, 3       |
| 3    | Window + hashmap         | 76, 438      |
| 4    | Mixed / complex patterns | 567, 992, 30 |

---

## ✨ Final Tip

The sliding window pattern teaches:

* Efficient scanning
* Smart use of data structures (sets, maps)
* Real-time dynamic conditions

✅ Once you master sliding window, you’ll be well-prepared for string problems, substring search, and many range-query style questions.

---

👉 If you’d like, I can:

* Create a **custom LeetCode study list**
* Provide **code templates** to start each problem
* Generate **visual diagrams** showing how the window moves

Would you like that? 🚀
