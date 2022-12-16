public class BinarySearchTree {
    // Root of the Binary Tree
    Node root;
    
    // Constructor
    BinarySearchTree() {
        root = null;
    }
    
    // This method mainly calls insertRec()
    void insert(int key) {
        root = insertRec(root, key);
    }
    
    /* A recursive function to insert a new key in the
        binary search tree */
    Node insertRec(Node root, int key) {
        /* If the tree is empty, return a new node */
        if (root == null) {
        root = new Node(key);
        return root;
        }
    
        /* Otherwise, recur down the tree */
        if (key < root.key) {
        root.left = insertRec(root.left, key);
        } else if (key > root.key) {
        root.right = insertRec(root.right, key);
        }
    
        /* return the (unchanged) node pointer */
        return root;
    }
    
    // This method mainly calls InorderRec()
    void inorder() {
        inorderRec(root);
    }
    
    // A utility function to do inorder traversal of the tree
    void inorderRec(Node root) {
        if (root != null) {
        inorderRec(root.left);
        System.out.println(root.key);
        inorderRec(root.right);
        }
    }
    
   // This method mainly calls printTree()
   void print() {
    printTree(root, 0);
  }

  // A utility function to print the tree in a human-readable format
  void printTree(Node root, int space) {
    // Base case
    if (root == null) {
      return;
    }

    // Increase the distance between levels
    space += 10;

    // Process right child first
    printTree(root.right, space);

    // Print current node after space
    // count
    System.out.println();
    for (int i = 10; i < space; i++) {
      System.out.print(" ");
    }
    System.out.println(root.key);

    // Process left child
    printTree(root.left, space);
  }

    class Node {
        int key;
        Node left, right;
      
        public Node(int item) {
          key = item;
          left = right = null;
        }
      }
}
