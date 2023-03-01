public String makeGood(String s)
{
    // Use stack to store the visited characters
    Stack<Character> stack = new Stack<>();

    // Iterate over s
    for (char currChar : s.toCharArray())
    {
        // If the current character makes a pair with the last char in the stack
        // remove both of them. Else, add current char to stack
        if (!stack.isEmpty() && Math.abs(stack.lastElement() - currChar) == 32)
        {
            stack.pop();
        }
        else
        {
            stack.add(currChar);
        }
    }

    // Return string concatenated by all chars left in stack
    StringBuilder ans = new StringBuilder();
    for (char currChar : stack)
    {
        ans.append(currChar);
    }
    return ans.toString();
}