/**
 * @param {number[][]} piles
 * @param {number} k
 * @return {number}
 */
var maxValueOfCoinsDS1 = function(piles, k) {
    const get_max_value = (curr_pile, remain_coins) => {
        if (curr_pile == piles.length || remain_coins == 0)
        {
            return 0;
        }

        if (memo[curr_pile][remain_coins] != -1)
        {
            return memo[curr_pile][remain_coins];
        }

        //  Skip this pile
        let max_value = get_max_value(curr_pile + 1, remain_coins);
        let curr_value = 0;
        for (let coin = 0;
             coin < Math.min(remain_coins, piles[curr_pile].length);
             coin++)
        {
            curr_value += piles[curr_pile][coin];
            max_value = Math.max(max_value,
                                 get_max_value(curr_pile + 1,
                                               remain_coins - coin - 1)
                                 + curr_value);
        }

        memo[curr_pile][remain_coins] = max_value;
        return max_value;
    }

    let memo = [];
    for (let curr_pile = 0; curr_pile < piles.length; curr_pile++)
    {
        memo.push(new Array(k + 1).fill(-1));
    }

    return get_max_value(0, k);
};

/**
 * @param {number[][]} piles
 * @param {number} k
 * @return {number}
 */
var maxValueOfCoinsDS2 = function(piles, k) {
    const num_piles = piles.length;
    let dp = [];
    for (let curr_pile = 0; curr_pile <= num_piles; curr_pile++)
    {
        dp.push(new Array(k + 1).fill(0));
    }

    for (let curr_pile = num_piles - 1; curr_pile >= 0; curr_pile--)
    {
        for (let remain_coins = 1; remain_coins <= k; remain_coins++)
        {
            // Skip this pile
            dp[curr_pile][remain_coins] = dp[curr_pile + 1][remain_coins];

            let curr_value = 0;
            for (let coin = 0;
                 coin < Math.min(remain_coins, piles[curr_pile].length);
                 coin++)
            {
                curr_value += piles[curr_pile][coin];
                dp[curr_pile][remain_coins] =
                    Math.max(dp[curr_pile][remain_coins],
                             dp[curr_pile + 1][remain_coins - coin - 1]
                             + curr_value);
            }
        }
    }

    return dp[0][k];
};
