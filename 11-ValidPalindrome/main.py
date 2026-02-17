import re

def isPalindrome(s: str) -> bool:
    """
    Determines if a string is a palindrome, considering only alphanumeric characters and ignoring cases.

    Args:
        s: The input string.

    Returns:
        True if the string is a palindrome, False otherwise.
    """
    filtered_chars = []
    for char in s:
        if char.isalnum():
            filtered_chars.append(char.lower())
    
    filtered_s = "".join(filtered_chars)
    
    left = 0
    right = len(filtered_s) - 1
    
    while left < right:
        if filtered_s[left] != filtered_s[right]:
            return False
        left += 1
        right -= 1
            
    return True

# Test Cases
if __name__ == "__main__":
    test_cases = [
        ("A man, a plan, a canal: Panama", True),
        ("race a car", False),
        (" ", True),
        ("Madam, in Eden, I'm Adam", True),
        ("hello", False),
        ("Live on no evil", True),
        ("0P", False)
    ]

    for s, expected in test_cases:
        result = isPalindrome(s)
        print(f"Input: \"{s}\", Expected: {expected}, Got: {result} -> {'Passed' if result == expected else 'Failed'}")
        assert result == expected, f"Test failed for input: \"{s}\""

    print("\nAll test cases passed!")
