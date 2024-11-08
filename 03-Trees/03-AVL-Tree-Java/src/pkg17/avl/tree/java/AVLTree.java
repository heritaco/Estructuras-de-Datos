import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

// definir la clase para el nodo del arbol AVL
class TreeNode {
    int item; // valor del nodo
    TreeNode left; // puntero al hijo izquierdo
    TreeNode right; // puntero al hijo derecho
    int height; // altura del nodo

    // constructor para crear un nuevo nodo
    TreeNode(int item) {
        this.item = item;
        this.left = null;
        this.right = null;
        this.height = 0;
    }
}

public class AVLTree {

    // funcion para crear un nuevo nodo
    TreeNode newNode(int item) {
        return new TreeNode(item);
    }

    // funcion para obtener la altura del nodo
    int getHeight(TreeNode n) {
        if (n == null)
            return 0;
        return n.height;
    }

    // funcion utilitaria para obtener el maximo de dos enteros
    int max(int a, int b) {
        return Math.max(a, b);
    }

    // funcion para rotar a la derecha el subarbol enraizado con y
    TreeNode rightRotate(TreeNode y) {
        TreeNode x = y.left; // almacenar el hijo izquierdo de y en x
        TreeNode T2 = x.right; // almacenar el hijo derecho de x en T2

        // realizar la rotacion
        x.right = y; // hacer que y sea el hijo derecho de x
        y.left = T2; // hacer que T2 sea el hijo izquierdo de y

        // actualizar las alturas
        y.height = max(getHeight(y.left), getHeight(y.right)) + 1; // actualizar la altura de y
        x.height = max(getHeight(x.left), getHeight(x.right)) + 1; // actualizar la altura de x

        return x; // retornar el nuevo nodo raiz
    }

    // funcion para rotar a la izquierda el subarbol enraizado con x
    TreeNode leftRotate(TreeNode x) {
        TreeNode y = x.right; // almacenar el hijo derecho de x en y
        TreeNode T2 = y.left; // almacenar el hijo izquierdo de y en T2

        // realizar la rotacion
        y.left = x; // hacer que x sea el hijo izquierdo de y
        x.right = T2; // hacer que T2 sea el hijo derecho de x

        // actualizar las alturas
        x.height = max(getHeight(x.left), getHeight(x.right)) + 1; // actualizar la altura de x
        y.height = max(getHeight(y.left), getHeight(y.right)) + 1; // actualizar la altura de y

        return y; // retornar el nuevo nodo raiz
    }

    // obtener el factor de balance del nodo n
    int getBalance(TreeNode n) {
        if (n == null) // si el nodo es nulo
            return 0; // retornar 0
        return getHeight(n.left) - getHeight(n.right); // retornar la diferencia de alturas entre el hijo izquierdo y el
                                                       // hijo derecho
    }

    // funcion recursiva para insertar un item en el subarbol enraizado con node y
    // retorna la nueva raiz del subarbol
    TreeNode insert(TreeNode node, int item) {
        // 1. realizar la insercion normal en el arbol binario de busqueda
        if (node == null) // si el nodo es nulo
            return newNode(item); // crear un nuevo nodo con el item

        if (item < node.item) // si el item es menor que el item del nodo
            node.left = insert(node.left, item); // insertar en el subarbol izquierdo
        else if (item > node.item) // si el item es mayor que el item del nodo
            node.right = insert(node.right, item); // insertar en el subarbol derecho
        else // si el item es igual al item del nodo
            return node; // retornar el nodo

        // 2. actualizar la altura de este nodo ancestro
        node.height = 1 + max(getHeight(node.left), getHeight(node.right)); // actualizar la altura del nodo

        // 3. obtener el factor de balance de este nodo ancestro para verificar si este
        // nodo se volvio desequilibrado
        int balance = getBalance(node); // obtener el factor de balance del nodo

        // si este nodo se vuelve desequilibrado, entonces hay 4 casos

        // caso izquierda izquierda
        if (balance > 1 && item < node.left.item) // si el balance es mayor que 1 y el item es menor que el item del
                                                  // hijo izquierdo
            return rightRotate(node); // realizar una rotacion a la derecha

        // caso derecha derecha
        if (balance < -1 && item > node.right.item) // si el balance es menor que -1 y el item es mayor que el item del
                                                    // hijo derecho
            return leftRotate(node); // realizar una rotacion a la izquierda

        // caso izquierda derecha
        if (balance > 1 && item > node.left.item) { // si el balance es mayor que 1 y el item es mayor que el item del
                                                    // hijo izquierdo
            node.left = leftRotate(node.left); // realizar una rotacion a la izquierda en el hijo izquierdo
            return rightRotate(node); // realizar una rotacion a la derecha
        }

        // caso derecha izquierda
        if (balance < -1 && item < node.right.item) { // si el balance es menor que -1 y el item es menor que el item
                                                      // del hijo derecho
            node.right = rightRotate(node.right); // realizar una rotacion a la derecha en el hijo derecho
            return leftRotate(node); // realizar una rotacion a la izquierda
        }

        return node; // retornar el nodo
    }

    // funcion para realizar el recorrido en preorden del arbol AVL
    void preOrder(TreeNode root) {
        if (root != null) {
            System.out.print(root.item + " ");
            preOrder(root.left);
            preOrder(root.right);
        }
    }

    // funcion para realizar el recorrido en orden del arbol
    void inOrder(TreeNode root) {
        if (root != null) {
            inOrder(root.left);
            System.out.print(root.item + " ");
            inOrder(root.right);
        }
    }

    public static void main(String[] args) {
        AVLTree tree = new AVLTree();
        TreeNode root = null;

        try {
            File file = new File("Test.txt");
            Scanner scanner = new Scanner(file);

            while (scanner.hasNextInt()) {
                int data = scanner.nextInt();
                root = tree.insert(root, data);
            }

            scanner.close();
        } catch (FileNotFoundException e) {
            System.out.println("Unable to open test file");
            System.exit(-1);
        }

        System.out.println("File successfully opened");

        // imprimir el recorrido en preorden del arbol AVL
        System.out.print("Preorder AVL tree: ");
        tree.preOrder(root);
        System.out.println();

        // imprimir el recorrido en orden del arbol AVL
        System.out.print("Inorder AVL tree: ");
        tree.inOrder(root);
        System.out.println();
    }
}