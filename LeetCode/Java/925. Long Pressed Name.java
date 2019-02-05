class Solution {
    public boolean isLongPressedName(String name, String typed) {
        int i = 0;
        for (char c : name.toCharArray()) {
            if (i == typed.length())
                return false;
            if (typed.charAt(i) != c) {
                if (i == 0 || typed.charAt(i - 1) != typed.charAt(i))
                    return false;
                char cur = typed.charAt(i);
                while (i < typed.length() && typed.charAt(i) == cur)
                    i++;
                if (i == typed.length() || typed.charAt(i) != c)
                    return false;
            }
            i++;
        }
        return true;
    }
}