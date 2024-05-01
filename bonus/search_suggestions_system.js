class TrieNode
{
    constructor()
    {
        this.children = new Map();
        this.suggestions = [];
    }
}

/**
 * @param {string[]} products
 * @param {string} searchWord
 * @returns {string[][]}
 */
var suggestedProducts = function(products, searchWord) {
    let root = new TrieNode();

    for (const product of products)
    {
        let node = root;
        for (const letter of product)
        {
            if (!node.children.has(letter))
            {
                node.children.set(letter, new TrieNode());
            }
            node = node.children.get(letter);

            node.suggestions.push(product);
            node.suggestions.sort();
            if (node.suggestions.length > 3)
            {
                node.suggestions.pop();
            }
        }
    }

    let suggested_products = [];
    let node = root;
    for (const letter of searchWord)
    {
        if (node.children.has(letter))
        {
            node = node.children.get(letter);
            suggested_products.push(node.suggestions);
        }
        else
        {
            node.children = new Map();
            suggested_products.push([]);
        }
    }

    return suggested_products;
};
