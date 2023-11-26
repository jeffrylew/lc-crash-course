def combine(n: int, k: int) -> list[list[int]]:
    def backtrack(curr: list[int], i: int):
        if len(curr) == k:
            ans.append(curr[:])
            return

        for num in range(i, n + 1):
            curr.append(num)
            backtrack(curr, num + 1)
            curr.pop()

    ans = []
    backtrack([], 1)
    return ans
