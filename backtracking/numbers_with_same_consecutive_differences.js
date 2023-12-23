/**
 * @param {number} n
 * @param {number} k
 * @return {number[]}
 */
var numsSameConsecDiffDS1 = function(n, k) {
    if (n == 1)
    {
        return [0, 1, 2, 3, 4, 5, 6, 7, 8, 9];
    }

    let results = [];

    const dfs = (remaining_N_digits, num) => {
        if (remaining_N_digits == 0)
        {
            results.push(num);
            return;
        }

        const tail_digit = num % 10;
        let next_digits = [tail_digit + k];
        if (k != 0)
        {
            next_digits.push(tail_digit - k);
        }

        for (const next_digit of next_digits)
        {
            if (0 <= next_digit && next_digit < 10)
            {
                dfs(remaining_N_digits - 1, num * 10 + next_digit);
            }
        }
    };

    for (let num = 1; num < 10; ++num)
    {
        dfs(n - 1, num);
    }

    return results;
};
