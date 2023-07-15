from collections import defaultdict
from collections import deque


def ladderLengthBFS(beginWord: str, endWord: str, wordList: list[str]) -> int:
    if endWord not in wordList:
        return 0
    
    # Since all words are of same length
    L = len(beginWord)

    # Dict holding combination of words that can be formed from any given word
    # by changing one letter at a time
    all_combo_dict = defaultdict(list)
    for word in wordList:
        for i in range(L):
            # Key is generic word
            # Value is list of words that have same intermediate generic word
            all_combo_dict[word[:i] + "*" + word[i + 1:]].append(word)
    
    # Queue for BFS
    queue = deque([(beginWord, 1)])
    visited = set([beginWord])

    while queue:
        current_word, level = queue.popleft()

        for i in range(L):
            # Intermediate words for current word
            intermediate_word = current_word[:i] + "*" + current_word[i + 1:]

            for word in all_combo_dict[intermediate_word]:
                if word == endWord:
                    return level + 1
                
                if word not in visited:
                    visited.add(word)
                    queue.append((word, level + 1))
            
            all_combo_dict[intermediate_word] = []
    
    return 0