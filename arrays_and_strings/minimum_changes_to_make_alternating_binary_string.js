/**
 * @param {string} s
 * @return {number}
 */
var minOperationsDS1 = function(s) {
    let start0 = 0;
    let start1 = 0;

    for (let i = 0; i < s.length; i++)
    {
        if (i % 2 == 0)
        {
            if (s[i] == '0')
            {
                start1++;
            }
            else
            {
                start0++;
            }
        }
        else
        {
            if (s[i] == '1')
            {
                start1++;
            }
            else
            {
                start0++;
            }
        }
    }

    return Math.min(start0, start1);
};
