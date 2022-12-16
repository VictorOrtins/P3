public class App {
    public static void main(String[] args) throws Exception {
        SearchBinaryTree tree = new SearchBinaryTree();

        tree.insert(8);
        tree.insert(9);
        tree.insert(4);
        tree.insert(12);
        tree.insert(10);
        tree.insert(2);
        tree.insert(5);

        System.out.println(tree.showAscendingOrder());

        tree.clearTree();

        tree.insert(2);
        tree.insert(4);
        tree.insert(-1);
        tree.insert(-5);
        tree.insert(0);
        tree.insert(-3);
        tree.insert(3);
        tree.insert(9);
        tree.insert(7);

        System.out.println(tree.showAscendingOrder());
    }
}
