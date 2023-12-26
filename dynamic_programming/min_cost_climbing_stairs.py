def minCostClimbingStairsTopDown(cost: list[int]) -> int:
    # 1. A function that returns the answer
    def dp(i: int) -> int:
        if i <= 1:
            # 3. Base case(s)
            return 0

        if i in memo:
            return memo[i]

        # 2. Recurrence relation
        memo[i] = min(dp(i - 1) + cost[i - 1], dp(i - 2) + cost[i - 2])
        return memo[i]

    memo = {}
    return dp(len(cost))


def minCostClimbingStairsBottomUp(cost: list[int]) -> int:
    n = len(cost)

    # Step 2
    dp = [0] * (n + 1)

    # Step 3: Base case(s) are implicitly defined as they are 0

    # Step 4
    for i in range(2, n + 1):
        # Step 5
        dp[i] = min(dp[i - 1] + cost[i - 1], dp[i - 2] + cost[i - 2])

    # Step 6
    return dp[n]
