class SolutionDS1
{
    int text1_len;
    int text2_len;
    int[][] memo;
    String text1;
    String text2;

    private int get_lcs(int idx1, int idx2)
    {
        if (idx1 == this.text1_len || idx2 == this.text2_len)
        {
            return 0;
        }

        if (this.memo[idx1][idx2] != -1)
        {
            return this.memo[idx1][idx2];
        }

        int length = 0;

        if (text1.charAt(idx1) == text2.charAt(idx2))
        {
            length = 1 + get_lcs(idx1 + 1, idx2 + 1);
        }
        else
        {
            length = Math.max(get_lcs(idx1 + 1, idx2), get_lcs(idx1, idx2 + 1));
        }

        this.memo[idx1][idx2] = length;
        return length;
    }

    public int longestCommonSubsequence(String text1, String text2)
    {
        this.text1_len = text1.length();
        this.text2_len = text2.length();
        this.text1 = text1;
        this.text2 = text2;
        this.memo = new int[this.text1_len][this.text2_len];

        for (int idx1 = 0; idx1 < this.text1_len; idx1++)
        {
            Arrays.fill(this.memo[idx1], -1);
        }

        return get_lcs(0, 0);
    }
}

public int longestCommonSubsequenceDS2(String text1, String text2)
{
    int text1_len = text1.length();
    int text2_len = text2.length();

    int lcs[][] = new int[text1_len + 1][text2_len + 1];
    for (int idx1 = text1_len - 1; idx1 >= 0; idx1--)
    {
        for (int idx2 = text2_len - 1; idx2 >= 0; idx2--)
        {
            if (text1.charAt(idx1) == text2.charAt(idx2))
            {
                lcs[idx1][idx2] = 1 + lcs[idx1 + 1][idx2 + 1];
            }
            else
            {
                lcs[idx1][idx2] =
                    Math.max(lcs[idx1 + 1][idx2], lcs[idx1][idx2 + 1]);
            }
        }
    }

    return lcs[0][0];
}
