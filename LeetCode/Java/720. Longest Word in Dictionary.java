class Solution {
    public String longestWord(String[] words) {
        Set<String> wordset = new HashSet();
        for (String word : words)
            wordset.add(word);
        Arrays.sort(words, (a, b) -> a.length() == b.length() ? a.compareTo(b) : b.length() - a.length());
        for (String word : words) {
            boolean good = true;
            for (int i = 1; good && i < word.length(); i++)
                if (!wordset.contains(word.substring(0, i)))
                    good = false;
            if (good)
                return word;
        }
        return "";
    }
}