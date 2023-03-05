public int[] dailyTemperatures(int[] temperatures)
{
    Stack<Integer> stack = new Stack<>();
    int[] answer = new int[temperatures.length];

    for (int i = 0; i < temperatures.length; i++)
    {
        while (!stack.empty() && temperatures[stack.peek()] < temperatures[i])
        {
            int j = stack.pop();
            answer[j] = i - j;
        }

        stack.push(i);
    }

    return answer;
}