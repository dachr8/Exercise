//198. House Robber
int rob(int *nums, int numsSize) {
    int a = 0, b = 0;

    for (int i = 0; i < numsSize; i++)
        if (i % 2)
            a = (a + nums[i]) > b ? (a + nums[i]) : b;
        else
            b = (b + nums[i]) > a ? (b + nums[i]) : a;

    return a > b ? a : b;
}
