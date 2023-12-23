public void DFS(int remaining_N_digits, int num, int K, List<Integer> results)
{
    if (remaining_N_digits == 0)
    {
        results.add(num);
        return;
    }

    List<Integer> nextDigits = new ArrayList<>();
    Integer tailDigit = num % 10;
    nextDigits.add(tailDigit + K);
    if (K != 0)
    {
        nextDigits.add(tailDigit - K);
    }

    for (Integer nextDigit : nextDigits)
    {
        if (0 <= nextDigit && nextDigit < 10)
        {
            Integer newNum = num * 10 + nextDigit;
            DFS(remaining_N_digits - 1, newNum, K, results);
        }
    }
}

public int[] numsSameConsecDiffDS1(int n, int k)
{
    if (n == 1)
    {
        return new int[] {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    }

    List<Integer> results = new ArrayList<Integer>();
    for (int num = 1; num < 10; ++num)
    {
        DFS(n - 1, num, k, results);
    }

    // Convert ArrayList to int[]
    return results.stream().mapToInt(i -> i).toArray();
}
