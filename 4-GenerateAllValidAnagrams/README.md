# 4. Generate All Valid Anagrams

[Original File](https://ppl-ai-file-upload.s3.amazonaws.com/web/direct-files/collection_56c59554-dd0a-419e-9118-d83f6c2ce621/4ebc7a1a-e1c0-4852-84a3-1a0d8948849d/Coding-Questions-Report-QUANT.pdf)

### Problem Explanation

Given a **dictionary** (list of valid words) and a **multiset of letters**, generate **all valid words (anagrams)** that can be formed using those letters.

**Key points:**
- You have a collection of letters (possibly with duplicates)
- You must form valid dictionary words
- Each letter can be used at most once per word
- Return all possible valid words

### Examples

#### Example 1: Basic Case
```
Input:
dictionary = ["cat", "act", "dog", "good", "tac"]
letters = ['c', 'a', 't']

Output:
["cat", "act", "tac"]
```

#### Example 2: With Duplicate Letters
```
Input:
dictionary = ["eat", "tea", "ate", "apple", "leap"]
letters = ['e', 'a', 't', 'a']  # Note: two 'a's

Output:
["eat", "tea", "ate"]
```

#### Example 3: Subset Usage
```
Input:
dictionary = ["a", "an", "at", "tan", "nat"]
letters = ['t', 'a', 'n']

Output:
["a", "an", "at", "tan", "nat"]
```

### Key Insights

**1. Anagram Signature:**
Two words are anagrams if they have the **same sorted letters**.
- "cat" -> sorted: "act"
- "act" -> sorted: "act"

**2. Character Frequency:**
A word can be formed if its character frequency <= available letter frequency.

### Approaches

#### Approach 1: Brute Force
For each word in the dictionary, check if it can be formed from the given letters completely.
- **Time Complexity:** $O(D \times L)$ where D is dictionary size and L is average word length.

#### Approach 2: Preprocess Dictionary
If multiple queries are expected, preprocess the dictionary into a frequency map or sorted signatures.

### Interview Questions

1. **Checking Validity:** How would you check if a word can be formed from the letters?
2. **Preprocessing:** Would you preprocess the dictionary or the letters?
3. **Handling Duplicates:** How do you ensure you don't use more letters than available?
