//70. Climbing Stairs
int climbStairs(int n) {
    if (n == 1)
        return 1;

    int first = 1, second = 2, third;

    for (int i = 3; i <= n; i++) {
        third = first + second;
        first = second;
        second = third;
    }

    return second;
}
