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

def ladderLengthBidirBFS(
    beginWord: str, endWord: str, wordList: list[str]
) -> int:
    if endWord not in wordList:
        return 0
    
    # Since all words are of same length
    L = len(beginWord)

    all_combo_dict = defaultdict(list)
    for word in wordList:
        for i in range(L):
            # Key is generic word
            # Value is list of words that have same intermediate generic word
            all_combo_dict[word[:i] + "*" + word[i + 1:]].append(word)

    def visitWordNode(queue, visited, others_visited):
        queue_size = len(queue)
        for _ in range(queue_size):
            curr_word = queue.popleft()

            for i in range(L):
                intermediate_word = curr_word[:i] + "*" + curr_word[i + 1:]

                for adjacent in all_combo_dict[intermediate_word]:
                    if adjacent in others_visited:
                        return visited[curr_word] + others_visited[adjacent]
                    
                    if adjacent not in visited:
                        visited[adjacent] = visited[curr_word] + 1
                        queue.append(adjacent)
        
        return None

    # Queues for bidirectional BFS
    q_begin = deque([beginWord])
    q_end = deque([endWord])

    visited_begin = {beginWord : 1}
    visited_end = {endWord : 1}
    ans = None

    while q_begin and q_end:
        if len(q_begin) <= len(q_end):
            ans = visitWordNode(q_begin, visited_begin, visited_end)
        else:
            ans = visitWordNode(q_end, visited_end, visited_begin)
        
        if ans:
            return ans
    
    return 0