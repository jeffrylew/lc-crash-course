public Map<Character, Integer> makeCountsMap(String s)
{
    Map<Character, Integer> counts = new HashMap<>();
    for (char c : s.toCharArray())
    {
        int currentCount = counts.getOrDefault(c, 0);
        counts.put(c, currentCount + 1);
    }

    return counts;
}

public boolean canConstruct(String ransomNote, String magazine)
{
    if (ransomNote.length() > magazine.length())
    {
        return false;
    }

    // Make a counts map for the magazine
    Map<Character, Integer> magazineCounts = makeCountsMap(magazine);

    // For each character in the ransom note:
    for (char c : ransomNote.toCharArray())
    {
        // Get current count for c in magazine
        int countInMagazine = magazineCounts.getOrDefault(c, 0);

        // If there are none of c left, return false
        if (countInMagazine == 0)
        {
            return false;
        }

        // Put updated count for c back into magazineCounts
        magazineCounts.put(c, countInMagazine - 1);
    }

    // If we got this far, can successfully build note
    return true;
}