public int snakesAndLaddersBFS(int[][] board)
{
    int n = board.length;
    Pair<Integer, Integer>[] cells = new Pair[n * n + 1];

    int label = 1;
    Integer[] columns = new Integer[n];
    for (int i = 0; i < n; i++)
    {
        columns[i] = i;
    }

    for (int row = n - 1; row >= 0; row--)
    {
        for (int column : columns)
        {
            cells[label++] = new Pair<>(row, column);
        }
        Collections.reverse(Arrays.asList(columns));
    }

    int[] dist = new int[n * n + 1];
    Arrays.fill(dist, -1);
    dist[1] = 0;

    Queue<Integer> queue = new LinkedList<Integer>();
    queue.add(1);

    while (!queue.isEmpty())
    {
        int curr = queue.remove();

        for (int next = curr + 1; next <= Math.min(curr + 6, n * n); next++)
        {
            int row = cells[next].getKey();
            int col = cells[next].getValue();
            
            int destination = board[row][col] != -1 ? board[row][col] : next;

            if (dist[destination] == -1)
            {
                dist[destination] = dist[curr] + 1;
                queue.add(destination);
            }
        }
    }

    return dist[n * n];
}

public int snakesAndLaddersDijkstra(int[][] board)
{
    int n = board.length;
    Pair<Integer, Integer>[] cells = new Pair[n * n + 1];

    int label = 1;
    Integer[] columns = new Integer[n];
    for (int i = 0; i < n; i++)
    {
        columns[i] = i;
    }

    for (int row = n - 1; row >= 0; row--)
    {
        for (int column : columns)
        {
            cells[label++] = new Pair<>(row, column);
        }
        Collections.reverse(Arrays.asList(columns));
    }

    int[] dist = new int[n * n + 1];
    Arrays.fill(dist, -1);
    dist[1] = 0;

    class Vertex implement Comparable<Vertex>
    {
        int distance;
        int label;

        public Vertex(int distance, int label)
        {
            this.distance = distance;
            this.label = label;
        }

        public int compareTo(Vertex v)
        {
            return this.distance - v.distance;
        }
    }

    PriorityQueue<Vertex> queue = new PriorityQueue<Vertex>();
    queue.add(new Vertex(0, 1));

    while (!queue.isEmpty())
    {
        Vertex vertex = queue.remove();

        int d = vertex.distance;
        int curr = vertex.label;

        if (d != dist[curr])
        {
            continue;
        }

        for (int next = curr + 1; next <= Math.min(curr + 6, n * n); next++)
        {
            int row = cells[next].getKey();
            int col = cells[next].getValue();

            int destination = board[row][col] != -1 ? board[row][col] : next;

            if (dist[destination] == -1 || dist[curr] + 1 < dist[destination])
            {
                dist[destination] = dist[curr] + 1;
                queue.add(new Vertex(dist[destination], destination));
            }
        }
    }

    return dist[n * n];
}