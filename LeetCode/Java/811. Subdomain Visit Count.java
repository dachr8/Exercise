class Solution {
    public List<String> subdomainVisits(String[] cpdomains) {
        Map<String, Integer> counts = new HashMap();
        for (String domain : cpdomains) {
            String[] cpinfo = domain.split("\\s+");
            String[] frags = cpinfo[1].split("\\.");
            String cur = "";
            for (int i = frags.length - 1; i >= 0; --i) {
                cur = frags[i] + (i < frags.length - 1 ? "." : "") + cur;
                counts.put(cur, counts.getOrDefault(cur, 0) + Integer.valueOf(cpinfo[0]));
            }
        }
        List<String> ans = new ArrayList();
        for (String dom : counts.keySet())
            ans.add("" + counts.get(dom) + " " + dom);
        return ans;
    }
}