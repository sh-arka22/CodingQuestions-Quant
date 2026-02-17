# 11. Sharpe Ratio Statistics

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

# Statistical Significance of Sharpe Ratios: A Deep Dive

This code answers a fundamental question in quantitative finance: **"How many observations do I need before I can be confident that my positive Sharpe Ratio isn't just luck?"**

## The Core Problem

Imagine you develop a trading strategy that shows a Sharpe Ratio of 0.5 over 10 days. Is this real skill, or just random noise? This code determines the **minimum sample size (N)** needed to statistically prove your strategy has genuine alpha.

## Part 1: The Normal CDF Function

```python
def norm_cdf(x):
    return (1.0 + math.erf(x / math.sqrt(2.0))) / 2.0
```

**What it does:** Calculates the cumulative probability for a standard normal distribution.

**Why we need it:** In hypothesis testing, we need to know "what's the probability of seeing a result this extreme by pure chance?" The CDF tells us what percentage of random outcomes fall below our observed value.

**Example:** `norm_cdf(1.645) ≈ 0.95` means 95% of random data falls below 1.645 standard deviations.

## Part 2: The Power Calculation (Heart of the Code)

```python
def calculate_power(n, alpha, observed_sr):
```

This function performs a **one-tailed Z-test** to determine if we can reject the null hypothesis.

### The Hypothesis Test Framework

**Null Hypothesis (H₀):** The strategy has no edge; true Sharpe Ratio = 0 (pure luck)  
**Alternative Hypothesis (H₁):** The strategy has a positive Sharpe Ratio > 0 (real skill)

### Step-by-Step Breakdown

#### Step 1: Calculate Standard Error
```python
se = math.sqrt((1 + (observed_sr**2) / 2) / n)
```

**What this represents:** The "noise" or uncertainty in our Sharpe Ratio measurement.

**The formula:** This is Bailey and López de Prado's approximation for the standard error of the Sharpe Ratio estimator:

SE(SR) ≈ √[(1 + SR²/2) / N]

**Intuition:**
- Larger N → smaller SE → more precise measurement
- Higher SR → slightly larger SE (more variable returns)
- The SR²/2 term accounts for the fact that high-Sharpe strategies tend to have more variable returns

**Example:** With SR = 0.5 and N = 100:
```
SE = sqrt((1 + 0.5²/2) / 100)
   = sqrt((1 + 0.125) / 100)
   = sqrt(1.125 / 100)
   = sqrt(0.01125)
   ≈ 0.106
```

#### Step 2: Calculate the Z-Score
```python
z_score = observed_sr / se
```

**What this means:** How many standard errors is our observed Sharpe Ratio away from zero?

**Intuition:** If your SR is 3 standard errors away from zero, it's extremely unlikely to be luck.

**Continuing our example:**
```
z_score = 0.5 / 0.106 ≈ 4.72
```

This is a **very strong** signal that the SR ≠ 0.

#### Step 3: Calculate the P-Value
```python
p_value = 1 - norm_cdf(z_score)
```

**What this represents:** The probability of observing a Sharpe Ratio this high (or higher) if the true SR were actually zero.

**Why one-tailed:** We use `1 - norm_cdf(z)` because we only care about **positive** deviations. We're asking: "What's the chance of getting an SR ≥ 0.5 by pure luck?"

**For our example:**
```
p_value = 1 - norm_cdf(4.72)
        ≈ 1 - 0.99999882
        ≈ 0.0000012
```

This means there's a 0.00012% chance this result is random luck!

#### Step 4: Reject or Fail to Reject
```python
return p_value < alpha
```

**Decision rule:**
- If p-value < α (typically 0.05), **REJECT H₀** → We have statistically significant evidence of skill
- If p-value ≥ α, **FAIL TO REJECT H₀** → Not enough evidence; could still be luck

## Part 3: Finding Minimum N (Iterative Approach)

```python
def find_minimum_n_iterative(observed_sr, alpha=0.05):
    n = 2
    while True:
        if calculate_power(n, alpha, observed_sr):
            return n
        n += 1
```

**The algorithm:** Brute force search from N=2 upward.

**Why it works:**
1. Start with the smallest possible sample (N=2)
2. Check if we can reject H₀ at this sample size
3. If yes → return N (we found the minimum!)
4. If no → increment N and try again

**Mathematical insight:** As N increases, the Z-score increases monotonically:
- Larger N → smaller SE
- Smaller SE → larger Z-score
- Larger Z-score → smaller p-value
- Eventually, p-value drops below α

**Example walkthrough** with SR = 0.5, α = 0.05:

| N   | SE    | Z-score | p-value | Reject H₀? |
|-----|-------|---------|---------|------------|
| 2   | 0.75  | 0.67    | 0.251   | No         |
| 10  | 0.335 | 1.49    | 0.068   | No         |
| 20  | 0.237 | 2.11    | 0.017   | **Yes**    |

The minimum N is **20**.

## Part 4: Binary Search Optimization

```python
def find_minimum_n_binary_search(observed_sr, alpha=0.05):
    low = 2
    high = 10000000
    result = None
    
    while low <= high:
        mid = (low + high) // 2
        
        if calculate_power(mid, alpha, observed_sr):
            result = mid  # This N works, try to find smaller
            high = mid - 1
        else:
            low = mid + 1  # Need larger N
            
    return result
```

**Why this works:** The "rejection region" is monotonic:
- If N=100 rejects H₀, then N=200, N=300, ... all reject H₀
- If N=50 fails to reject, then N=40, N=30, ... all fail to reject

This creates a **sorted structure** perfect for binary search.

**Efficiency comparison:**
- Iterative: O(N) — must check every value from 2 to answer
- Binary Search: O(log N) — halves the search space each iteration

For SR = 0.1 (weak signal), the iterative approach might check 1000+ values, while binary search checks only ~20.

## Practical Interpretation

### Example Results

Running the code:

```
Sharpe      Alpha      Iterative N     Binary Search N
-------------------------------------------------------
0.50        0.05       39              39
0.10        0.05       9608            9608
1.00        0.01       27              27
2.00        0.05       10              10
```

**Key insights:**

1. **SR = 0.5, α = 0.05:** Need 39 observations (e.g., 39 days of daily returns) to prove this isn't luck
   
2. **SR = 0.1, α = 0.05:** Need 9,608 observations! Weak signals require massive sample sizes
   - If using daily data, that's ~38 years of trading
   - This is why many "low-Sharpe" strategies can't be validated statistically

3. **SR = 1.0, α = 0.01:** Only need 27 observations even with stricter confidence (99%)
   - High-Sharpe strategies reveal themselves quickly

4. **SR = 2.0, α = 0.05:** Just 10 observations
   - Exceptionally strong signals don't need much data

## Why This Matters in Quant Finance

### Interview Context
This demonstrates understanding of:
- **Statistical rigor:** Not confusing backtest performance with statistical significance
- **Sample size planning:** Knowing how much data you need before making investment decisions
- **Type I errors:** The α parameter controls false positives (claiming skill when there is none)

### Real-World Application
- **Strategy validation:** Before allocating capital, ensure your backtest has sufficient sample size
- **Performance monitoring:** Know when live performance deviates significantly from expectations
- **Risk management:** Avoid over-trusting strategies with insufficient trading history

### The Hidden Danger
Many traders see a Sharpe Ratio of 0.5 over 10 days and think they've found gold. This code proves they need **4x more data** to make that claim with 95% confidence. This prevents costly mistakes from data mining and overfitting.

## Code Implementation

The python script implements both approaches.

[View Solution Code](./main.py)
