class TrieNode
{
    // Can store data at nodes if desired
    Map<Character, TrieNode> children;
    List<String> suggestions;

    TrieNode()
    {
        this.children = new HashMap<>();
        this.suggestions = new ArrayList<>();
    }
}

public List<List<String>> suggestedProducts(
    String[] products, String searchWord)
{
    TrieNode root = new TrieNode();

    for (String product : products)
    {
        TrieNode node = root;
        for (char letter : product.toCharArray())
        {
            if (!node.children.containsKey(letter))
            {
                node.children.put(letter, new TrieNode());
            }
            node = node.children.get(letter);

            node.suggestions.add(product);
            Collections.sort(node.suggestions);
            if (node.suggestions.size() > 3)
            {
                node.suggestions.remove(node.suggestions.size() - 1);
            }
        }
    }

    List<List<String>> suggested_products = new ArrayList<>();
    TrieNode node = root;

    for (char letter : searchWord.toCharArray())
    {
        if (node.children.containsKey(letter))
        {
            node = node.children.get(letter);
            suggested_products.add(node.suggestions);
        }
        else
        {
            // Deadend reached
            node.children = new HashMap<>();
            suggested_products.add(new ArrayList<String>());
        }
    }

    return suggested_products;
}
