var checkForTarget = function(nums, target) {
    let left = 0;
    let right = nums.length - 1;

    while (left < right)
    {
        let curr = nums[left] + nums[right];
        if (curr == target)
        {
            return true;
        }

        if (curr > target)
        {
            right--;
        }
        else
        {
            left++;
        }
    }

    return false;
}