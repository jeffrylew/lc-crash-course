class TrieNode:
    def __init__(self):
        self.is_end = False
        self.links = [None] * 26

    def contains_key(self, ch: str) -> bool:
        return self.links[ord(ch) - ord('a')] != None

    def get(self, ch: str):
        return self.links[ord(ch) - ord('a')]

    def put(self, ch: str, node) -> None:
        self.links[ord(ch) - ord('a')] = node

    def set_end(self) -> None:
        self.is_end = True

    def is_end(self) -> bool:
        return self.is_end


class Trie:

    def __init__(self):
        

    def insert(self, word: str) -> None:
        

    def search(self, word: str) -> bool:
        

    def startsWith(self, prefix: str) -> bool: