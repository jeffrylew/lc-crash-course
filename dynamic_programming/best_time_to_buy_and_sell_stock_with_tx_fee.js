/**
 * @param {number[]} prices
 * @param {number} fee
 * @return {number}
 */
var maxProfitDS1 = function(prices, fee) {
    const num_days = prices.length;
    let free = Array(num_days).fill(0);
    let hold = Array(num_days).fill(0);

    // In order to hold a stock on day 0, we have
    // no other choice but to buy it for prices[0]
    hold[0] = -prices[0];

    for (let curr_day = 1; curr_day < num_days; curr_day++)
    {
        free[curr_day] = Math.max(free[curr_day - 1],
                                  hold[curr_day - 1] + prices[curr_day] - fee);
        hold[curr_day] = Math.max(hold[curr_day - 1],
                                  free[curr_day - 1] - prices[curr_day]);
    }

    return free[num_days - 1];
};

/**
 * @param {number[]} prices
 * @param {number} fee
 * @return {number}
 */
var maxProfitDS2 = function(prices, fee) {
    const num_days = prices.length;
    let free = 0;
    let hold = -prices[0];

    for (let curr_day = 1; curr_day < num_days; curr_day++)
    {
        const hold_init = hold;
        hold = Math.max(hold, free - prices[curr_day]);
        free = Math.max(free, hold_init + prices[curr_day] - fee);
    }

    return free;
};
