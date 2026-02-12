def intersection_optimized(arr1, arr2):
    """
    Optimized for m << n case.
    Time: O(m log n) where m = min(len(arr1), len(arr2))
    Space: O(1) excluding output
    """
    # Ensure arr1 is the smaller array
    if len(arr1) > len(arr2):
        arr1, arr2 = arr2, arr1
    
    m, n = len(arr1), len(arr2)
    
    # Edge case: if small array is empty
    if m == 0:
        return []
    
    result = []
    i = 0
    
    # Optimization 1: Range check before binary search
    arr2_min, arr2_max = arr2[0], arr2[-1]
    
    while i < m:
        current = arr1[i]
        
        # Optimization 2: Skip if out of range
        if current < arr2_min or current > arr2_max:
            while i < m and arr1[i] == current:
                i += 1
            continue
        
        # Optimization 3: Use binary search with range bounds
        first_idx = binary_search_first_in_range(
            arr2, current, 0, n - 1
        )
        
        if first_idx != -1:
            # Count occurrences efficiently
            count1 = count_occurrences(arr1, current, i)
            count2 = count_occurrences_from(arr2, current, first_idx)
            
            min_count = min(count1, count2)
            result.extend([current] * min_count)
            i += count1  # Skip past all occurrences
        else:
            # Skip this value
            while i < m and arr1[i] == current:
                i += 1
    
    return result


def binary_search_first_in_range(arr, target, left, right):
    """
    Binary search for first occurrence within a range.
    Returns index or -1 if not found.
    """
    result = -1
    
    while left <= right:
        mid = left + (right - left) // 2
        
        if arr[mid] == target:
            result = mid
            right = mid - 1  # Keep searching left
        elif arr[mid] < target:
            left = mid + 1
        else:
            right = mid - 1
    
    return result


def count_occurrences(arr, value, start_idx):
    """Count consecutive occurrences starting from start_idx."""
    count = 0
    while start_idx < len(arr) and arr[start_idx] == value:
        count += 1
        start_idx += 1
    return count


def count_occurrences_from(arr, value, start_idx):
    """Count consecutive occurrences starting from start_idx."""
    count = 0
    while start_idx < len(arr) and arr[start_idx] == value:
        count += 1
        start_idx += 1
    return count


# Optimization 4: Use exponential search to find range
# When to use: Elements in small array are clustered near the beginning of large array.
def exponential_then_binary_search(arr, target, start=0):
    """
    Use exponential search to find range, then binary search.
    Useful when target is near the start.
    
    Time: O(log k) where k is position of target
    """
    if start >= len(arr):
        return -1
    
    # Check first element
    if arr[start] == target:
        return start
    if arr[start] > target:
        return -1
    
    # Exponential search to find range
    i = 1
    while start + i < len(arr) and arr[start + i] < target:
        i *= 2
    
    # Binary search in range [start + i//2, min(start + i, n-1)]
    left = start + i // 2
    right = min(start + i, len(arr) - 1)
    
    return binary_search_first_in_range(arr, target, left, right)
