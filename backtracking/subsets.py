def subsets(nums: list[int]) -> list[list[int]]:
    def backtrack(curr, i):
        if i > len(nums):
            return

        ans.append(curr[:])
        for j in range(i, len(nums)):
            curr.append(nums[j])
            backtrack(curr, j + 1)
            curr.pop()

    ans = []
    backtrack([], 0)
    return ans
