/**
 * @param {string} sentence
 * @returns {boolean}
 */
var checkIfPangram = function(sentence) {
    let seen = new Set();

    for (const c of sentence)
    {
        seen.add(c);
    }

    return seen.size == 26;
}