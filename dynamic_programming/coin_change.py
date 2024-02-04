from functools import cache


def coinChangeDS1(coins: list[int], amount: int) -> int:
    def get_min_coins(remaining_amt: int) -> int:
        if remaining_amt < 0:
            return -1

        if remaining_amt == 0:
            return 0

        min_count = amount + 1
        for coin in coins:
            count = get_min_coins(remaining_amt - coin)

            if count == -1:
                continue

            min_count = min(min_count, count + 1)

        return -1 if min_count == (amount + 1) else min_count

    return get_min_coins(amount)


def coinChangeDS2(coins: list[int], amount: int) -> int:
    @cache
    def get_min_coins(remaining_amt: int) -> int:
        if remaining_amt < 0:
            return -1

        if remaining_amt == 0:
            return 0

        min_count = amount + 1
        for coin in coins:
            count = get_min_coins(remaining_amt - coin)

            if count == -1:
                continue

            min_count = min(min_count, count + 1)

        return -1 if min_count == (amount + 1) else min_count

    return get_min_coins(amount)


def coinChangeDS3(coins: list[int], amount: int) -> int:
    dp = [amount + 1] * (amount + 1)
    dp[0] = 0

    for remaining_amt in range(1, amount + 1):
        for coin in coins:
            if remaining_amt - coin < 0:
                continue

            dp[remaining_amt] = min(
                dp[remaining_amt], dp[remaining_amt - coin] + 1
            )

    return -1 if dp[amount] == (amount + 1) else dp[amount]
