const buildGraph = edges => {
    let graph = new Map();

    for (const [x, y] of edges)
    {
        if (!graph.has(x))
        {
            graph.set(x, []);
        }

        graph.get(x).push(y);

        // Uncomment following lines if the graph is undirected
        // if (!graph.has(y))
        // {
        //     graph.set(y, []);
        // }

        // graph.get(y).push(x);
    }

    return graph;
}