public int[] findNumbers(int[] nums)
{
    List<Integer> ans     = new ArrayList<>();
    Set<Integer>  numsSet = new HashSet<>();

    for (int num : nums)
    {
        numsSet.add(num);
    }

    for (int num : nums)
    {
        if (!numsSet.contains(num + 1) && !numsSet.contains(num - 1))
        {
            ans.add(num);
        }
    }

    return ans;
}