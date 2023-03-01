public static void main(String[] args)
{
    Queue<Integer> queue = new LinkedList<>();

    queue.offer(1);
    queue.offer(2);
    queue.offer(3);

    while (!queue.isEmpty())
    {
        // poll() removes and returns from the front of the queue
        System.out.println(queue.poll());
    }

    if (queue.isEmpty())
    {
        System.out.println("Queue is empty!");
    }
}