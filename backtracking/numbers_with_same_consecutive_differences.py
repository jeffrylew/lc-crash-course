def numsSameConsecDiffDS1(n: int, k: int) -> list[int]:
    if n == 1:
        return [i for i in range(10)]

    ans = []

    def dfs(remaining_N_digits: int, num: int):
        # Base case
        if remaining_N_digits == 0:
            return ans.append(num)

        tail_digit = num % 10

        # Use set() to avoid duplicates when k == 0
        next_digits = set([tail_digit + k, tail_digit - k])

        for next_digit in next_digits:
            if 0 <= next_digit < 10:
                dfs(remaining_N_digits - 1, num * 10 + next_digit)

    for num in range(1, 10):
        dfs(n - 1, num)

    return list(ans)
