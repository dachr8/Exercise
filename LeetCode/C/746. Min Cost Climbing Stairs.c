//746. Min Cost Climbing Stairs
int minCostClimbingStairs(int *cost, int costSize) {
    int f0, f1 = 0, f2 = 0;

    for (int i = costSize - 1; i >= 0; --i) {
        f0 = cost[i] + (f1 < f2 ? f1 : f2);
        f2 = f1;
        f1 = f0;
    }
    
    return f1 < f2 ? f1 : f2;
}
