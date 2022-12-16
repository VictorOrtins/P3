public class App {
    public static void main(String[] args) throws Exception {
        Stack<Integer> pilha = new Stack<Integer>();

        pilha.push(1);
        pilha.push(2);
        pilha.push(3);
        pilha.pop();
        pilha.pop();
        pilha.push(4);
        pilha.push(5);
        pilha.pop();
        pilha.push(6);
        System.out.println(pilha.printList());
        pilha.pop();
        pilha.pop();

        System.out.println(pilha.printList());
    }
}
