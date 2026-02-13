def count_partitions(n: int) -> int:
    """
    Count the number of integer partitions of n using bottom-up DP.
    
    Time: O(n²)
    Space: O(n²)
    
    Args:
        n: The positive integer to partition
        
    Returns:
        Number of partitions of n
    """
    if n <= 0:
        return 0 if n < 0 else 1
    
    # dp[i][j] = number of partitions of i using integers ≤ j
    dp = [[0] * (n + 1) for _ in range(n + 1)]
    
    # Base case: empty partition
    for j in range(n + 1):
        dp[0][j] = 1
    
    # Fill the table
    for i in range(1, n + 1):
        for j in range(1, n + 1):
            # Case 1: don't use j
            dp[i][j] = dp[i][j - 1] if j > 0 else 0
            
            # Case 2: use j at least once
            if i >= j:
                dp[i][j] += dp[i - j][j]
    
    return dp[n][n]


def count_partitions_optimized(n: int) -> int:
    """
    Space-optimized version using 1D array.
    
    Time: O(n²)
    Space: O(n)
    
    Args:
        n: The positive integer to partition
        
    Returns:
        Number of partitions of n
    """
    if n <= 0:
        return 0 if n < 0 else 1
    
    # dp[i] = number of partitions of i
    dp = [0] * (n + 1)
    dp[0] = 1  # Base case
    
    # For each possible part size
    for part in range(1, n + 1):
        # Update all values that can use this part
        for total in range(part, n + 1):
            dp[total] += dp[total - part]
    
    return dp[n]


def count_partitions_recursive(n: int, m: int = None) -> int:
    """
    Recursive solution with memoization.
    
    Args:
        n: The number to partition
        m: Maximum value allowed in partition (defaults to n)
        
    Returns:
        Number of partitions of n using integers ≤ m
    """
    if m is None:
        m = n
    
    memo = {}
    
    def helper(n: int, m: int) -> int:
        if (n, m) in memo:
            return memo[(n, m)]
        
        # Base cases
        if n == 0:
            return 1
        if n < 0 or m == 0:
            return 0
        
        # Recurrence: don't use m + use m
        result = helper(n, m - 1) + helper(n - m, m)
        memo[(n, m)] = result
        return result
    
    return helper(n, m)


if __name__ == "__main__":
    test_cases = [
        (1, 1),
        (2, 2),
        (3, 3),
        (4, 5),
        (5, 7),
        (6, 11),
        (7, 15),
        (10, 42),
    ]
    
    print("Testing Integer Partition Implementations:")
    print("=" * 60)
    
    for n, expected in test_cases:
        result_dp = count_partitions(n)
        result_opt = count_partitions_optimized(n)
        result_rec = count_partitions_recursive(n)
        
        status = "✓" if result_dp == expected else "✗"
        match = "✓" if result_dp == result_opt == result_rec else "✗"
        
        print(f"{status} p({n:2d}) = {result_dp:3d} | Optimized: {result_opt:3d} | Recursive: {result_rec:3d} | Expected: {expected:3d} {match}")
