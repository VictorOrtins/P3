public class App {
    public static void main(String[] args) {
        /*
        --- RELATIVO AOS EXERCÍCIOS DE GAME ENTRY ---


        BestScores teste = new BestScores();
        GameEntry[] scores = new GameEntry[10];

        scores[0] = new GameEntry("Victor", 10);
        scores[1] = new GameEntry("Reuben", 9);
        scores[2] = new GameEntry("Pedro", 8);
        scores[3] = new GameEntry("Valcir", 11);
        scores[4] = new GameEntry("Hilton", 6);
        scores[5] = new GameEntry("Teste", 2);

        teste.addEntry(scores[0]);
        teste.addEntry(scores[1]);
        teste.addEntry(scores[2]);
        teste.addEntry(scores[3]);
        teste.addEntry(scores[4]);


        teste.removeEntry(1);

        teste.addEntry(scores[5]);

        System.out.println(teste.toString());

        */

        /* 
        --- ARRAY ANTES E DEPOIS DE SORT ---

        int num[] = new int[10];
        Random random = new Random();
        for (int i = 0; i < num.length; i++){
            num[i] = random.nextInt(100);
        }
        int old[] = num.clone();
        System.out.println("Arrays equals before sort: " + Arrays.equals(num, old));
        Arrays.sort(num);
        System.out.println("Arrays equals after sort: " + Arrays.equals(num, old));
        System.out.println("num = " + Arrays.toString(num));
        System.out.println("old = " + Arrays.toString(old));

        String nome = "nome";
        System.out.println(Arrays.toString(nome.toCharArray()));

        num['A' - 5] = 4;
        System.out.println(num['A' - 5]);

        */

        Caesar caesar = new Caesar();
        String string = "meet at joe's";
        //phhw dw mrh'v


        System.out.println(caesar.encryptString(string));





        
    }
}
