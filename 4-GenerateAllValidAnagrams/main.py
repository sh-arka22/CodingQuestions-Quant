from typing import List
from collections import Counter

def generate_valid_anagrams(dictionary: List[str], letters: List[str]) -> List[str]:
    """
    Given a dictionary of valid words and a list of available letters,
    return all valid words that can be formed using the letters.
    
    Each letter from the input list can be used at most once per word.
    
    Args:
    dictionary: List of valid words.
    letters: List of available characters (may contain duplicates).
    
    Returns:
    List of valid words from the dictionary that can be formed.
    """
    letter_count = Counter(letters)
    result = []
    for word in dictionary:
        word_count = Counter(word)
        if all(word_count[char] <= letter_count[char] for char in word_count):
            result.append(word)
    return result

if __name__ == "__main__":
    # Test Case 1: Basic
    dictionary = ["cat", "act", "dog", "good", "tac"]
    letters = ['c', 'a', 't']
    print(f"Dictionary: {dictionary}")
    print(f"Letters: {letters}")
    print(f"Valid words: {generate_valid_anagrams(dictionary, letters)}")
    print("-" * 20)

    # Test Case 2: Duplicates
    dictionary = ["eat", "tea", "ate", "apple", "leap"]
    letters = ['e', 'a', 't', 'a']
    print(f"Dictionary: {dictionary}")
    print(f"Letters: {letters}")
    print(f"Valid words: {generate_valid_anagrams(dictionary, letters)}")
    print("-" * 20)
    
    # Test Case 3: Subset
    dictionary = ["a", "an", "at", "tan", "nat"]
    letters = ['t', 'a', 'n']
    print(f"Dictionary: {dictionary}")
    print(f"Letters: {letters}")
    print(f"Valid words: {generate_valid_anagrams(dictionary, letters)}")
    print("-" * 20)
