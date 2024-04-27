// Note: Using a class is only necessary if want to store data at each node.
// Otherwise, can implement a trie using only hash maps.
class TrieNode
{
    // Can store data at node if desired
    int data;

    Map<Character, TrieNode> children;

    TrieNode()
    {
        this.children = new HashMap<>();
    }
}

public TrieNode buildTrie(String[] words)
{
    TrieNode root = new TrieNode();

    for (String word : words)
    {
        TrieNode curr = root;
        for (char letter : word.toCharArray())
        {
            if (!curr.children.containsKey(letter))
            {
                curr.children.put(letter, new TrieNode());
            }

            curr = curr.children.get(c);
        }

        // At this point we have a full word at curr
        // Can perform more logic here to give curr an attribute
    }

    return root;
}
