public List<List<String>> groupAnagrams(String[] strs)
{
    Map<String, List<String>> groups = new HashMap<>();
    for (String s : strs)
    {
        char[] arr = s.toCharArray();
        Arrays.sort(arr);
        String key = new String(arr);

        if (!groups.containsKey(key))
        {
            groups.put(key, new ArrayList<String>());
        }

        groups.get(key).add(s);
    }

    return new ArrayList(groups.values());
}