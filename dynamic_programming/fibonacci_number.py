def fibonacci1(n: int) -> int:
    if n == 0:
        return 0

    if n == 1:
        return 1

    return fibonacci1(n - 1) + fibonacci1(n - 2)


memo = {}


def fibonacci2(n: int) -> int:
    if n == 0:
        return 0

    if n == 1:
        return 1

    if n in memo:
        return memo[n]

    memo[n] = fibonacci2(n - 1) + fibonacci2(n - 2)
    return memo[n]


def fibonacci3(n: int) -> int:
    arr = [0] * (n + 1)

    # Base case - the second Fibonacci number is 1
    arr[1] = 1

    for i in range(2, n + 1):
        arr[i] = arr[i - 1] + arr[i - 2]

    return arr[n]
