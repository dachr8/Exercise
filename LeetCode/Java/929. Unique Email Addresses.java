class Solution {
    public int numUniqueEmails(String[] emails) {
        Set<String> seen = new HashSet();
        for (String email : emails) {
            String[] names = email.split("@");
            String[] local = names[0].replace(".", "").split("\\+");
            seen.add(local[0] + "@" + names[1]);
        }
        return seen.size();
    }
}