public class App {
    public static void main(String[] args) throws Exception {
        Stack<String> stack = new Stack<String>();
        // System.out.println(stack.printStack());

        stack.push("Victor");
        stack.push("Reuben");
        stack.pop();
        stack.push("PedroLucena");
        stack.push("PedroAugusto");
        stack.push("PedroQueiroga");
        stack.pop();
        stack.pop();
        stack.push("Yan");
        System.out.println(stack.printStack());

        // Stack<Integer> stack = new Stack<Integer>();
        // stack.push(10);
        // stack.push(12);
        // System.out.println(stack.printStack());
    }
}
