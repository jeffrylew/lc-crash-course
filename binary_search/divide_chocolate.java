public int maximizeSweetness(int[] sweetness, int k)
{
    // Initialize the left and right boundaries
    // left = 1
    // right = total sweetness / number of people
    int numPeople = k + 1;
    int left = Arrays.stream(sweetness).min().getAsInt();
    int right = Arrays.stream(sweetness).sum() / numPeople;

    while (left < right)
    {
        // Get the midle index between left and right boundary indices
        // curSweetness = total sweetness for the current person
        // peopleWithChocolate = number of people that have a piece of
        // chocoloate with sweetness greater than or equal to mid
        int mid = (left + right + 1) / 2;
        int curSweetness = 0;
        int peopleWithChocolate = 0;

        // Start assigning chunks
        for (int chunk_sweetness : sweetness)
        {
            curSweetness += chunk_sweetness;

            // If the total sweetness is no less than mid then
            // move on to assigning chunks for the next person
            if (curSweetness >= mid)
            {
                peopleWithChocolate++;
                curSweetness = 0;
            }
        }

        // Check if we successfully gave everyone a piece of chocolate with
        // sweetness no less than mid and eliminate the search space by half
        if (peopleWithChocolate >= numPeople)
        {
            left = mid;
        }
        else
        {
            right = mid - 1;
        }
    }

    // Once the left and right boundaries coincide, we find the
    // target value which is the maximum possible sweetness
    return right;
}