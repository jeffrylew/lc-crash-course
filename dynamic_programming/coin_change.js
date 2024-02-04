/**
 * @param {number[]} coins
 * @param {number} amount
 * @return {number}
 */
var coinChangeDS1 = function(coins, amount) {
    const get_min_coins = remaining_amt => {
        if (remaining_amt < 0)
        {
            return -1;
        }

        if (remaining_amt == 0)
        {
            return 0;
        }

        let min_count = amount + 1;
        for (const coin of coins)
        {
            const count = get_min_coins(remaining_amt - coin);

            if (count == -1)
            {
                continue;
            }

            min_count = Math.min(min_count, count + 1);
        }

        return min_count == (amount + 1) ? -1 : min_count;
    }

    return get_min_coins(amount);
};

/**
 * @param {number[]} coins
 * @param {number} amount
 * @return {number}
 */
var coinChangeDS2 = function(coins, amount) {
    let memo = new Array(amount + 1).fill(0);

    const get_min_coins = remaining_amt => {
        if (remaining_amt < 0)
        {
            return -1;
        }

        if (remaining_amt == 0)
        {
            return 0;
        }

        if (memo[remaining_amt] != 0)
        {
            return memo[remaining_amt];
        }

        let min_count = amount + 1;
        for (const coin of coins)
        {
            const count = get_min_coins(remaining_amt - coin);

            if (count == -1)
            {
                continue;
            }

            min_count = Math.min(min_count, count + 1);
        }

        memo[remaining_amt] = min_count == (amount + 1) ? -1 : min_count;
        return memo[remaining_amt];
    }

    return get_min_coins(amount);
};

/**
 * @param {number[]} coins
 * @param {number} amount
 * @return {number}
 */
var coinChangeDS3 = function(coins, amount) {
    let dp = new Array(amount + 1).fill(amount + 1);
    dp[0] = 0;

    for (let remaining_amt = 1; remaining_amt <= amount; remaining_amt++)
    {
        for (const coin of coins)
        {
            if (remaining_amt - coin < 0)
            {
                continue;
            }

            dp[remaining_amt] =
                Math.min(dp[remaining_amt], dp[remaining_amt - coin] + 1);
        }
    }

    return dp[amount] == (amount + 1) ? -1 : dp[amount];
};
