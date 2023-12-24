public int minOperationsDS1(String s)
{
    int start0 = 0;
    int start1 = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (i % 2 == 0)
        {
            if (s.charAt(i) == '0')
            {
                start1++;
            }
            else
            {
                start0++;
            }
        }
        else
        {
            if (s.charAt(i) == '1')
            {
                start1++;
            }
            else
            {
                start0++;
            }
        }
    }

    return Math.min(start0, start1);
}

public int minOperationsDS2(String s)
{
    int start0 = 0;

    for (int i = 0; i < s.length(); i++)
    {
        if (i % 2 == 0)
        {
            if (s.charAt(i) == '1')
            {
                start0++;
            }
        }
        else
        {
            if (s.charAt(i) == '0')
            {
                start0++;
            }
        }
    }

    return Math.min(start0, s.length() - start0);
}
