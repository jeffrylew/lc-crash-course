/**
 * @param {string} s
 * @returns {string}
 */
var removeDuplicates = function(s) {
    let stack = [];
    for (const c of s)
    {
        if (stack.length && stack[stack.length - 1] == c)
        {
            stack.pop();
        }
        else
        {
            stack.push(c);
        }
    }

    return stack.join("");
}