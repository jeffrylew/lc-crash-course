/**
 * @param {number[]} arr
 * @returns {number}
 */
var minSetSizeDS1 = function(arr)
{
    arr.sort((a, b) => a - b);

    const counts = [];
    let currentRun = 1;

    for (let i = 1; i < arr.length; i++)
    {
        if (arr[i] === arr[i - 1])
        {
            currentRun++;
            continue;
        }

        counts.push(currentRun);
        currentRun = 1;
    }
    counts.push(currentRun);

    // Reverse sort counts
    counts.sort((a, b) => b - a);

    let numberOfItemsRemovedFromArr = 0;
    let setSize = 0;

    for (const count of counts)
    {
        numberOfItemsRemovedFromArr += count;
        setSize++;

        if (numberOfItemsRemovedFromArr >= arr.length / 2)
        {
            break;
        }
    }

    return setSize;
};

/**
 * @param {number[]} arr
 * @returns {number}
 */
var minSetSizeDS2 = function(arr)
{
    arr.sort((a, b) => a - b);

    let currentRun = 1;
    let currentRunIdx = 0;

    for (let i = 1; i < arr.length; i++)
    {
        if (arr[i] === arr[i - 1])
        {
            currentRun++;
            continue;
        }

        arr[currentRunIdx++] = currentRun;
        currentRun = 1;
    }
    arr[currentRunIdx++] = currentRun;

    for (let i = currentRunIdx; i < arr.length; i++)
    {
        arr[i] = 0;
    }

    // Reverse sort arr
    arr.sort((a, b) => b - a);

    let numberOfItemsRemovedFromArr = 0;
    let setSize = 0;

    for (const count of arr)
    {
        numberOfItemsRemovedFromArr += count;
        setSize++;

        if (numberOfItemsRemovedFromArr >= arr.length / 2)
        {
            break;
        }
    }

    return setSize;
};

class Counter
{
    static from(array)
    {
        const counter = new Counter();
        for (const item of array)
        {
            counter.add(item);
        }
        return counter;
    }

    _counts = new Map();

    add(item)
    {
        if (!this._counts.has(item))
        {
            this._counts.set(item, 0);
        }
        this._counts.set(item, this._counts.get(item) + 1);
    }

    values()
    {
        return this._counts.values();
    }
}

/**
 * @param {number[]} arr
 * @returns {number}
 */
var minSetSizeDS3 = function(arr)
{
    const counter = Counter.from(arr);

    // Sort element frequencies from largest to smallest
    const counts = Array.from(counter.values()).sort((a, b) => b - a);

    let numberOfItemsRemovedFromArr = 0;
    let setSize = 0;

    for (const count of counts)
    {
        numberOfItemsRemovedFromArr += count;
        setSize++;

        if (numberOfItemsRemovedFromArr >= arr.length / 2)
        {
            break;
        }
    }

    return setSize;
};