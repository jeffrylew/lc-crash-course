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
