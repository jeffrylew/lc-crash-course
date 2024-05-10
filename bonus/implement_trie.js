class TrieNode
{
    constructor()
    {
        this.links = new Array(26);
        this.is_end = false;
    }

    ascii_diff(lhs_letter, rhs_letter)
    {
        return lhs_letter.charCodeAt(0) - rhs_letter.charCodeAt(0);
    }

    contains_key(ch)
    {
        return this.links[this.ascii_diff(ch, 'a')] !== undefined;
    }

    get(ch)
    {
        return this.links[this.ascii_diff(ch, 'a')];
    }

    put(ch, node)
    {
        this.links[this.ascii_diff(ch, 'a')] = node;
    }

    set_end()
    {
        this.is_end = true;
    }

    get_is_end()
    {
        return this.is_end;
    }
}

var Trie = function()
{
    this.root = new TrieNode();
};

/** 
 * @param {string} word
 * @return {void}
 */
Trie.prototype.insert = function(word)
{
    let node = this.root;

    for (let i = 0; i < word.length; i++)
    {
        const current_char = word.charAt(i);

        if (!node.contains_key(current_char))
        {
            node.put(current_char, new TrieNode());
        }

        node = node.get(current_char);
    }

    node.set_end();
};

/**
 * @param {string} word
 * @return {TrieNode}
 */
Trie.prototype.search_prefix = function(word)
{
    let node = this.root;

    for (let i = 0; i < word.length; i++)
    {
        const current_char = word.charAt(i);

        if (node.contains_key(current_char))
        {
            node = node.get(current_char);
        }
        else
        {
            return null;
        }
    }

    return node;
};

/** 
 * @param {string} word
 * @return {boolean}
 */
Trie.prototype.search = function(word)
{
    const node = this.search_prefix(word);
    return node !== null && node.get_is_end();
};

/** 
 * @param {string} prefix
 * @return {boolean}
 */
Trie.prototype.startsWith = function(prefix)
{
    const node = this.search_prefix(prefix);
    return node !== null;
};
