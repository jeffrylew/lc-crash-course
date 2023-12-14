def combinationSum(candidates: list[int], target: int) -> list[list[int]]:
    def backtrack(path: list[int], start: int, curr: int):
        if curr == target:
            ans.append(path[:])
            return

        for i in range(start, len(candidates)):
            num = candidates[i]
            if curr + num <= target:
                path.append(num)
                backtrack(path, i, curr + num)
                path.pop()

    ans = []
    backtrack([], 0, 0)
    return ans
