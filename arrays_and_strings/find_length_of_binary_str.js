/**
 * @param {string} s
 * @return {number}
 */
var findLength = function(s) {
    let left = 0, curr = 0, max_substr_length = 0;

    for (let right = 0; right < s.length; right++)
    {
        if (s[right] == "0")
        {
            curr++;    
        }

        while (curr > 1)
        {
            if (s[left] == "0")
            {
                curr -= 1;    
            }
            left++;
        }

        max_substr_length = Math.max(max_substr_length, right - left + 1);
    }

    return max_substr_length;
}