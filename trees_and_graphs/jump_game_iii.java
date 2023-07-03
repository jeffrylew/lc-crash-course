public boolean canReach(int[] arr, int start)
{
    int n = arr.length;

    Queue<Integer> queue = new LinkedList<>();
    queue.add(start);

    while (not queue.isEmpty())
    {
        int node = queue.poll();

        //! Check if reach zero
        if (arr[node] == 0)
        {
            return true;
        }

        if (arr[node] < 0)
        {
            continue;
        }

        //! Check available next steps
        if (node + arr[node] < n)
        {
            queue.offer(node + arr[node]);
        }

        if (node - arr[node] >= 0)
        {
            queue.offer(node - arr[node]);
        }

        //! Mark as visited
        arr[node] = -arr[node];
    }

    return false;
}