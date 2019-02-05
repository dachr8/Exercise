class Solution {
    public int calPoints(String[] ops) {
        Stack<Integer> stack = new Stack();
        for (String op : ops) {
            switch (op) {
                case "+":
                    int top = stack.pop();
                    int newtop = top + stack.peek();
                    stack.push(top);
                    stack.push(newtop);
                    break;
                case "C":
                    stack.pop();
                    break;
                case "D":
                    stack.push(2 * stack.peek());
                    break;
                default:
                    stack.push(Integer.valueOf(op));
                    break;
            }
        }
        int ans = 0;
        for (int score : stack)
            ans += score;
        return ans;
    }
}