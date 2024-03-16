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
