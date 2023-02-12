public String removeDuplicates(String s)
{
    Stack<Character> stack = new Stack<>();
    for (char c : s.toCharArray())
    {
        if (!stack.empty() && stack.peek() == c)
        {
            stack.pop();
        }
        else
        {
            stack.push(c);
        }
    }

    StringBuilder sb = new StringBuilder();
    while (!stack.empty())
    {
        sb.append(stack.pop());
    }

    return sb.reverse().toString();
}