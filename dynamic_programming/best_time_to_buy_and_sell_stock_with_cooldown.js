/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfitDS1 = function(prices) {
    let sold = Number.MIN_SAFE_INTEGER;
    let hold = Number.MIN_SAFE_INTEGER;
    let reset = 0;

    for (const price of prices)
    {
        const pre_sold = sold;
        sold = hold + price;
        hold = Math.max(hold, reset - price);
        reset = Math.max(reset, pre_sold);
    }

    return Math.max(sold, reset);
};

/**
 * @param {number[]} prices
 * @return {number}
 */
var maxProfitDS2 = function(prices) {
    let max_profit = new Array(prices.length + 2).fill(0);

    for (let prev_day = prices.length - 1; prev_day >= 0; prev_day--)
    {
        let case1 = 0;

        for (let curr_day = prev_day + 1; curr_day < prices.length; curr_day++)
        {
            const profit =
                prices[curr_day] - prices[prev_day] + max_profit[curr_day + 2];
            case1 = Math.max(profit, case1);
        }

        const case2 = max_profit[prev_day + 1];

        max_profit[prev_day] = Math.max(case1, case2);
    }

    return max_profit[0];
};
