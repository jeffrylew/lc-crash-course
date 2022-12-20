var minStartValue = function(nums) {
    let minVal = 0;
    let total = 0;

    for (let i = 0; i < nums.length; ++i)
    {
        total += nums[i];
        minVal = Math.min(minVal, total);
    }

    return 1 - minVal;
}