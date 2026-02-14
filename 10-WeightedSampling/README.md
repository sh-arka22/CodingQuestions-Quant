# 10. Tricky Interview Variations on Weighted Sampling

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

### Problem Statement

Weighted sampling is a standard problem: "Pick an item $i$ with probability $w_i / \sum w$."
However, interviewers often ask for variations where the standard approaches fail or are inefficient.

### Common Variations & Solutions

#### 1. Large Cumulative Sum (Precision Issues)
**Problem**: Adding small weights to a huge total causes floating point precision loss using standard `double`.
**Solution**:
- **Kahan Summation**: Track lost low-order bits.
- **Tree-Based Sampling**: Sum only $O(\log N)$ values at a time.

#### 2. Weighted Sampling *Without* Replacement
**Problem**: Once an item is picked, it cannot be picked again. Standard prefix sum requires $O(N)$ update per pick.
**Solution**:
- **Efraimidis-Spirakis Algorithm**: Generate key $k_i = u_i^{(1/w_i)}$ and pick top $k$. elegant and efficient.

#### 3. Distributed/Streaming Data (Reservoir Sampling)
**Problem**: Stream of items, unknown $N$, pick 1 (or $k$) items with weighted probability.
**Solution**:
- **A-Res Algorithm**: Keep item with max key $k_i = u_i^{(1/w_i)}$.

#### 4. Many Queries, Changing Weights
**Problem**: Weights update frequently. Prefix sum is $O(N)$ update.
**Solution**:
- **Segment Tree**: $O(\log N)$ update, $O(\log N)$ query.

#### 5. High Frequency Sampling (Static Weights)
**Problem**: Need $O(1)$ sampling time.
**Solution**:
- **Alias Method**: Preprocess in $O(N)$, sample in $O(1)$. Uses a table to "top up" probability buckets.

### Summary Table

| Problem Constraint | Best Algorithm | Complexity |
| :--- | :--- | :--- |
| **Standard (Static)** | Prefix Sum + Binary Search | $O(N)$ setup, $O(\log N)$ query |
| **High Frequency Sampling** | Alias Method | $O(N)$ setup, $O(1)$ query |
| **Dynamic Weights** | Segment Tree (Sum Tree) | $O(\log N)$ update, $O(\log N)$ query |
| **Stream / Unknown N** | A-Res (Key-based Reservoir) | $O(N)$ time, $O(1)$ space |
| **Without Replacement** | Efraimidis-Spirakis (Keys) | $O(N \log k)$ time |

[View C++ Solutions](./main.cpp)
