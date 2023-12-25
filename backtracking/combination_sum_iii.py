def combinationSum3DS1(k: int, n: int) -> list[list[int]]:
    results = []

    def backtrack(remain: int, comb: list[int], next_start: int):
        if remain == 0 and len(comb) == k:
            # Make a copy of current combination otherwise the combination
            # would be reverted in another branch of backtracking
            results.append(list(comb))
            return
        elif remain < 0 or len(comb) == k:
            # Exceeded the scope, no need to explore further
            return

        # Iterate through the reduced list of candidates
        for i in range(next_start, 9):
            comb.append(i + 1)
            backtrack(remain - i - 1, comb, i + 1)
            comb.pop()

    backtrack(n, [], 0)
    return results
