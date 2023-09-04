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