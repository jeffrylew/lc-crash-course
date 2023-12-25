public void backtrack(int                 remain,
                      int                 k,
                      LinkedList<Integer> comb,
                      int                 next_start,
                      List<List<Integer>> results)
{
    if (remain == 0 && comb.size() == k)
    {
        // Note: It's important to make a deep copy here otherwise the
        // combination would be reverted in another branch of backtracking
        results.add(new ArrayList<Integer>(comb));
        return;
    }
    else if (remain < 0 || comb.size() == k)
    {
        // Exceeded the scope, no need to explore further
        return;
    }

    // Iterate through the reduced list of candidates
    for (int i = next_start; i < 9; ++i)
    {
        comb.add(i + 1);
        backtrack(remain - i - 1, k, comb, i + 1, results);
        comb.removeLast();
    }
}

public List<List<Integer>> combinationSum3DS1(int k, int n)
{
    List<List<Integer>> results = new ArrayList<List<Integer>>();
    LinkedList<Integer> comb = new LinkedList<Integer>();

    backtrack(n, k, comb, 0, results);
    return results;
}
