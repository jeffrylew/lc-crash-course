import math
from functools import cache


def climbStairsDS1(n: int) -> int:
    def climb_Stairs(curr_step: int) -> int:
        if curr_step > n:
            return 0

        if curr_step == n:
            return 1

        return climb_Stairs(curr_step + 1) + climb_Stairs(curr_step + 2)

    return climb_Stairs(0)


def climbStairsDS2(n: int) -> int:
    # Alternatively, can use list
    # memo = [0] * (n + 1)
    # if memo[curr_step] > 0:
    #     return memo[curr_step]
    # memo[curr_step] = recurrence relation
    # return memo[curr_step]
    @cache
    def climb_Stairs(curr_step: int) -> int:
        if curr_step > n:
            return 0

        if curr_step == n:
            return 1

        return climb_Stairs(curr_step + 1) + climb_Stairs(curr_step + 2)

    return climb_Stairs(0)


def climbStairsDS3(n: int) -> int:
    if n == 1:
        return 1

    dp = [0] * (n + 1)
    dp[1] = 1
    dp[2] = 2

    for curr_step in range(3, n + 1):
        dp[curr_step] = dp[curr_step - 1] + dp[curr_step - 2]

    return dp[n]


def climbStairsDS4(n: int) -> int:
    if n == 1:
        return 1

    first = 1
    second = 2

    for curr_step in range(3, n + 1):
        third = first + second
        first = second
        second = third

    return second


def climbStairsDS5(n: int) -> int:
    sqrt5 = math.sqrt(5)
    phi = (1 + sqrt5) / 2
    psi = (1 - sqrt5) / 2

    return math.floor((phi ** (n + 1) - psi ** (n + 1)) / sqrt5)
