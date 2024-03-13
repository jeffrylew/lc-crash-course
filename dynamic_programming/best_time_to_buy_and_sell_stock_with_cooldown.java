public int maxProfitDS1(int[] prices)
{
    int sold = Integer.MIN_VALUE;
    int held = Integer.MIN_VALUE;
    int reset = 0;

    for (int price : prices)
    {
        int pre_sold = sold;

        sold = held + price;
        held = Math.max(held, reset - price);
        reset = Math.max(reset, pre_sold);
    }

    return Math.max(sold, reset);
}
