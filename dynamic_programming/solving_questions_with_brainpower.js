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

/**
 * @param {number[][]} questions
 * @return {number}
 */
var mostPointsBottomUp = function(questions) {
    const questions_length = questions.length;

    // + 1 to avoid out of bounds
    let dp = new Array(questions_length + 1).fill(0);

    for (let i = questions_length - 1; i >= 0; i--)
    {
        // Need to make sure we don't go out of bounds
        const next_index = Math.min(i + questions[i][1] + 1, questions_length);

        dp[i] = Math.max(questions[i][0] + dp[next_index], dp[i + 1]);
    }

    return dp[0];
};
