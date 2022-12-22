public boolean checkIfPangram1(String sentence)
{
    Set<Character> seen = new HashSet<>();

    for (char currChar : sentence.toCharArray())
    {
        seen.add(currChar);
    }

    return seen.size() == 26;
}

public boolean checkIfPangram2(String sentence)
{
    boolean[] seen = new boolean[26];

    for (char currChar : sentence.toCharArray())
    {
        seen[currChar - 'a'] = true;
    }

    for (boolean status : seen)
    {
        if (!status)
        {
            return false;
        }
    }

    return true;
}

public boolean checkIfPangram3(String sentence)
{
    int seen = 0;

    for (char currChar : sentence.toCharArray())
    {
        int mappedIndex = currChar - 'a';

        int currBit = 1 << mappedIndex;

        seen |= currBit;
    }

    return seen == (1 << 26) - 1;
}