# 14. Eigenvalues of a Special Matrix

### Problem Statement

Find the eigenvalues of an n x n matrix `A` with `n` on the diagonal and `1` everywhere else.

The matrix `A` has the following structure:

```
| n 1 1 ... 1 |
| 1 n 1 ... 1 |
| 1 1 n ... 1 |
| . . . ... . |
| 1 1 1 ... n |
```

### Solution

The solution involves a common linear algebra trick: decomposing the matrix `A` into simpler, more structured matrices.

#### Step 1: Decompose the Matrix

We can express the matrix `A` as the sum of two matrices:

1.  A diagonal matrix, which is `(n-1)` times the identity matrix `I`.
2.  A matrix of all ones, which we will call `J`.

So, the decomposition is:

**A = (n-1)I + J**

where `I` is the n x n identity matrix and `J` is the n x n matrix of all ones.

```
      | n 1 ... 1 |   | n-1 0 ... 0 |   | 1 1 ... 1 |
      | 1 n ... 1 |   | 0 n-1 ... 0 |   | 1 1 ... 1 |
A   = | . . ... . | = | . .  ...  . | + | . . ... . |
      | 1 1 ... n |   | 0 0 ... n-1 |   | 1 1 ... 1 |
```

#### Step 2: Find the Eigenvalues of J

The matrix `J` (the matrix of all ones) has a very special structure.
-   It has a **rank of 1**, because every row is a linear combination of every other row (in fact, all rows are identical).
-   A fundamental theorem of linear algebra states that for an n x n matrix, if the rank is `r`, then there will be `n-r` eigenvalues of 0.
-   Since the rank of `J` is 1, it must have **n-1 eigenvalues equal to 0**.

To find the one non-zero eigenvalue, we can consider the vector `v = [1, 1, ..., 1]^T`.
When we multiply `J` by `v`, each row of `J` (which is all ones) is multiplied by the vector `v`, resulting in the sum of the elements of `v`, which is `n`.

`Jv = [n, n, ..., n]^T = n * [1, 1, ..., 1]^T = n * v`

This shows that **n is an eigenvalue of J**, with the corresponding eigenvector being the vector of all ones.

So, the eigenvalues of `J` are:
-   `n` (with multiplicity 1)
-   `0` (with multiplicity n-1)

#### Step 3: Relate the Eigenvalues of A and J

Now, we can use the relationship `A = (n-1)I + J` to find the eigenvalues of `A`.

Let `v` be an eigenvector of `J` with eigenvalue `λ`. By definition, `Jv = λv`.

Let's apply the matrix `A` to the eigenvector `v`:

`Av = ((n-1)I + J)v`
`Av = (n-1)Iv + Jv`
`Av = (n-1)v + λv`
`Av = (n-1 + λ)v`

This shows that if `λ` is an eigenvalue of `J`, then `(n-1 + λ)` is an eigenvalue of `A`, with the same eigenvector `v`.

#### Step 4: Calculate the Eigenvalues of A

We can now find the eigenvalues of `A` by using the eigenvalues of `J` that we found in Step 2:

1.  For the **n-1 eigenvalues of J that are 0**:
    The corresponding eigenvalues of `A` are `(n-1) + 0 = n-1`.

2.  For the **one eigenvalue of J that is n**:
    The corresponding eigenvalue of `A` is `(n-1) + n = 2n-1`.

### Conclusion

The eigenvalues of the matrix `A` are:
-   **n-1** (with a multiplicity of n-1)
-   **2n-1** (with a multiplicity of 1)
