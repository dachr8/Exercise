class Solution {
    public int reachNumber(int target) {
        target = Math.abs(target);
        int n = 0;
        while (target > 0)
            target -= ++n;
        return target % 2 == 0 ? n : n + 1 + n % 2;
    }
}