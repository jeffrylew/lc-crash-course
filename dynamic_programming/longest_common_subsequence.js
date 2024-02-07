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
