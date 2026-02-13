# 5. Integer Partition

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

### Problem Statement

Write a **recursive function** to compute the **number of partitions** of a positive integer **n**.

A **partition** of n is a way of writing n as a **sum of positive integers**, where the **order doesn't matter**.

**Key rules:**
- Only use positive integers (1, 2, 3, ...)
- Order doesn't matter: 3+1 and 1+3 are the **same** partition
- The number itself counts as a partition

### Examples

#### Example 1: n = 4
```
Partitions of 4:
1. 4
2. 3 + 1
3. 2 + 2
4. 2 + 1 + 1
5. 1 + 1 + 1 + 1

Answer: 5 partitions
```

#### Example 2: n = 5
```
Partitions of 5:
1. 5
2. 4 + 1
3. 3 + 2
4. 3 + 1 + 1
5. 2 + 2 + 1
6. 2 + 1 + 1 + 1
7. 1 + 1 + 1 + 1 + 1

Answer: 7 partitions
```

### Key Insight: The Recurrence Relation

To avoid duplicates, we use a clever trick:

**Define:** `p(n, m)` = number of partitions of `n` using integers **≤ m**

### The Recurrence
```
p(n, m) = number of partitions of n using integers ≤ m

Two cases:
1. Partitions that DON'T use m: p(n, m-1)
2. Partitions that DO use m: p(n-m, m)

Therefore:
p(n, m) = p(n, m-1) + p(n-m, m)
```

### Base Cases

```
1. p(0, m) = 1 for all m ≥ 0 (empty sum)
2. p(n, 0) = 0 for n > 0 (can't partition with 0)
3. p(n, m) = p(n, n) for m > n
```

### Solutions & Complexity Analysis

#### Approach 1: Pure Recursion
Simple recursive implementation without memoization.
- **Time Complexity:** $O(2^n)$ - Too slow
- **Space Complexity:** $O(n)$ - Stack depth

#### Approach 2: Recursion with Memoization
Add memoization to cache computed values.
- **Time Complexity:** $O(n^2)$
- **Space Complexity:** $O(n^2)$

#### Approach 3: Bottom-Up DP
Iterative dynamic programming solution.
- **Time Complexity:** $O(n^2)$
- **Space Complexity:** $O(n^2)$

#### Approach 4: Space-Optimized DP
Use 1D array instead of 2D table.
- **Time Complexity:** $O(n^2)$
- **Space Complexity:** $O(n)$ - Best space usage

### Interview Questions - Answered

**Q1: Why do we need the parameter m (max value)?**

The parameter `m` is crucial to avoid counting duplicate partitions. Without it, we would count the same partition multiple times in different orders. For example, for n=4, we might count both "3+1" and "1+3" as separate partitions, when they should be the same.

By restricting partitions to use only numbers ≤ m, we enforce an implicit ordering: we consider larger numbers first, then smaller ones. This ensures each unique partition is counted exactly once.

**Q2: How does p(n, m-1) + p(n-m, m) avoid counting duplicates?**

This recurrence divides all partitions of n using numbers ≤ m into two **mutually exclusive** groups:

1. **p(n, m-1)**: Partitions that don't use the number m at all (only use numbers < m)
2. **p(n-m, m)**: Partitions that use m at least once (after using m once, we have n-m remaining to partition, still allowing ≤ m)

Since these two cases don't overlap (a partition either uses m or doesn't), and together they cover all possibilities, we get the correct count without duplicates.

**Q3: What would be the first few values in the DP table for n=5?**

```
dp[i][j] = partitions of i using numbers ≤ j

    j:  0   1   2   3   4   5
i:
0       1   1   1   1   1   1
1       0   1   1   1   1   1
2       0   1   2   2   2   2
3       0   1   2   3   3   3
4       0   1   3   4   5   5
5       0   1   3   5   6   7

Answer: dp[5][5] = 7
```

[View Solution Code](./main.py)
