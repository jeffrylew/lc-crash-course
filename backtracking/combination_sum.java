public void backtrack(List<Integer>       path,
                      int                 start,
                      int                 curr,
                      List<List<Integer>> ans,
                      int[]               candidates,
                      int                 target)
{
    if (curr == target)
    {
        ans.add(new ArrayList<>(path));
        return;
    }

    for (int i = start; i < candidates.length; i++)
    {
        int num = candidates[i];
        if (curr + num <= target)
        {
            path.add(num);
            backtrack(path, i, curr + num, ans, candidates, target);
            path.remove(path.size() - 1);
        }
    }
}

public List<List<Integer>> combinationSum(int[] candidates, int target)
{
    List<List<Integer>> ans = new ArrayList<>();
    backtrack(new ArrayList<>(), 0, 0, ans, candidates, target);
    return ans;
}
