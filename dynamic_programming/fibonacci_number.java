public int fibonacci1(int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    return fibonacci1(n - 1) + fibonacci1(n - 2);
}

Map<Integer, Integer> memo = new HashMap<>();

public int fibonacci2(int n)
{
    if (n == 0)
    {
        return 0;
    }

    if (n == 1)
    {
        return 1;
    }

    if (memo.containsKey(n))
    {
        return memo.get(n);
    }

    memo.put(n, fibonacci2(n - 1) + fibonacci2(n - 2));
    return memo.get(n);
}
