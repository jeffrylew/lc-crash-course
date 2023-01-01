public int minimumCardPickup1(int[] cards)
{
    Map<Integer, List<Integer>> dic = new HashMap<>();
    for (int i = 0; i < cards.length; i++)
    {
        int num = cards[i];
        if (!dic.containsKey(num))
        {
            dic.put(num, new ArrayList<Integer>());
        }
        dic.get(num).add(i);
    }

    int ans = Integer.MAX_VALUE;
    for (int key : dic.keySet())
    {
        List<Integer> arr = dic.get(key);
        for (int i = 1; i < arr.size(); i++)
        {
            ans = Math.min(ans, arr.get(i) - arr.get(i - 1) + 1);
        }
    }

    if (ans == Integer.MAX_VALUE)
    {
        return -1;
    }

    return ans;
}

public int minimumCardPickup2(int[] cards)
{
    Map<Integer, Integer> dic = new HashMap<>();
    
    int ans = Integer.MAX_VALUE;

    for (int i = 0; i < cards.length; i++)
    {
        int num = cards[i];
        if (dic.containsKey(num))
        {
            ans = Math.min(ans, i - dic.get(num) + 1);
        }

        dic.put(num, i);
    }

    if (ans == Integer.MAX_VALUE)
    {
        return -1;
    }

    return ans;
}