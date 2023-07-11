public int ladderLength(String beginWord, String endWord, List<String> wordList)
{
    // All words are same length
    int L = beginWord.length();

    // Map holding combination of words that can be formed from any given word
    // by changing one letter at a time
    Map<String, List<String>> allComboDict = new HashMap<>();

    wordList.forEach(word -> {
        for (int i = 0; i < L; i++)
        {
            // Key is the generic word
            // Value is list of words that have same intermediate generic word
            String newWord =
                word.substring(0, i) + '*' + word.substring(i + 1, L);
            
            List<String> transformations =
                allComboDict.getOrDefault(newWord, new ArrayList<>());
            
            transformations.add(word);
            allComboDict.put(newWord, transformations);
        }
    });

    // Queue for BFS
    Queue<Pair<String, Integer>> queue = new LinkedList<>();
    queue.add(new Pair(beginWord, 1));

    // visited to avoid processing same word
    Map<String, Boolean> visited = new HashMap<>();
    visited.put(beginWord, true);

    while (!queue.isEmpty())
    {
        Pair<String, Integer> node = queue.remove();
        String word = node.getKey();
        int level = node.getValue();

        for (int i = 0; i < L; i++)
        {
            // Intermediate words for current word
            String newWord =
                word.substring(0, i) + '*' + word.substring(i + 1, L);
            
            // Next states are all words that share same intermediate state
            for (String adjacentWord
                : allComboDict.getOrDefault(newWord, new ArrayList<>()))
            {
                if (adjacentWord.equals(endWord))
                {
                    return level + 1;
                }

                if (!visited.containsKey(adjacentWord))
                {
                    visited.put(adjacentWord, true);
                    queue.add(new Pair(adjacentWord, level + 1));
                }
            }
        }
    }

    return 0;
}

class Solution
{
    private int L;
    private Map<String, List<String>> allComboDict;

    Solution()
    {
        this.L = 0;

        this.allComboDict = new HashMap<>();
    }

    private int visitWordNode(
        Queue<Pair<String, Integer>> queue,
        Map<String, Integer> visited,
        Map<String, Integer> othersVisited)
    {
        int initQueueLen = queue.length();

        for (int j = 0; j < initQueueLen; j++)
        {
            Pair<String, Integer> node = queue.remove();
            String word = node.getKey();
            int level = node.getValue();

            for (int i = 0; i < this.L; i++)
            {
                String newWord =
                    word.substring(0, i) + '*' + word.substring(i + 1, L);
                
                for (String adjacentWord
                    : this.allComboDict.getOrDefault(newWord, new ArrayList<>()))
                {
                    if (othersVisited.containsKey(adjacentWord))
                    {
                        return level + othersVisited.get(adjacentWord);
                    }

                    if (!visited.containsKey(adjacentWord))
                    {
                        visited.put(adjacentWord, level + 1);
                        queue.add(new Pair(adjacentWord, level + 1));
                    }
                }
            }
        }

        return -1;
    }

    public int ladderLengthBidirBFS(
        String       beginWord,
        String       endWord,
        List<String> wordList)
    {
        if (!wordList.contains(endWord))
        {
            return 0;
        }

        this.L = beginWord.length();

        wordList.forEach( word -> {
            for (int i = 0; i < L; i++)
            {
                String newWord =
                    word.substring(0, i) + '*' + word.substring(i + 1, L);
                
                List<String> transformations =
                    this.allComboDict.getOrDefault(newWord, new ArrayList<>());
                transformations.add(word);

                this.allComboDict.put(newWord, transformations);
            }
        });

        Queue<Pair<String, Integer>> qBegin = new LinkedList<>();
        Queue<Pair<String, Integer>> qEnd = new LinkedList<>();

        qBegin.add(new Pair(beginWord, 1));
        qEnd.add(new Pair(endWord, 1));

        Map<String, Integer> visitedBegin = new HashMap<>();
        Map<String, Integer> visitedEnd = new HashMap<>();

        visitedBegin.put(beginWord, 1);
        visitedEnd.put(endWord, 1);

        int ans = -1;

        while (!qBegin.isEmpty() && !qEnd.isEmpty())
        {
            if (qBegin.size() <= qEnd.size())
            {
                ans = visitWordNode(qBegin, visitedBegin, visitedEnd);
            }
            else
            {
                ans = visitWordNode(qEnd, visitedEnd, visitedBegin);
            }

            if (ans > -1)
            {
                return ans;
            }
        }

        return 0;
    }
}