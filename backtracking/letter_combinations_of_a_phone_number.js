/**
 * @param {string} digits
 * @return {string[]}
 */
var letterCombinations = function(digits) {
    if (digits.length == 0)
    {
        return [];
    }

    letters = new Map([
        ["2", "abc"],
        ["3", "def"],
        ["4", "ghi"],
        ["5", "jkl"],
        ["6", "mno"],
        ["7", "pqrs"],
        ["8", "tuv"],
        ["9", "wxyz"]
    ]);

    const backtrack = (index, path) => {
        if (path.length == digits.length)
        {
            combinations.push([...path].join(""));
            return;
        }

        possible_letters = letters.get(digits.charAt(index));
        for (const letter of possible_letters)
        {
            path.push(letter);
            backtrack(index + 1, path);
            path.pop();
        }
    };

    let combinations = [];
    backtrack(0, []);
    return combinations;
};
