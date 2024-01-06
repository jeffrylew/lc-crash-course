from functools import cache


def lengthOfLISTopDown(nums: list[int]) -> int:
    @cache
    def dp(i: int) -> int:
        # Base case
        ans = 1

        # Recurrence relation
        for j in range(i):
            if nums[i] > nums[j]:
                ans = max(ans, dp(j) + 1)

        return ans

    return max(dp(i) for i in range(len(nums)))
