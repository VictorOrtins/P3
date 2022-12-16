public class App {
    public static void main(String[] args) throws Exception {
        DoubleLinkedList<Integer> list = new DoubleLinkedList<Integer>();

        list.pushFront(3);
        list.pushBack(5);
        list.pushBack(8);
        list.pushBack(11);
        list.pushBack(13);
        list.pushFront(1);
        System.out.println(list.getSize());
        list.add(12, 2);
        list.add(14, 2);
        list.add(7, 3);
        System.out.println(list.getSize());
        list.add(5, 5);//10
        list.add(9, 20);//10
        list.add(8, 7);//11
        list.add(9, 7);//12
        list.add(40, 7);//13
        System.out.println(list.getSize());

        list.unpushFront();
        list.unpushFront();
        list.unpushBack();
        list.unpushBack();

        list.remove(5);
        list.remove(3);
        System.out.println(list.getSize());
        list.remove(5);
        list.remove(5);

        System.out.println(list.printList());
        // System.out.println(aux.printList());
    }
}
