const binarySearch = (arr, target) => {
    let left = 0;
    let right = arr.length - 1;

    while (left <= right)
    {
        const mid = Math.floor((left + right) / 2);

        if (arr[mid] == target)
        {
            // Do something
            return mid;
        }

        if (arr[mid] > target)
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    // Target is not in arr but left is at the insertion point
    return left;
};

const binarySearchFirstIndex = (arr, target) => {
    let left = 0;
    let right = arr.length;

    while (left < right)
    {
        const mid = Math.floor((left + right) / 2);

        if (arr[mid] >= target)
        {
            right = mid;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;
};