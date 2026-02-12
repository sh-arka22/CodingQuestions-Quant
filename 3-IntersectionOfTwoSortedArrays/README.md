# 3. Intersection of Two Sorted Arrays

### Problem Explanation

Given two sorted arrays `arr1` and `arr2`, return a new array containing the **intersection** of these two arrays. The intersection should contain all elements that appear in both arrays, including duplicates (i.e., if a value appears `min(x, y)` times in the intersection where `x` is count in `arr1` and `y` is count in `arr2`).

**Example:**
```python
arr1 = [1, 2, 2, 1]
arr2 = [2, 2]
Output: [2, 2]

arr1 = [4, 9, 5]
arr2 = [9, 4, 9, 8, 4]
Output: [4, 9] (or [9, 4])
```

### Solutions & Complexity Analysis

There are multiple ways to solve this, but since the arrays are **sorted**, we can optimize specifically for that property.

#### 1. Two Pointers Approach (Standard)
Use two pointers `i` and `j` to traverse `arr1` and `arr2`.
- If `arr1[i] < arr2[j]`, increment `i`.
- If `arr1[i] > arr2[j]`, increment `j`.
- If `arr1[i] == arr2[j]`, add to result and increment both.

- **Time Complexity:** $O(m + n)$ where $m$ and $n$ are lengths of the arrays.
- **Space Complexity:** $O(1)$ (ignoring output space).

#### 2. Binary Search Approach (Optimized for $m \ll n$)
If one array is significantly smaller than the other (say `len(arr1) = m` and `len(arr2) = n` with $m \ll n$), we can iterate through the smaller array and perform a binary search in the larger array.

**Key Optimizations in Code:**
1.  **Range Check:** Before searching, check if the value is within the range `[arr2_min, arr2_max]`.
2.  **Skipping Duplicates:** If we find a match, we can skip consecutive duplicates to avoid redundant searches/comparisons.
3.  **Restricted Binary Search:** Instead of searching the entire array `arr2` every time, we can search only in the remaining valid range (from the index of the last found element to the end).
4.  **Exponential Search:** If elements are clustered at the beginning, exponential search can find the search bounds faster than standard binary search.

- **Time Complexity:** $O(m \log n)$ (basic binary search) or better with optimizations.
- **Space Complexity:** $O(1)$.

### Code Implementation

```python
def intersection_optimized(arr1, arr2):
    """
    Optimized for m << n case.
    Time: O(m log n) where m = min(len(arr1), len(arr2))
    Space: O(1) excluding output
    """
    # ... (See main.py for full implementation)
```

[View Solution Code](./main.py)
