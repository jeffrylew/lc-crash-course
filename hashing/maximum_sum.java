public int getDigitSum(int num)
{
    int digitSum = 0;
    while (num > 0)
    {
        digitSum += num % 10;
        num /= 10;
    }

    return digitSum;
}

public int maximumSum1(int[] nums)
{
    Map<Integer, List<Integer>> dic = new HashMap<>();
    for (int num : nums)
    {
        int digitSum = getDigitSum(num);
        if (!dic.containsKey(digitSum))
        {
            dic.put(digitSum, new ArrayList<Integer>());
        }
        dic.get(digitSum).add(num);
    }

    int ans = -1;
    for (int key : dic.keySet())
    {
        List<Integer> curr = dic.get(key);
        if (curr.size() > 1)
        {
            Collections.sort(curr, Collections.reverseOrder());
            ans = Math.max(ans, curr.get(0) + curr.get(1));
        }
    }

    return ans;
}

public int maximumSum2(int[] nums)
{
    Map<Integer, Integer> dic = new HashMap<>();

    int ans = -1;

    for (int num : nums)
    {
        int digitSum = getDigitSum(num);
        if (dic.containsKey(digitSum))
        {
            ans = Math.max(ans, num + dic.get(digitSum));
        }
        dic.put(digitSum, Math.max(dic.getOrDefault(digitSum, 0), num));
    }

    return ans;
}
