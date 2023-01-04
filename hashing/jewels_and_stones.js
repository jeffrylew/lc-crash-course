/**
 * @param {string} jewels
 * @param {string} stones
 * @returns {number}
 */
var numJewelsInStones = function(jewels, stones) {
    let jewelSet = new Set();
    for (const c of jewels)
    {
        jewelSet.add(c);
    }

    let num_jewels = 0;
    for (const c of stones)
    {
        if (jewelSet.has(c))
        {
            num_jewels++;
        }
    }

    return num_jewels;
}