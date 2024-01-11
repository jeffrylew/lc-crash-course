/**
 * @param {number[][]} questions
 * @return {number}
 */
var mostPointsTopDown = function(questions) {
    const dp = i => {
        if (i >= questions.length)
        {
            return 0;
        }

        if (memo[i] != -1)
        {
            return memo[i];
        }

        const next_index = i + questions[i][1] + 1;
        memo[i] = Math.max(questions[i][0] + dp(next_index), dp(i + 1));
        return memo[i];
    };

    let memo = new Array(questions.length).fill(-1);
    return dp(0);
};
