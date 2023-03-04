class MovingAverage
{
    int size, windowSumDS1 = 0, countDS1 = 0;
    Deque queueDS1 = new ArrayDeque<Integer>();

    public MovingAverage(int size)
    {
        this.size = size;
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
}