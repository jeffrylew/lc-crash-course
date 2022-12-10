/**
 * @param {string} s
 * @param {string} t
 * @returns {boolean}
 */

/**
 * Alternatively can use ES6 arrow function,
 * let isSubsequence = (s, t) => { ... }
 */
var isSubsequence = function(s, t) {
    let i = 0, j = 0;
    while (i < s.length && j < t.length)
    {
        if (s[i] == t[j])
        {
            i++;
        }
        j++;
    }

    return i == s.length;
}