const countElements = (arr) => {
    const numSet = new Set();
    for (const x of arr)
    {
        numSet.add(x);
    }

    let count = 0;
    for (const x of arr)
    {
        if (numSet.has(x + 1))
        {
            count++;
        }
    }

    return count;
}