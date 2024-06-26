/**
 * @param {number} n
 * @param {number[][]} flights
 * @param {number} src
 * @param {number} dst
 * @param {number} k
 * @return {number}
 */
var findCheapestPriceDS1 = function(n, flights, src, dst, k)
{
    let adj = new Map();
    for (const flight of flights)
    {
        if (adj.has(flight[0]))
        {
            adj.get(flight[0]).push([flight[1], flight[2]]);
        }
        else
        {
            adj.set(flight[0], [[flight[1], flight[2]]]);
        }
    }

    let costs = new Array(n).fill(Number.MAX_SAFE_INTEGER);

    let city_cost = [[src, 0]];

    let stops = 0;
    while (stops <= k && city_cost.length)
    {
        let level_size = city_cost.length;
        let next_city_cost = [];

        for (let idx = 0; idx < level_size; idx++)
        {
            const [curr_city, cost_to_curr_city] = city_cost[idx];

            if (!adj.has(curr_city))
            {
                continue;
            }

            for (const [neighbor, price] of adj.get(curr_city))
            {
                if (cost_to_curr_city + price >= costs[neighbor])
                {
                    continue;
                }

                costs[neighbor] = cost_to_curr_city + price;
                next_city_cost.push([neighbor, costs[neighbor]]);
            }
        }

        city_cost = next_city_cost;
        stops++;
    }

    return costs[dst] === Number.MAX_SAFE_INTEGER ? -1 : costs[dst];
};

/**
 * @param {number} n
 * @param {number[][]} flights
 * @param {number} src
 * @param {number} dst
 * @param {number} k
 * @return {number}
 */
var findCheapestPriceDS2 = function(n, flights, src, dst, k)
{
    // Costs from src to all other cities
    let costs = new Array(n).fill(Number.MAX_SAFE_INTEGER);
    costs[src] = 0;

    // Run only k + 1 times since want minimum cost in k stops
    for (let num_flights = 0; num_flights <= k; num_flights++)
    {
        // Create copy of costs array
        let temp = [...costs];

        for (const [from, to, price] of flights)
        {
            if (costs[from] != Number.MAX_SAFE_INTEGER)
            {
                temp[to] = Math.min(temp[to], costs[from] + price);
            }
        }

        // Copy temp array into costs
        costs = temp;
    }

    return costs[dst] == Number.MAX_SAFE_INTEGER ? -1 : costs[dst];
};
