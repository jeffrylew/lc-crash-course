/**
 * @param {string} word
 * @param {number} m
 * @returns {number[]}
 */
var divisibilityArray = function(word, m)
{
    let div = [];
    let curr = 0;

    for (let pos = 0; pos < word.length; pos++)
    {
        curr = (curr * 10 + +word[pos]) % m;

        if (curr == 0)
        {
            div.push(1);
        }
        else
        {
            div.push(0);
        }
    }

    return div;
};
