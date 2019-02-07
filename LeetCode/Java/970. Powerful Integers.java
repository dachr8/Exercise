class Solution {
    public List<Integer> powerfulIntegers(int x, int y, int bound) {
        Set<Integer> seen = new HashSet();
        int xi = 1;
        for (int i = 0; i < 20 && xi <= bound; i++, xi *= x) {
            int yj = 1;
            for (int j = 0; j < 20 && xi + yj <= bound; j++, yj *= y)
                if (xi + yj <= bound)
                    seen.add(xi + yj);
        }
        return new ArrayList(seen);
    }
}