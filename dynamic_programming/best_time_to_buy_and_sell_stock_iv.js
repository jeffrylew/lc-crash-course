var maxProfitDS1 = function(k, prices)
{
    const get_max_profit = (curr_day, holding_stock, remain_tx) => {
        if (curr_day == prices.length || remain_tx == 0)
        {
            return 0;
        }

        if (memo[curr_day][holding_stock][remain_tx] != -1)
        {
            return memo[curr_day][holding_stock][remain_tx];
        }

        let max_profit = get_max_profit(curr_day + 1, holding_stock, remain_tx);
        if (holding_stock)
        {
            max_profit = Math.max(max_profit,
                                  get_max_profit(curr_day + 1, 0, remain_tx - 1)
                                  + prices[curr_day]);
        }
        else
        {
            max_profit = Math.max(max_profit,
                                  get_max_profit(curr_day + 1, 1, remain_tx)
                                  - prices[curr_day]);
        }

        memo[curr_day][holding_stock][remain_tx] = max_profit;
        return max_profit;
    }

    let memo = [];
    for (let curr_day = 0; curr_day < prices.length; curr_day++)
    {
        memo.push([]);
        for (let holding_idx = 0; holding_idx < 2; holding_idx++)
        {
            memo[holding_idx].push(new Array(k + 1).fill(-1));
        }
    }

    return get_max_profit(0, 0, k);
};
