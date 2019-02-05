class Solution {
    public int[] fairCandySwap(int[] A, int[] B) {
        int sa = 0;
        for (int x : A)
            sa += x;
        int sb = 0;
        Set<Integer> setB = new HashSet();
        for (int x : B) {
            sb += x;
            setB.add(x);
        }
        int delta = (sb - sa) / 2;
        for (int x : A)
            if (setB.contains(x + delta))
                return new int[]{x, x + delta};
        throw null;
    }
}