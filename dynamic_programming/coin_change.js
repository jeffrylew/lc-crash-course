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
