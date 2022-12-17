public int findLengthOfBinaryStr(String s)
{
    int left = 0;
    int curr = 0;
    int max_substr_length = 0;

    for (int right = 0; right < s.length(); right++)
    {
        if (s.charAt(right) == '0')
        {
            curr++;
        }

        while (curr > 1)
        {
            if (s.charAt(left) == '0')
            {
                curr--;
            }
            left++;
        }

        max_substr_length = Math.max(max_substr_length, right - left + 1);
    }

    return max_substr_length;
}