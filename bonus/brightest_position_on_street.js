/**
 * @param {number[][]} lights
 * @returns {number}
 */
var findBrightestPosition = function(lights)
{
    let brightness_changes = [];
    for (const [position, radius] of lights)
    {
        brightness_changes.push([position - radius, 1]);
        brightness_changes.push([position + radius + 1, -1]);
    }

    // Discussion solution is incorrect since sort() needs to account for both
    // elements of each array in brightness_changes.
    // Incorrect solution is commented out in the following line
    // brightness_changes.sort((lhs, rhs) => lhs[0] - rhs[0]);
    brightness_changes.sort((lhs, rhs) => {
        if (lhs[0] == rhs[0])
        {
            return lhs[1] - rhs[1];
        }
        return lhs[0] - rhs[0];
    });

    let brightest_pos = 0;
    let curr_brightness = 0;
    let max_brightness = 0;

    for (const [position, brightness] of brightness_changes)
    {
        curr_brightness += brightness;
        if (curr_brightness > max_brightness)
        {
            max_brightness = curr_brightness;
            brightest_pos = position;
        }
    }

    return brightest_pos;
};
