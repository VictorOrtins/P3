public class App {
    public static void main(String[] args) throws Exception {
        Queue<Integer> queue = new Queue<Integer>();
        queue.add(1);
        queue.add(2);
        queue.add(3);
        queue.remove();
        queue.add(4);
        queue.add(5);
        queue.remove();
        queue.add(6);
        queue.remove();
        queue.remove();
        queue.add(105);

        System.out.println(queue.first());

        System.out.println(queue.printQueue());
    }
}
