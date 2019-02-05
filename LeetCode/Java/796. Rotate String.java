class Solution {
    public boolean rotateString(String A, String B) {
        int N = A.length();
        if (N != B.length())
            return false;
        if (N == 0)
            return true;

        int[] shifts = new int[N + 1];
        Arrays.fill(shifts, 1);
        int left = -1;
        for (int right = 0; right < N; right++) {
            while (left >= 0 && B.charAt(left) != B.charAt(right))
                left -= shifts[left];
            shifts[right + 1] = right - left++;
        }

        int matchLen = 0;
        for (char c : (A + A).toCharArray()) {
            while (matchLen >= 0 && B.charAt(matchLen) != c)
                matchLen -= shifts[matchLen];
            if (++matchLen == N)
                return true;
        }
        return false;
    }
}