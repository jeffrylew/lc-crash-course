var findLeastNumOfUniqueInts = function(arr, k)
{
    let counts = new Map();

    for (const num of arr)
    {
        counts.set(num, (counts.get(num) || 0) + 1);
    }

    let ordered = [];
    for (const val of counts.values())
    {
        ordered.push(val);
    }

    ordered.sort((a, b) => b - a);
    while (k > 0)
    {
        let val = ordered[ordered.length - 1];
        if (val <= k)
        {
            k -= val;
            ordered.pop();
        }
        else
        {
            break;
        }
    }

    return ordered.length;
}