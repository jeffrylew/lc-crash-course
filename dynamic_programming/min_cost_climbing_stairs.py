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
