/**
 * @param {string} s
 * @returns {number}
 */
var lengthOfLongestSubstring = function(s) {
    let substr_len = 0;
    let left = 0;

    let char_idx = new Map();

    for (let right = 0; right < s.length; right++)
    {
        if (char_idx.has(s.charAt(right)))
        {
            left = Math.max(char_idx.get(s.charAt(right)), left);
        }

        substr_len = Math.max(substr_len, right - left + 1);
        char_idx.set(s.charAt(right), right + 1);
    }

    return substr_len;
}