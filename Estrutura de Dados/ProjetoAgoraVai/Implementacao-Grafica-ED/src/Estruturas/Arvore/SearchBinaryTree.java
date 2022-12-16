package Estruturas.Arvore;

public class SearchBinaryTree {

    private Node root;

    public boolean isEmpty(){
        if(root == null){
            return true;
        }

        return false;
    }

    public Node searchNode(int value){
        if(isEmpty()){
            return null;
        }

        return searchNode(value, root);
    }

    public Node searchNode(int value, Node node){
        if(node == null){
            return null;
        }

        if(node.getValue() == value){
            return node;
        }

        Node aux = null;
        if(value > node.getValue()){
            aux = searchNode(value, node.getRight());
        }
        else{
            aux = searchNode(value, node.getLeft());
        }

        return aux;
    }

    public boolean setRoot(int value){
        if(!(isEmpty())){
            return false;
        }

        Node newRoot = new Node();
        newRoot.setValue(value);

        root = newRoot;

        return true;
    }

    public boolean insert(int value){
        if(isEmpty()){
            return setRoot(value);
        }


        if(searchNode(value) != null){
            return false;
        }

        Node aux = root;
        Node father = new Node();
        boolean left = false;
        while(aux != null){
            father = aux;
            if(value > aux.getValue()){
                aux = aux.getRight();
                left = false;
            }
            else{
                aux = aux.getLeft();
                left = true;
            }
        }

        aux = new Node();
        aux.setValue(value);

        if(left){
            father.setLeft(aux);
        }
        else{
            father.setRight(aux);
        }
        return true;
    }

    public String showAscendingOrder(){
        if(isEmpty()){
            return "Tree is empty";
        }

        String[] ret = showAscendingOrder(root, "").split("");
        String auxiliar = "";
        for(int i = 0; i < ret.length; i++){
            auxiliar += ret[i];
        }

        return auxiliar.strip();
    }

    public String showAscendingOrder(Node node, String ret){
        if(node == null){
            return "";
        }

        return showAscendingOrder(node.getLeft(), ret) + " " + node.getValue() + " "+ showAscendingOrder(node.getRight(), ret);
    }

    public void clearTree(){
        root = null;
    }

    public Node getRoot(){
        return root;
    }

    
}

