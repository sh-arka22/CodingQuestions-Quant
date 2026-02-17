# 11. Valid Palindrome

### Problem Statement

Given a string `s`, determine if it is a palindrome, considering only alphanumeric characters and ignoring cases.

A **palindrome** is a sequence that reads the same forwards and backward.

### Examples

**Example 1:**
Input: `s = "A man, a plan, a canal: Panama"`
Output: `true`
Explanation: "amanaplanacanalpanama" is a palindrome.

**Example 2:**
Input: `s = "race a car"`
Output: `false`
Explanation: "raceacar" is not a palindrome.

**Example 3:**
Input: `s = " "`
Output: `true`
Explanation: Empty string is considered a palindrome.

### Approaches

#### 1. Two Pointers

This approach involves filtering the string first to keep only alphanumeric characters and converting it to lowercase. Then, use two pointers, one starting from the beginning and the other from the end, moving towards the center. Compare characters at each pointer. If they don't match, it's not a palindrome.

**Algorithm:**
1.  Initialize an empty string or list to store filtered characters.
2.  Iterate through the input string:
    *   If a character is alphanumeric, convert it to lowercase and add it to the filtered collection.
3.  Initialize `left` pointer to 0 and `right` pointer to `len(filtered_string) - 1`.
4.  While `left < right`:
    *   If `filtered_string[left] != filtered_string[right]`, return `false`.
    *   Increment `left` and decrement `right`.
5.  If the loop completes, return `true`.

**Time Complexity:** O(N), where N is the length of the input string (due to filtering and two-pointer traversal).
**Space Complexity:** O(N), to store the filtered string.

#### 2. In-place Two Pointers (Optimized Space)

This approach avoids creating a new string by performing the filtering and comparison simultaneously with two pointers on the original string.

**Algorithm:**
1.  Initialize `left` pointer to 0 and `right` pointer to `len(s) - 1`.
2.  While `left < right`:
    *   Move `left` pointer forward until it points to an alphanumeric character.
    *   Move `right` pointer backward until it points to an alphanumeric character.
    *   If `left < right`:
        *   Convert both `s[left]` and `s[right]` to lowercase.
        *   If they don't match, return `false`.
        *   Increment `left` and decrement `right`.
    *   Else (pointers crossed or met), break the loop.
3.  Return `true`.

**Time Complexity:** O(N), where N is the length of the input string.
**Space Complexity:** O(1), as no extra data structure is used beyond pointers.
