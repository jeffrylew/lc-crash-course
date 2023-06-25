class Pair
{
    String node;
    double ratio;

    Pair(String node, double ratio)
    {
        this.node = node;
        this.ratio = ratio;
    }
}

class Solution
{
    Map<String, Map<String, Double>> graph = new HashMap<>();

    public double answerQuery(String start, String end)
    {
        // No info on this node
        if (!graph.containsKey(start))
        {
            return -1;
        }

        Set<String> seen = new HashSet<>();
        seen.add(start);

        Stack<Pair> stack = new Stack<>();
        stack.push(new Pair(start, 1));

        while (!stack.empty())
        {
            Pair pair = stack.pop();
            String node = pair.node;
            double ratio = pair.ratio;

            if (node.equals(end))
            {
                return ratio;
            }

            if (graph.containsKey(node))
            {
                for (String neighbor : graph.get(node).keySet())
                {
                    if (!seen.contains(neighbor))
                    {
                        seen.add(neighbor);
                        stack.push(
                            new Pair(neighbor,
                                     ratio * graph.get(node).get(neighbor)));
                    }
                }
            }
        }

        return -1;
    }

    public double[] calcEquation(List<List<String>> equations,
                                 double[]           values,
                                 List<List<String>> queries)
    {
        for (int i = 0; i < equations.size(); i++)
        {
            String numerator = equations.get(i).get(0);
            String denominator = equations.get(i).get(1);
            double val = values[i];

            if (!graph.containsKey(numerator))
            {
                graph.put(numerator, new HashMap<>());
            }

            if (!graph.containsKey(denominator))
            {
                graph.put(denominator, new HashMap<>());
            }

            graph.get(numerator).put(denominator, val);
            graph.get(denominator).put(numerator, 1 / val);
        }

        double[] ans = new double[queries.size()];
        for (int i = 0; i < queries.size(); i++)
        {
            ans[i] = answerQuery(queries.get(i).get(0), queries.get(i).get(1));
        }

        return ans;
    }
}