/**
 * @param {string} text1
 * @param {string} text2
 * @returns {number}
 */
var longestCommonSubsequenceDS1 = function(text1, text2) {
    const get_lcs = (idx1, idx2) => {
        if (idx1 == text1.length || idx2 == text2.length)
        {
            return 0;
        }

        if (memo[idx1][idx2] != -1)
        {
            return memo[idx1][idx2];
        }

        let length = 0;

        if (text1[idx1] == text2[idx2])
        {
            length = 1 + get_lcs(idx1 + 1, idx2 + 1);
        }
        else
        {
            length = Math.max(get_lcs(idx1 + 1, idx2), get_lcs(idx1, idx2 + 1));
        }

        memo[idx1][idx2] = length;
        return memo[idx1][idx2];
    }

    let memo = [];
    for (let idx1 = 0; idx1 < text1.length; idx1++)
    {
        memo.push(new Array(text2.length).fill(-1));
    }

    return get_lcs(0, 0);
};

/**
 * @param {string} text1
 * @param {string} text2
 * @returns {number}
 */
var longestCommonSubsequenceDS2 = function(text1, text2) {
    const text1_len = text1.length;
    const text2_len = text2.length;

    let lcs = [];
    for (let idx1 = 0; idx1 <= text1_len; idx1++)
    {
        lcs.push(new Array(text2_len + 1).fill(0));
    }

    for (let idx1 = text1_len - 1; idx1 >= 0; idx1--)
    {
        for (let idx2 = text2_len - 1; idx2 >= 0; idx2--)
        {
            if (text1[idx1] == text2[idx2])
            {
                lcs[idx1][idx2] = 1 + lcs[idx1 + 1][idx2 + 1];
            }
            else
            {
                lcs[idx1][idx2] =
                    Math.max(lcs[idx1 + 1][idx2], lcs[idx1][idx2 + 1]);
            }
        }
    }

    return lcs[0][0];
};
