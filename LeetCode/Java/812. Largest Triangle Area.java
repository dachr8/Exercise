class Solution {
    public double largestTriangleArea(int[][] points) {
        int N = points.length;
        double ans = 0;
        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                for (int k = j + 1; k < N; k++)
                    ans = Math.max(ans, 0.5 * Math.abs(points[i][0] * points[j][1] + points[j][0] * points[k][1] + points[k][0] * points[i][1]
                            - points[i][1] * points[j][0] - points[j][1] * points[k][0] - points[k][1] * points[i][0]));
        return ans;
    }
}