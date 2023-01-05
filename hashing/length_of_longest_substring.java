public int lengthOfLongestSubstring(String s)
{
    int substr_len = 0;
    int left = 0;

    // Current index of character
    Map<Character, Integer> char_idx = new HashMap<>();

    // Try to extend the range [left, right]
    for (int right = 0; right < s.length(); right++)
    {
        if (char_idx.containsKey(s.charAt(right)))
        {
            left = Math.max(char_idx.get(s.charAt(right)), left);
        }

        substr_len = Math.max(substr_len, right - left + 1);
        char_idx.put(s.charAt(right), right + 1);
    }

    return substr_len;
}