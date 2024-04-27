# Note: Using a class is only necessary if want to store data at each node.
# Otherwise, can implement a trie using only hash maps.
class TrieNode:
    def __init__(self):
        # Can store data at node if desired
        self.data = None
        self.children = {}


def build_trie(words: list[str]) -> TrieNode:
    root = TrieNode()
    for word in words:
        curr = root

        for letter in word:
            if letter not in curr.children:
                curr.children[letter] = TrieNode()
            curr = curr.children[letter]

        # At this point we have a full word at curr
        # Can perform more logic here to give curr an attribute

    return root
