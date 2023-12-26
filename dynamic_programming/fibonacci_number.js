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

/**
 * @param {number} n
 * @returns {number}
 */
var fibonacci3 = function(n) {
    let arr = new Array(n + 1).fill(0);

    // Base case - the second Fibonacci number is 1
    arr[1] = 1;

    for (let i = 2; i <= n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    return arr[n];
};
