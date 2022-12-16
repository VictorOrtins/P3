public class App {
    public static void main(String[] args) throws Exception {
        BinaryTree<Character> tree = new BinaryTree<Character>();

        tree.setRoot('A');
        tree.setRoot('B'); //Não é pra ser substituído

        tree.insertLeft('B', 'A');
        tree.insertRight('C', 'A');

        tree.insertLeft('D', 'B');

        tree.insertRight('G', 'D');

        tree.insertRight('D', 'A'); //não é pra ser substituido

        tree.insertLeft('E', 'C');
        tree.insertRight('F', 'C');

        tree.insertLeft('H', 'E');
        tree.insertRight('I', 'E');

        tree.insertLeft('J', 'F');

        System.out.println(tree.showPreOrder());

        System.out.println(tree.showInOrder());

        System.out.println(tree.showPostOrder());
    }
}
