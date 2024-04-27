// Note: Using a class is only necessary if want to store data at each node.
// Otherwise, can implement a trie using only hash maps.
class TrieNode
{
    constructor()
    {
        // Can store data at node if desired
        this.data = null;
        this.children = new Map();
    }
}

const buildTrie = words => {
    let root = new TrieNode();

    for (const word of words)
    {
        let curr = root;
        for (const letter of word)
        {
            if (!curr.children.has(letter))
            {
                curr.children.set(letter, new TrieNode());
            }
            curr = curr.children.get(letter);
        }

        // At this point we have a full word at curr
        // Can perform more logic here to give curr an attribute
    }

    return root;
}
