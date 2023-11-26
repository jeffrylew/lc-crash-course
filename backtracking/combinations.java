public void backtrack(List<List<Integer>> ans,
                      List<Integer>       curr,
                      int                 i,
                      int                 n,
                      int                 k)
{
    if (curr.size() == k)
    {
        ans.add(new ArrayList<>(curr));
        return;
    }

    for (int num = i; num <= n; num++)
    {
        curr.add(num);
        backtrack(ans, curr, num + 1, n, k);
        curr.remove(curr.size() - 1);
    }
}

public List<List<Integer>> combine(int n, int k)
{
    List<List<Integer>> ans = new ArrayList<>();
    backtrack(ans, new ArrayList<>(), 1, n, k);
    return ans;
}
