// Use PriorityQueue interface and PriorityQueue implementation
// By default, this implements a min heap
PriorityQueue<Integer> heap = new PriorityQueue<>();

// Add to heap
heap.add(1);
heap.add(2);
heap.add(3);

// Check minimum element
heap.peek(); // 1

// Pop minimum element
heap.remove(); // 1

// Get size
heap.size(); // 2

// If want a max heap instead, can pass Comparator.reverseOrder() to constructor
PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());

public class Example
{
    public static void main(String[] args)
    {
        PriorityQueue<integer> minHeap = new PriorityQueue<>();
        int[] nums = {67, 341, 234, -67, 12, -976};

        for (int num : nums)
        {
            minHeap.add(num);
        }

        minHeap.add(7451);
        minHeap.add(-5352);

        // The numbers will be printed in sorted order
        while (!heap.isEmpty())
        {
            System.out.println(heap.remove());
        }
    }
}