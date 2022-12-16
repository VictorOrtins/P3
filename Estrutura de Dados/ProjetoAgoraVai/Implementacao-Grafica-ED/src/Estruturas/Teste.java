package Estruturas;

import Estruturas.LSE.SimpleLinkedList;
import Estruturas.ListaSeq.ListaSeqGen;

// import Estruturas.Arvore.SearchBinaryTree;
// import Estruturas.LSE.SimpleLinkedList;
// import Estruturas.Pilha.Stack;
// import Estruturas.Queue.Queue;

public class Teste {
    public static void main(String[] args) throws EmptyStructureException {
        ListaSeqGen<String> lista = new ListaSeqGen<String>(12);

        lista.insere(1, "aaaaaaa");
        lista.insere(2, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(3, "aaaaaaa");
        lista.insere(1, "opaaaaa");
        lista.insere(12, "testeee");
        lista.insere(13, "teste");

        System.out.println(lista.print(false, null, false, -1));

        // SimpleLinkedList<Integer> lista = new SimpleLinkedList<Integer>();
        // lista.insert(100, 1);
        // lista.insert(120, 1);
        // lista.insert(10092, 1);
        // lista.insert(1203, 1);
        // lista.insert(1, 1);
        // lista.insert(109320, 1);
        // lista.insert(12, 1);
        // lista.insert(1, 1);
        // lista.insert(19, 1);
        // lista.insert(9, 1);
        // lista.insert(1100, 1);
        // lista.insert(10, 1);
        // lista.insert(10, 1);
        // lista.insert(10, 1);
        // lista.insert(10, 1);
        // lista.insert(10, 1);

        // System.out.println(lista.print(false, null, false, 0));

    }
}
