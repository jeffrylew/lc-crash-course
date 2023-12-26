/**
 * @param {number} n
 * @returns {number}
 */
var fibonacci1 = function(n) {
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return fibonacci1(n - 1) + fibonacci1(n - 2);
};

let memo = new Map();

/**
 * @param {number} n
 * @returns {number}
 */
var fibonacci2 = function(n) {
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    if (memo.has(n))
    {
        return memo.get(n);
    }

    memo.set(n, fibonacci2(n - 1) + fibonacci2(n - 2));
    return memo.get(n);
};
