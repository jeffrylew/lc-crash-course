var minSpeedOnTime = function(dist, hour)
{
    const check = k => {
        let t = 0;
        for (const d of dist)
        {
            t = Math.ceil(t);
            t += d / k;
        }

        return t <= hour;
    }

    if (dist.length > Math.ceil(hour))
    {
        return -1;
    }

    let left = 1;
    let right = Math.pow(10, 7);

    while (left <= right)
    {
        const mid = Math.floor((left + right) / 2);

        if (check(mid))
        {
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }

    return left;
};