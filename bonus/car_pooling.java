public boolean carPooling(int[][] trips, int capacity)
{
    int farthest = 0;
    for (int trip = 0; trip < trips.length; trip++)
    {
        farthest = Math.max(farthest, trips[trip][2]);
    }

    int[] change_in_passengers = new int[farthest + 1];
    for (int trip = 0; trip < trips.length; trip++)
    {
        int num_passengers = trips[trip][0];
        int left = trips[trip][1];
        int right = trips[trip][2];

        change_in_passengers[left] += num_passengers;
        change_in_passengers[right] -= num_passengers;
    }

    int curr_passengers = 0;
    for (int position = 0; position < change_in_passengers.length; position++)
    {
        curr_passengers += change_in_passengers[position];
        if (curr_passengers > capacity)
        {
            return false;
        }
    }

    return true;
}
