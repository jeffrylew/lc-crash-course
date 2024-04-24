public int findBrightestPosition(int[][] lights)
{
    List<int[]> brightness_changes = new ArrayList<int[]>();
    for (int idx = 0; idx < lights.length; idx++)
    {
        int position = lights[idx][0];
        int radius = lights[idx][1];

        brightness_changes.add(new int[] {position - radius, 1});
        brightness_changes.add(new int[] {position + radius + 1, -1});
    }

    // Discussion solution is incorrect since Collections.sort needs to account
    // for both elements of each int[] in brightness_changes. Incorrect solution
    // at https://leetcode.com/explore/interview/card
    //    /leetcodes-interview-crash-course-data-structures-and-algorithms/714
    //    /bonus/4688/
    // and is commented out in the following two lines
    // Collections.sort(
    //    brightness_changes, (lhs, rhs) -> Integer.compare(lhs[0], rhs[0]));
    Collections.sort(brightness_changes, new Comparator<int[]>() {
        public int compare(int[] lhs, int[] rhs) {
            if (lhs[0] == rhs[0])
            {
                return Integer.compare(lhs[1], rhs[1]);
            }

            return Integer.compare(lhs[0], rhs[0]);
        }});

    int brightest_pos = 0;
    int curr_brightness = 0;
    int max_brightness = 0;

    for (int idx = 0; idx < brightness_changes.size(); idx++)
    {
        int position = brightness_changes.get(idx)[0];
        int brightness = brightness_changes.get(idx)[1];

        curr_brightness += brightness;
        if (curr_brightness > max_brightness)
        {
            max_brightness = curr_brightness;
            brightest_pos = position;
        }
    }

    return brightest_pos;
}
