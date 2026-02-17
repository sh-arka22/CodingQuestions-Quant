import math

def norm_cdf(x):
    """Cumulative distribution function for the standard normal distribution."""
    return (1.0 + math.erf(x / math.sqrt(2.0))) / 2.0

def calculate_power(n, alpha, observed_sr):
    """
    Checks if a sample size 'n' provides enough evidence to reject H0.
    In a simple Z-test context, we check if the SR is far enough from 0.
    """
    if n <= 0: return False
    
    # 1. Calculate the standard error for the given N
    # This represents the 'noise' in our measurement
    # Approximation: SE = sqrt((1 + SR^2/2) / n)
    se = math.sqrt((1 + (observed_sr**2) / 2) / n)
    
    # 2. Calculate the Z-score (how many standard errors away from zero we are)
    z_score = observed_sr / se
    
    # 3. Find the p-value (the probability this result happened by luck)
    # We use a one-tailed test because we care about POSITIVE Sharpe Ratios
    p_value = 1 - norm_cdf(z_score)
    
    # Check if p-value < significance level (alpha)
    return p_value < alpha

def find_minimum_n_iterative(observed_sr, alpha=0.05):
    """
    The Bottom-Up approach: Starting from the smallest possible sample (n=2),
    we iterate until our hypothesis test is rejected.
    """
    n = 2  # Minimum sample size to have a variance
    
    while True:
        # Step: Check if the current 'n' allows us to reject the null
        if calculate_power(n, alpha, observed_sr):
            return n
        
        # Incremental Step: Move to the next subproblem
        n += 1
        
        # Safety break for the explorer (prevents infinite loops)
        if n > 10000000:
            return None 

def find_minimum_n_binary_search(observed_sr, alpha=0.05):
    """
    Optimized approach using Binary Search.
    The Z-score increases monotonically with N.
    """
    low = 2
    high = 10000000 # Reasonable upper bound
    result = None
    
    while low <= high:
        mid = (low + high) // 2
        
        if calculate_power(mid, alpha, observed_sr):
            # We rejected H0, try to find a smaller N
            result = mid
            high = mid - 1
        else:
            # Need more samples
            low = mid + 1
            
    return result

if __name__ == "__main__":
    test_cases = [
        (0.5, 0.05),
        (0.1, 0.05),
        (1.0, 0.01),
        (2.0, 0.05)
    ]
    
    print(f"{'Sharpe':<10} {'Alpha':<10} {'Iterative N':<15} {'Binary Search N':<15}")
    print("-" * 55)
    
    for sr, alpha in test_cases:
        n_iter = find_minimum_n_iterative(sr, alpha)
        n_bin = find_minimum_n_binary_search(sr, alpha)
        
        print(f"{sr:<10.2f} {alpha:<10.2f} {n_iter:<15} {n_bin:<15}")
