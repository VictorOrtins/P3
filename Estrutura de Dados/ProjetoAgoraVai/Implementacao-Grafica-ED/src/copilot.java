public class copilot{      
    // Driver method
    public static void main(String[] args) {
        BinarySearchTree tree = new BinarySearchTree();
    
        /* Let us create following BST
            50
            /     \
        30      70
        /  \    /  \
        20   40  60   80 */
        tree.insert(50);
        tree.insert(30);
        tree.insert(20);
        tree.insert(40);
        tree.insert(70);
        tree.insert(60);
        tree.insert(80);
    
        // Print the tree
        tree.print();
    
        // Print inorder travers
    
    }
}

