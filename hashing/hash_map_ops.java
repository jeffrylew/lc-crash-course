public static void main(String[] args)
{
    Map<Integer, Integer> myHashMap = new HashMap<>();

    myHashMap.put(4, 83);
    System.out.println(myHashMap.get(4)); // Prints 83
    System.out.println(myHashMap.containsKey(4)); // Prints true
    System.out.println(myHashMap.containsKey(854)); // Prints false

    myHashMap.put(8, 327);
    myHashMap.put(45, 82523);

    for (int key : myHashMap.keySet())
    {
        System.out.println(String.format("%d: %d", key, myHashMap.get(key)));
    }
}