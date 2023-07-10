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