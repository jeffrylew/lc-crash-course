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
