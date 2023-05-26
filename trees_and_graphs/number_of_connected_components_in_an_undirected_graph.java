public void dfs(List<Integer>[] adjList, boolean[] visited, int startNode)
{
    visited[startNode] = true;

    for (int i = 0; i < adjList[startNode].size(); i++)
    {
        if (visited[adjList[startNode].get(i)] == 0)
        {
            dfs(adjList, visited, adjList[startNode].get(i));
        }
    }
}

public int countComponents(int n, int[][] edges)
{
    int components = 0;
    int[] visited = new int[n];

    List<Integer>[] adjList = new ArrayList[n];
    for (int i = 0; i < n; i++)
    {
        adjList[i] = new ArrayList<Integer>();
    }

    for (int i = 0; i < edges.length; i++)
    {
        adjList[edges[i][0]].add(edges[i][1]);
        adjList[edges[i][1]].add(edges[i][0]);
    }

    for (int i = 0; i < n; i++)
    {
        if (!visited[i])
        {
            components++;
            dfs(adjList, visited, i);
        }
    }

    return components;
}