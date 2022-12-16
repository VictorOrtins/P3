public class App {
    public static void main(String[] args) throws Exception {
        Queue<Integer> queue = new Queue<Integer>();

        queue.add(1);
        queue.add(2);
        queue.add(3);
        queue.add(4);
        queue.add(5);
        queue.remove();
        queue.remove();
        queue.add(6);
        queue.add(7);
        queue.remove();
        queue.remove();
        queue.remove();
        queue.remove();
        queue.remove();
        queue.remove();

        System.out.println(queue.printList());
    }
}
