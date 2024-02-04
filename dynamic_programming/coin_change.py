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
