def fibonacci1(n: int) -> int:
    if n == 0:
        return 0

    if n == 1:
        return 1

    return fibonacci1(n - 1) + fibonacci1(n - 2)
