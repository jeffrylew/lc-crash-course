public int numRescueBoats(int[] people, int limit)
{
    int ans = 0;
    int lightest_idx = 0;
    int heaviest_idx = people.length - 1;
    Arrays.sort(people);

    while (lightest_idx <= heaviest_idx)
    {
        if (people[lightest_idx] + people[heaviest_idx] <= limit)
        {
            lightest_idx++;
        }

        heaviest_idx--;
        ans++;
    }

    return ans;
}