class Solution {
    public int maxDistToClosest(int[] seats) {
        int ans;
        int left = 0, right = seats.length - 1;
        for (; seats[left] != 1 && left <= right; left++) ;
        ans = left;
        for (; seats[right] != 1 && left <= right; right--) ;
        ans = Math.max(ans, seats.length - 1 - right);
        int K = 0;
        for (left++; left <= right; left++)
            if (seats[left] == 0)
                K++;
            else {
                ans = Math.max(ans, (K + 1) / 2);
                K = 0;
            }
        return ans;
    }
}