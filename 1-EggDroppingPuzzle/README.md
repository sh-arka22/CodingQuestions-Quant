# 1. Egg Dropping Puzzle

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

### Problem Explanation

Let me explain this classic dynamic programming problem as an interviewer would present it.

### Problem Statement

You have **k eggs** and a building with **n floors** (numbered 1 to n). You need to determine the **highest safe floor** from which an egg can be dropped without breaking.

**Key rules:**
- If an egg breaks when dropped from floor F, it will break from any floor above F
- If an egg survives a drop from floor F, it will survive any floor below F
- A broken egg must be discarded; you cannot reuse it
- A surviving egg can be reused in subsequent drops

**Goal:** Find the **minimum number of trials (drops)** needed in the **worst case** to determine the highest safe floor with certainty.

### Example: The Classic Two-Egg Problem (k=2, n=100)

Let's say you have 2 eggs and a 100-floor building.

**Naive approach:** Start from floor 1, go up sequentially
- Worst case: 100 drops (if safe floor is 100 or eggs never break)

**Better approach:** Use the first egg strategically
- Drop first egg at intervals (say every 10 floors: 10, 20, 30...)
- When it breaks, use second egg to test floors in between
- Example: First egg breaks at floor 30 -> test 21, 22, 23... with second egg
- Worst case: 10 + 9 = 19 drops

**Optimal approach:** Use variable intervals
- Drop from floors 14, 27, 39, 50, 60, 69, 77, 84, 90, 95, 99, 100
- This balances the worst case to exactly **14 drops**

### Solutions & Complexity Analysis

We can solve this problem using Dynamic Programming. Let `dp[i][j]` represent the minimum number of trials needed for `i` eggs and `j` floors.

#### 1. Recursive Approach
A simple recursive solution tries every floor `x` from 1 to `j` and takes the maximum of two cases (egg breaks or doesn't break).
- **Time Complexity:** $O(2^n)$ - Exponential without memoization due to overlapping subproblems.
- **Space Complexity:** $O(n)$ - Stack depth for recursion.

#### 2. Dynamic Programming (Iterative)
We fill a DP table where `dp[i][j] = 1 + min(max(dp[i-1][x-1], dp[i][j-x]))` for all `x` in `1...j`.
- **Time Complexity:** $O(k \cdot n^2)$ - We have $k \cdot n$ states, and computing each state takes $O(n)$ time.
- **Space Complexity:** $O(k \cdot n)$ - To store the DP table.

#### 3. DP with Binary Search Optimization
Notice that `dp[i-1][x-1]` is increasing with `x`, and `dp[i][j-x]` is decreasing with `x`. The function `max(increasing, decreasing)` is convex. We can find the minimum point using Binary Search instead of a linear scan.
- **Time Complexity:** $O(k \cdot n \log n)$ - Computing each state now takes $O(\log n)$ time.
- **Space Complexity:** $O(k \cdot n)$ - To store the DP table.

### What I'm Looking For As an Interviewer

1. **Understanding**: Can you explain the problem back to me? What makes this a DP problem?

2. **Approach**: What are the states? What decisions do you make at each step?

3. **Recurrence relation**: How do you express the minimum trials in terms of subproblems?

4. **Complexity**: Time and space complexity of your solution
