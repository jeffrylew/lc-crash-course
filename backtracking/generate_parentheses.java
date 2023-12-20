public boolean isValid(String pString)
{
    int leftCount = 0;
    for (char p : pString.toCharArray())
    {
        if (p == '(')
        {
            leftCount++;
        }
        else
        {
            leftCount--;
        }

        if (leftCount < 0)
        {
            return false;
        }
    }

    return leftCount == 0;
}

public List<String> generateParenthesisDS1(int n)
{
    List<String> answer = new ArrayList<>();
    Queue<String> queue = new LinkedList<>(Arrays.asList(""));

    while (!queue.isEmpty())
    {
        String curString = queue.poll();

        // If the length of curString is 2 * n,
        // add it to answer if it is valid
        if (curString.length() == 2 * n)
        {
            if (isValid(curString))
            {
                answer.add(curString);
            }
            continue;
        }

        queue.offer(curString + ")");
        queue.offer(curString + "(");
    }

    return answer;
}

public void backtrack(List<String> answer,
                     StringBuilder curString,
                     int           leftCount,
                     int           rightCount,
                     int           n)
{
    if (curString.length() == 2 * n)
    {
        answer.add(curString.toString());
        return;
    }

    if (leftCount < n)
    {
        curString.append("(");
        backtrack(answer, curString, leftCount + 1, rightCount, n);
        curString.deleteCharAt(curString.length() - 1);
    }

    if (rightCount < leftCount)
    {
        curString.append(")");
        backtrack(answer, curString, leftCount, rightCount + 1, n);
        curString.deleteCharAt(curString.length() - 1);
    }
}

public List<String> generateParenthesisDS2(int n)
{
    List<String> answer = new ArrayList<>();
    backtrack(answer, new StringBuilder(), 0, 0, n);
    return answer;
}
