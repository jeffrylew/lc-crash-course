class TrieNode:
    def __init__(self):
        self.children = {}
        self.suggestions = []


def suggestedProducts(products: list[str], searchWord: str) -> list[list[str]]:
    root = TrieNode()

    for product in products:
        node = root
        for letter in product:
            if letter not in node.children:
                node.children[letter] = TrieNode()
            node = node.children[letter]

            node.suggestions.append(product)
            node.suggestions.sort()
            if len(node.suggestions) > 3:
                node.suggestions.pop()

    suggested_products = []
    node = root
    for letter in searchWord:
        if letter in node.children:
            node = node.children[letter]
            suggested_products.append(node.suggestions)
        else:
            # Deadend reached
            node.children = {}
            suggested_products.append([])

    return suggested_products
