import java.util.Scanner;

public class App {
    public static void main(String[] args) throws Exception {
        Stack<Character> pilhaParenteses = new Stack<Character>();

        Scanner scan = new Scanner(System.in);

        boolean correct;
        String expression;

        char tempChar;
        char tempChar2;

        /* (a+b*(2-c)-2+a)*2 */

        while(scan.hasNext()){
            correct = true;
            expression = scan.nextLine();

            for(int i = 0; i < expression.length(); i++){
                tempChar = expression.charAt(i);
                if(tempChar == '('){
                    pilhaParenteses.push(tempChar);
                }
                else if(tempChar == ')'){
                    try{
                        tempChar2 = pilhaParenteses.pop();
                    }
                    catch(EmptyListException e){
                        correct = false;
                        break;
                    }

                    // System.out.println(pilhaParenteses.printList());
                }

                if(i == expression.length() - 1){
                    if(pilhaParenteses.getSize() > 0){
                        // System.out.println("teste");
                        correct = false;
                        break;
                    }
                }
            }

            if(correct){
                System.out.println("correct");
            }
            else{
                System.out.println("incorrect");
            }

            pilhaParenteses = new Stack<Character>();
        }
    }
}

