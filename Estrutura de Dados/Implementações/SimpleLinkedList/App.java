package SimpleLinkedList;

public class App {
    public static void main(String[] args) {
        SimpleLinkedList list = new SimpleLinkedList();

        list.insert(4, 1);
        list.insert(9, 1);
        list.insert(10, 3);
        list.insert(5, 1);
        list.insert(11, 5);
        list.insert(3, 3);
        list.insert(5, 5);

        list.removeBeggining();
        list.removeEnd();
        
        try{    
            list.remove(2);
        }catch(EmptyListException e){
            System.out.println("List is empty");
        }

        list.insertEnd(5);
        list.insertEnd(11);
        System.out.println(list.insert(100, 10));

        // try{
        //     System.out.println(list.valueInPosition(6));
        // }
        // catch(Exception e){
        //     System.out.println("Not valid");
        // }

        try{
            SimpleLinkedList list2 = list.positionsOfValue(5);
            System.out.println(list2.printList());

        }
        catch(EmptyListException e){
            System.out.println(e);
            System.out.println("Not valid");
        }


        System.out.println(list.printList());
    }
}
