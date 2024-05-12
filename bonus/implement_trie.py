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


    def get_is_end(self) -> bool:
        return self.is_end


class Trie:
    def __init__(self):
        self.root = TrieNode()
        

    def insert(self, word: str) -> None:
        node = self.root
        for curr_char in word:
            if not node.contains_key(curr_char):
                node.put(curr_char, TrieNode())
            node = node.get(curr_char)
        node.set_end()


    def search_prefix(self, word: str):
        node = self.root
        for curr_char in word:
            if node.contains_key(curr_char):
                node = node.get(curr_char)
            else:
                return None
        return node


    def search(self, word: str) -> bool:
        node = self.search_prefix(word)
        return node != None and node.get_is_end()
        

    def startsWith(self, prefix: str) -> bool:
        node = self.search_prefix(prefix)
        return node != None
