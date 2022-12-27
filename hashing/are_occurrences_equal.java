public boolean areOccurrencesEqual(String s)
{
    Map<Character, Integer> counts = new HashMap<>();
    for (char c : s.toCharArray())
    {
        counts.put(c, counts.getOrDefault(c, 0) + 1);
    }

    Set<Integer> frequencies = new HashSet<>(counts.values());
    return frequencies.size() == 1;
}