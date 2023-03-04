class MovingAverage
{
    int size, windowSumDS1 = 0, countDS1 = 0;
    Deque queueDS1 = new ArrayDeque<Integer>();

    int headDS2 = 0, windowSumDS2 = 0, countDS2 = 0;
    int[] queueDS2;

    public MovingAverage(int size)
    {
        this.size = size;
        queueDS2 = new int[size];
    }

    // Double-ended queue discussion solution
    public double nextDS1(int val)
    {
        // Time complexity O(1)
        // Space complexity O(N) where N is size of moving window

        ++countDS1;

        // Calculate the new sum by shifting the window
        queueDS1.add(val);
        int tail = countDS1 > size ? (int)queueDS1.poll() : 0;

        windowSumDS1 = windowSumDS1 - tail + val;

        return windowSumDS1 * 1.0 / Math.min(size, countDS1);
    }

    // Circular queue discussion solution
    public double next(int val)
    {
        // Time complexity O(1)
        // Space complexity O(N) where N is size of circular queue

        ++countDS2;

        // Calculate the new sum by shifting the window
        int tail = (headDS2 + 1) % size;
        windowSumDS2 = windowSumDS2 - queueDS2[tail] + val;

        // Move on to the next head
        headDS2 = tail;
        queueDS2[headDS2] = val;

        return windowSumDS2 * 1.0 / Math.min(size, countDS2);
    }
}