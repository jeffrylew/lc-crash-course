public boolean canReachBFS(int[] arr, int start)
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

public boolean canReachDFS(int[] arr, int start)
{
    if (start >= 0 && start < arr.length && arr[start] >= 0)
    {
        if (arr[start] == 0)
        {
            return true;
        }

        arr[start] = -arr[start];
        return canReachDFS(arr, start + arr[start])
            || canReachDFS(arr, start - arr[start]);
    }

    return false;
}