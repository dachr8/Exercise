class Solution {
    public String mostCommonWord(String paragraph, String[] banned) {
        paragraph += ".";
        Set<String> banset = new HashSet();
        for (String word : banned)
            banset.add(word);

        String ans = "";
        int ansfreq = 0;
        Map<String, Integer> count = new HashMap();
        StringBuilder word = new StringBuilder();
        for (char c : paragraph.toCharArray())
            if (Character.isLetter(c))
                word.append(Character.toLowerCase(c));
            else if (word.length() > 0) {
                String finalword = word.toString();
                if (!banset.contains(finalword)) {
                    count.put(finalword, count.getOrDefault(finalword, 0) + 1);
                    if (count.get(finalword) > ansfreq) {
                        ans = finalword;
                        ansfreq = count.get(finalword);
                    }
                }
                word = new StringBuilder();
            }
        return ans;
    }
}