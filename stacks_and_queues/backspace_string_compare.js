/**
 * @param {string} s
 * @param {string} t
 * @returns {boolean}
 */
const backspaceCompare = (s, t) => {
    let build = s => {
        let stack = [];
        for (const c of s)
        {
            if (c != "#")
            {
                stack.push(c);
            }
            else if (stack.length)
            {
                stack.pop();
            }
        }

        return stack.join("");
    }

    return build(s) == build(t);
}