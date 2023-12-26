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

public int fibonacci3(int n)
{
    int[] arr = new int[n + 1];

    // Base case - the second Fibonacci number is 1
    arr[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        arr[i] = arr[i - 1] + arr[i - 2];
    }

    return arr[n];
}
