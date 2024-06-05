public int[] divisibilityArray(String word, int m)
{
    int n = word.length();
    int[] div = new int[n];
    long curr = 0;

    for (int pos = 0; pos < n; pos++)
    {
        curr = (curr * 10 + (word.charAt(pos) - '0')) % m;

        if (curr == 0)
        {
            div[pos] = 1;
        }
        else
        {
            div[pos] = 0;
        }
    }

    return div;
}
