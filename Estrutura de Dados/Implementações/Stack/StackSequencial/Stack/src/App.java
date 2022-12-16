public class App {
    public static void main(String[] args) throws Exception {
        Stack stack = new Stack();

        stack.push(5);
        stack.push(10);
        stack.push(12);
        stack.push(17);
        // System.out.println(stack.getTop());

        stack.pop();
        stack.pop();
        stack.push(16);
        stack.push(18);
        // // stack.pop();

        System.out.println(stack.printStack());

        System.out.println(stack.getTop());

    }
}
