let helper = (s, left, right) => {
    if (left >= right)
    {
        return;
    }

    const tmp  = s[left];
    s[left++]  = s[right];
    s[right--] = tmp;

    helper(s, left, right);
};

/**
 * Recursive solution
 * @param {character[]} s
 * @return {void} Do not return anything, modify s in-place instead.
 */
var reverseStringRecursive = function(s) {
    helper(s, 0, s.length - 1);
};

let reverseStringTwoPointers = (s) => {
    let left  = 0;
    let right = s.length - 1;

    while (left < right)
    {
        const tmp  = s[left];
        s[left++]  = s[right];
        s[right--] = tmp;
    }
}