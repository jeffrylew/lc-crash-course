const missingNumber = (nums) => {
    const numSet = new Set();
    for (const num of nums)
    {
        numSet.add(num);
    }

    const expectedNumCount = nums.length + 1;
    for (let number = 0; number < expectedNumCount; number++)
    {
        if (!numSet.has(number))
        {
            return number;
        }
    }

    return -1;
}