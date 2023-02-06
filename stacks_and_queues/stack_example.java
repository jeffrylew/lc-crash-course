public class Example
{
    public static void main(String[] args)
    {
        Stack<Integer> stack = new Stack<>();

        stack.push(1);
        stack.push(2);
        stack.push(3);

        System.out.println(stack.pop());
        System.out.println(stack.pop());
        System.out.println(stack.pop());

        stack.push(5);

        if (stack.empty())
        {
            System.out.println("Stack is empty");
        }
        else
        {
            System.out.println(String.format("Stack is not empty, top is: %d", stack.peek()));
        }
    }
}