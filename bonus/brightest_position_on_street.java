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

    Collections.sort(brightness_changes, (a, b) -> Integer.compare(a[0], b[0]));

    int brightest_pos = 0;
    int curr_brightness = 0;
    int max_brightness = 0;

    for (int idx = 0; idx < brightess_changes.size(); idx++)
    {
        int position = brightess_changes.get(idx)[0];
        int brightness = brightess_changes.get(idx)[1];

        curr_brightness += brightness;
        if (curr_brightness > max_brightness)
        {
            max_brightness = curr_brightness;
            brightest_pos = position;
        }
    }

    return brightest_pos;
}
