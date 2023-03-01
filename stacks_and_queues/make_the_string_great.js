/**
 * @param {string} s
 * @returns {string}
 */
const makeGood = (s) => {
    let stack = [];

    for (const currChar of s)
    {
        if (stack.length
            && Math.abs(stack[stack.length - 1].charCodeAt(0)
                        - currChar.charCodeAt(0)) == 32)
        {
            stack.pop();
        }
        else
        {
            stack.push(currChar);
        }
    }

    return stack.join("");
}