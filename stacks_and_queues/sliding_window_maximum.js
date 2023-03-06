var maxSlidingWindow = function(nums, k)
{
    let ans = [];
    let queue = [];

    for (let i = 0; i < nums.length; i++)
    {
        // Maintain monotonically decreasing queue
        // All elements in the queue smaller than the current one have no
        // chance of being the maximum so get rid of them
        while (queue.length && nums[i] > nums[queue[queue.length - 1]])
        {
            queue.pop();
        }

        queue.push(i);

        // queue[0] is the index of the maximum element
        // if queue[0] + k == i then it is outside the window
        if (queue[0] + k == i)
        {
            queue.shift();
        }

        // Only add to answer once our window has reached size k
        if (i >= k - 1)
        {
            ans.push(nums[queue[0]]);
        }
    }

    return ans;
};