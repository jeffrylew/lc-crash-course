var minimumCardPickup1 = function(cards) {
    let dic = new Map();
    for (let i = 0; i < cards.length; i++)
    {
        const num = cards[i];
        if (!dic.has(num))
        {
            dic.set(num, []);
        }
        dic.get(num).push(i);
    }

    let ans = Infinity;
    for (const [key, arr] of dic)
    {
        for (let i = 1; i < arr.length; i++)
        {
            ans = Math.min(ans, arr[i] - arr[i - 1] + 1);
        }
    }

    return ans == Infinity ? -1 : ans;
}