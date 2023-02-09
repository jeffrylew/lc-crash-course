public boolean isValid(String s)
{
    Map<Character, Character> matching = new HashMap();
    matching.put('(', ')');
    matching.put('[', ']');
    matching.put('{', '}');

    Stack<Character> stack = new Stack<>();
    for (char c : s.toCharArray())
    {
        // If c is an opening bracket
        if (matching.containsKey(c))
        {
            stack.push(c);
        }
        else
        {
            if (stack.empty())
            {
                return false;
            }

            char previousOpening = stack.pop();
            if (matching.get(previousOpening) != c)
            {
                return false;
            }
        }
    }

    return stack.empty();
}