import java.util.concurrent.ThreadLocalRandom;

class Solution {
    int[][] points;

    public int[][] kClosest(int[][] points, int K) {
        this.points = points;
        int left = 0, right = points.length - 1;
        int oK = K;
        while (left < right) {
            int oleft = left, oright = right;
            int pivot = dist(ThreadLocalRandom.current().nextInt(left, right));
            while (left < right) {
                while (left < right && dist(left) < pivot)
                    left++;
                while (left < right && dist(right) > pivot)
                    right--;
                int[] tmp = points[left];
                points[left] = points[right];
                points[right] = tmp;
            }

            if (K <= left - oleft + 1) {
                left = oleft;
                right = left;
            } else {
                left++;
                right = oright;
                K -= (left - oleft + 1);
            }
        }
        return Arrays.copyOfRange(points, 0, oK);
    }

    public int dist(int i) {
        return points[i][0] * points[i][0] + points[i][1] * points[i][1];
    }
}