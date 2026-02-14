# 8. Expected Draws to Get an Ace

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

### Problem Statement

You have a **standard deck of 52 cards** with **4 Aces**.

**Question:** What is the **expected number of draws** (without replacement) until you draw your **first Ace**?

---

### Solutions & Approaches

#### 1. Symmetry Argument (The "Quant" Way)
Imagine the 48 non-Ace cards are placed in a row. Now, we place the 4 Aces at random positions. These 4 Aces divide the 48 non-Ace cards into **5 gaps**:
- Gap 1: Before Ace 1
- Gap 2: Between Ace 1 and Ace 2
- Gap 3: Between Ace 2 and Ace 3
- Gap 4: Between Ace 3 and Ace 4
- Gap 5: After Ace 4

By symmetry, each gap is expected to have the same number of cards: $48 / 5 = 9.6$.
The first Ace is found immediately after the first gap.
**Expected Draws = 9.6 + 1 = 10.6**

#### 2. The General Formula
For a deck of $N$ cards with $K$ target cards:
$$E[X] = \frac{N + 1}{K + 1}$$
For $N=52$ and $K=4$:
$$E[X] = \frac{52 + 1}{4 + 1} = \frac{53}{5} = \mathbf{10.6}$$

#### 3. Recursive Approach
Let $E_n$ be the expected draws with $n$ non-target cards and a fixed $K=4$ targets.
$$E_n = 1 + \frac{n}{n+4} \cdot E_{n-1}$$
Starting from $E_0 = 1$, we can iterate up to $E_{48}$.

---

### Interview Questions - Answered

**Q1: Quick Check - If there were only 1 Ace in the deck, what's the expected number of draws?**
Using the formula: $E[X] = (52+1)/(1+1) = 53/2 = \mathbf{26.5}$.
Using symmetry: The 51 non-Aces are divided into 2 gaps (before and after the Ace). Average gap is $51/2 = 25.5$. Position of Ace is $25.5 + 1 = 26.5$.

**Q2: Generalization - Deck has N cards total, K are Aces. What's the formula?**
$$E[X] = \frac{N + 1}{K + 1}$$

**Q3: Related Problem - What's the expected number of draws to get all 4 Aces?**
Using the symmetry argument, we need to pass 4 gaps and the 4 Aces themselves.
Expected position of 4th Ace = $4 \times (\text{Average Gap}) + 4$
Expected Draws = $4 \times (48/5) + 4 = 38.4 + 4 = \mathbf{42.4}$.

**Q4: Variance - What's the variance of the number of draws to the first Ace?**
The number of draws follows a Negative Hypergeometric distribution. For $r=1$ success:
$$Var(X) = \frac{(N+1)(N-K)(K)}{(K+1)^2(K+2)}$$
For $N=52, K=4$:
$$Var(X) = \frac{(53)(48)(4)}{(25)(6)} = \frac{53 \times 8 \times 4}{25} = \frac{1696}{25} = \mathbf{67.84}$$

**Q5: Conditional - Given that the first Ace appears after position 20, what's the expected position?**
If the first 20 cards are not Aces, we have a new problem with $52 - 20 = 32$ cards remaining and 4 Aces still in the deck.
Expected additional draws = $(32+1)/(4+1) = 33/5 = 6.6$.
Total expected position = $20 + 6.6 = \mathbf{26.6}$.

---

### Complexity Analysis

| Approach | Time | Space | Notes |
|----------|------|-------|-------|
| Symmetry | $O(1)$ | $O(1)$ | Most elegant for interviews |
| Recursive | $O(N)$ | $O(1)$ | Good for checking small values |
| Simulation | $O(M \cdot N)$ | $O(N)$ | Useful for verification |

[View Solution Code](./main.py)
