public int numJewelsInStones(String jewels, String stones)
{
    Set<Character> jewelSet = new HashSet<>();
    for (char c : jewels.toCharArray())
    {
        jewelSet.add(c);
    }

    int num_jewels = 0;
    for (char c : stones.toCharArray())
    {
        if (jewelSet.contains(c))
        {
            num_jewels++;
        }
    }

    return num_jewels;
}