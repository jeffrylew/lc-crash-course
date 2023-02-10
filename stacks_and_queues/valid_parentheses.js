/**
 * @param {string} s
 * @returns {boolean}
 */
var isValid = function(s) {
    let stack = [];
    const matching = {
        "(": ")",
        "[": "]",
        "{": "}"
    }

    for (const c of s)
    {
        // If c is an opening bracket
        if (c in matching)
        {
            stack.push(c);
        }
        else
        {
            if (!stack.length)
            {
                return false;
            }

            let previousOpening = stack.pop();
            if (matching[previousOpening] != c)
            {
                return false;
            }
        }
    }

    return !stack.length;
}