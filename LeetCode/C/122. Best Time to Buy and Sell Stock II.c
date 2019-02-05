//122. Best Time to Buy and Sell Stock II
int maxProfit(int *prices, int pricesSize) {
    int max = 0;
    
    for (int i = 1; i < pricesSize; i++)
        if (prices[i] - prices[i - 1] > 0)
            max += (prices[i] - prices[i - 1]);

    return max;
}
