from functools import cache


def rob_top_down(nums: list[int]) -> int:
    if len(nums) == 1:
        # Prevent out-of-bounds error
        return nums[0]

    def dp(i: int) -> int:
        # Base cases
        if i == 0:
            return nums[0]

        if i == 1:
            return max(nums[0], nums[1])

        if i in memo:
            return memo[i]

        # Recurrence relation
        memo[i] = max(dp(i - 1), dp(i - 2) + nums[i])
        return memo[i]

    memo = {}
    return dp(len(nums) - 1)


def rob_top_down_cached(nums: list[int]) -> int:
    @cache
    def dp(i: int) -> int:
        # Base cases
        if i == 0:
            return nums[0]

        if i == 1:
            return max(nums[0], nums[1])

        # Recurrence relation
        return max(dp(i - 1), dp(i - 2) + nums[i])

    return dp(len(nums) - 1)


def rob_bottom_up(nums: list[int]) -> int:
    nums_len = len(nums)

    # Avoid out-of-bounds error from setting base case
    if nums_len == 1:
        return nums[0]

    dp = [0] * nums_len

    # Base cases
    dp[0] = nums[0]
    dp[1] = max(nums[0], nums[1])

    for i in range(2, nums_len):
        # Recurrence relation
        dp[i] = max(dp[i - 1], dp[i - 2] + nums[i])

    return dp[nums_len - 1]
