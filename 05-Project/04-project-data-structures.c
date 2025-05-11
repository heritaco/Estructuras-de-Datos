#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the Product structure
typedef struct Product
{
    int id;
    char name[50];
    int quantity;
    float cost;
    char entryDate[11]; // Format: YYYY-MM-DD
    int priority;
    struct Product *left;
    struct Product *right;
} Product;

// Function prototype for searchProductByName
Product *searchProductByName(Product *root, char *name);

// Function to create a new product
Product *createProduct(int id, char *name, int quantity, float cost, char *entryDate, int priority)
{
    Product *newProduct = (Product *)malloc(sizeof(Product));
    newProduct->id = id;
    strcpy(newProduct->name, name);
    newProduct->quantity = quantity;
    newProduct->cost = cost;
    strcpy(newProduct->entryDate, entryDate);
    newProduct->priority = priority;
    newProduct->left = NULL;
    newProduct->right = NULL;
    return newProduct;
}

// Function to insert a product into the BST with unique name check
Product *insertProduct(Product *root, Product *newProduct)
{
    // if product with the same name already exists, do not insert
    if (searchProductByName(root, newProduct->name) != NULL)
    {
        printf("Error: A product with the name '%s' already exists.\n", newProduct->name);
        free(newProduct); // Free the memory allocated for the new product
        return root;
    }

    // If the tree is empty, return the new product as the root
    if (root == NULL)
    {
        return newProduct;
    }

    // Otherwise, recur down the tree
    if (newProduct->id < root->id)
    {
        root->left = insertProduct(root->left, newProduct);
    }

    // If the new product ID is greater than the root ID, insert in the right subtree
    else if (newProduct->id > root->id)
    {
        root->right = insertProduct(root->right, newProduct);
    }
    // If IDs are equal, do not insert
    return root;
}

// Function to insert multiple products from keyboard
void insertMultipleProducts(Product **root)
{
    int N, id, quantity, priority;
    float cost;
    char name[50], entryDate[11];

    printf("Enter the number of products to insert: ");
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
    {
        printf("Enter ID, Name, Quantity, Cost, Entry Date (YYYY-MM-DD), Priority for product %d: ", i + 1);
        scanf("%d %s %d %f %s %d", &id, name, &quantity, &cost, entryDate, &priority);
        *root = insertProduct(*root, createProduct(id, name, quantity, cost, entryDate, priority));
        printf("Product %d inserted.\n", i + 1);
    }
}

// Function to insert products from a file
void insertProductsFromFile(Product **root, const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error: Could not open file '%s'.\n", filename);
        return;
    }

    int id, quantity, priority;
    float cost;
    char name[50], entryDate[11];

    while (fscanf(file, "%d %s %d %f %s %d", &id, name, &quantity, &cost, entryDate, &priority) != EOF)
    {
        *root = insertProduct(*root, createProduct(id, name, quantity, cost, entryDate, priority));
        printf("Product '%s' inserted from file.\n", name);
    }

    fclose(file);
}

// Function to display products in-order
void inOrderTraversal(Product *root)
{
    if (root != NULL)
    {
        inOrderTraversal(root->left);
        printf("ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
               root->id, root->name, root->quantity, root->cost, root->entryDate, root->priority);
        inOrderTraversal(root->right);
    }
}

// Function to find the minimum value node
Product *findMin(Product *root)
{
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Function to delete a product by ID
Product *deleteProductById(Product *root, int id)
{
    if (root == NULL)
        return root;
    if (id < root->id)
        root->left = deleteProductById(root->left, id);
    else if (id > root->id)
        root->right = deleteProductById(root->right, id);
    else
    {
        // Node with only one child or no child
        if (root->left == NULL)
        {
            Product *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Product *temp = root->left;
            free(root);
            return temp;
        }
        // Node with two children: Get the inorder successor
        Product *temp = findMin(root->right);
        root->id = temp->id;
        strcpy(root->name, temp->name);
        root->quantity = temp->quantity;
        root->cost = temp->cost;
        strcpy(root->entryDate, temp->entryDate);
        root->priority = temp->priority;
        root->right = deleteProductById(root->right, temp->id);
    }
    return root;
}

// Function to delete a product by name
Product *deleteProductByName(Product *root, const char *name)
{
    Product *target = searchProductByName(root, (char *)name);
    if (target == NULL)
    {
        printf("Error: No product found with name '%s'.\n", name);
        return root;
    }
    return deleteProductById(root, target->id);
}

// Function to find the maximum value node
Product *findMax(Product *root)
{
    while (root->right != NULL)
        root = root->right;
    return root;
}

// Function to delete the first product (minimum ID)
Product *deleteFirstProduct(Product *root)
{
    if (root == NULL)
    {
        printf("Error: Tree is empty.\n");
        return root;
    }
    Product *minNode = findMin(root);
    printf("Deleting first product: %s\n", minNode->name);
    return deleteProductById(root, minNode->id);
}

// Function to delete the last product (maximum ID)
Product *deleteLastProduct(Product *root)
{
    if (root == NULL)
    {
        printf("Error: Tree is empty.\n");
        return root;
    }
    Product *maxNode = findMax(root);
    printf("Deleting last product: %s\n", maxNode->name);
    return deleteProductById(root, maxNode->id);
}

// Function to search for a product by name
Product *searchProductByName(Product *root, char *name)
{
    // Base Cases: root is null or name is found
    // If the root is null, return null
    if (root == NULL)
        return NULL;
    // If the name is found, return the root
    if (strcmp(name, root->name) == 0)
        return root;
    // Recur down the tree
    Product *found = searchProductByName(root->left, name);
    // If the name is found in the left subtree, return the node
    if (found == NULL)
        found = searchProductByName(root->right, name);
    return found;
}

// Function to search for products by price
void searchProductByPrice(Product *root, float price)
{
    if (root != NULL)
    {
        searchProductByPrice(root->left, price);
        if (root->cost == price)
        {
            printf("Found: ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
                   root->id, root->name, root->quantity, root->cost, root->entryDate, root->priority);
        }
        searchProductByPrice(root->right, price);
    }
}

// Function to search for products by entry date
void searchProductByEntryDate(Product *root, const char *date)
{
    if (root != NULL)
    {
        searchProductByEntryDate(root->left, date);
        if (strcmp(root->entryDate, date) == 0)
        {
            printf("Found: ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
                   root->id, root->name, root->quantity, root->cost, root->entryDate, root->priority);
        }
        searchProductByEntryDate(root->right, date);
    }
}

// Function to update a product's details
Product *updateProduct(Product *root, int id, char *name, float cost, int quantity, char *entryDate, int priority)
{
    root = deleteProductById(root, id);

    root = insertProduct(root, createProduct(id, name, quantity, cost, entryDate, priority));
    printf("Product inserted.\n");

    return root;
}

// Comparator for sorting by name
int compareName(const void *a, const void *b)
{
    Product *p1 = *(Product **)a;
    Product *p2 = *(Product **)b;
    return strcmp(p1->name, p2->name);
}

// Comparator for sorting by price
int comparePrice(const void *a, const void *b)
{
    Product *p1 = *(Product **)a;
    Product *p2 = *(Product **)b;
    if (p1->cost < p2->cost)
        return -1;
    if (p1->cost > p2->cost)
        return 1;
    return 0;
}

// Function to collect all products into an array
int collectProducts(Product *root, Product **arr, int index)
{
    if (root == NULL)
        return index;
    index = collectProducts(root->left, arr, index);
    arr[index++] = root;
    index = collectProducts(root->right, arr, index);
    return index;
}

int countProducts(Product *node)
{
    if (node == NULL)
        return 0;
    return 1 + countProducts(node->left) + countProducts(node->right);
}

// Function to display products sorted by price
void displaySortedByPrice(Product *root)
{
    // First, collect all products into an array
    int count = countProducts(root);

    if (count == 0)
    {
        printf("No products to display.\nTotal products: %d\n", count);
        printf("Total products: %d\n", count);
    }

    Product **arr = (Product **)malloc(count * sizeof(Product *));
    collectProducts(root, arr, 0);

    // Sort the array by price
    qsort(arr, count, sizeof(Product *), comparePrice);

    // Display the sorted products
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
               arr[i]->id, arr[i]->name, arr[i]->quantity, arr[i]->cost, arr[i]->entryDate, arr[i]->priority);
    }

    free(arr);
}

// Function to display products sorted by name
void displaySortedByName(Product *root)
{
    // First, collect all products into an array
    int count = countProducts(root);

    if (count == 0)
    {
        printf("No products to display.\nTotal products: %d\n", count);
        return;
    }

    Product **arr = (Product **)malloc(count * sizeof(Product *));
    collectProducts(root, arr, 0);

    // Sort the array by name
    qsort(arr, count, sizeof(Product *), compareName);

    // Display the sorted products
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
               arr[i]->id, arr[i]->name, arr[i]->quantity, arr[i]->cost, arr[i]->entryDate, arr[i]->priority);
    }

    free(arr);
}

// Comparator for priority
int comparePriority(const void *a, const void *b)
{
    Product *p1 = *(Product **)a;
    Product *p2 = *(Product **)b;
    return p1->priority - p2->priority;
}

// Function to display products sorted by priority
void displaySortedByPriority(Product *root)
{
    // Similar to inOrderTraversal but sorted by priority
    // Collect all products into an array

    Product *temp = root;

    int count = countProducts(root);

    if (count == 0)
    {
        printf("No products to display.\nTotal products: %d\n", count);
        return;
    }

    Product **arr = (Product **)malloc(count * sizeof(Product *));
    collectProducts(root, arr, 0);

    // Sort the array by priority
    qsort(arr, count, sizeof(Product *), comparePriority);

    // Display the sorted products
    for (int i = 0; i < count; i++)
    {
        printf("ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
               arr[i]->id, arr[i]->name, arr[i]->quantity, arr[i]->cost, arr[i]->entryDate, arr[i]->priority);
    }

    free(arr);
}

// Function to display products sorted by priority (in-order traversal)
void displayByPriority(Product *root)
{
    if (root != NULL)
    {
        displayByPriority(root->left);
        printf("ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
               root->id, root->name, root->quantity, root->cost, root->entryDate, root->priority);
        displayByPriority(root->right);
    }
}

int main()
{
    Product *root = NULL;
    int mainChoice;
    int choice, id, quantity, priority;
    float cost;
    char name[50], entryDate[11], filename[100];
    float searchPrice;
    char searchDate[11];

    while (1)
    {
        printf("\n===================================\n");
        printf("      Inventory Management System  \n");
        printf("===================================\n");
        printf("1. Insert Operations\n");
        printf("2. Delete Operations\n");
        printf("3. Search Operations\n");
        printf("4. Update Product\n");
        printf("5. Display Operations\n");
        printf("6. Exit\n");
        printf("===================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &mainChoice) != 1)
        {
            printf("Invalid input. Please enter a number between 1 and 6.\n");
            while (getchar() != '\n')
                ; // Clear input buffer
            continue;
        }

        switch (mainChoice)
        {
        case 1:
        {
            int insertChoice;
            printf("\n--- Insert Operations ---\n");
            printf("1. Insert Single Product\n");
            printf("2. Insert Multiple Products\n");
            printf("3. Insert Products from File\n");
            printf("4. Back to Main Menu\n");
            printf("Enter your choice: ");
            if (scanf("%d", &insertChoice) != 1)
            {
                printf("Invalid input. Please enter a number between 1 and 4.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            switch (insertChoice)
            {
            case 1:
                printf("\n--- Insert Single Product ---\n");
                printf("Enter ID, Name, Quantity, Cost, Entry Date (YYYY-MM-DD), Priority: ");
                scanf("%d %s %d %f %s %d", &id, name, &quantity, &cost, entryDate, &priority);
                root = insertProduct(root, createProduct(id, name, quantity, cost, entryDate, priority));
                printf("Product inserted.\n");
                break;
            case 2:
                printf("\n--- Insert Multiple Products ---\n");
                insertMultipleProducts(&root);
                break;
            case 3:
                printf("\n--- Insert Products from File ---\n");
                scanf("%s", filename);
                insertProductsFromFile(&root, filename);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please select a number between 1 and 4.\n");
            }
            break;
        }
        case 2:
        {
            int deleteChoice;
            printf("\n--- Delete Operations ---\n");
            printf("1. Delete Product by ID\n");
            printf("2. Delete Product by Name\n");
            printf("3. Delete First Product\n");
            printf("4. Delete Last Product\n");
            printf("5. Back to Main Menu\n");
            printf("Enter your choice: ");
            if (scanf("%d", &deleteChoice) != 1)
            {
                printf("Invalid input. Please enter a number between 1 and 5.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            switch (deleteChoice)
            {
            case 1:
                printf("\n--- Delete Product by ID ---\n");
                printf("Enter Product ID to delete: ");
                scanf("%d", &id);
                root = deleteProductById(root, id);
                printf("Product deleted.\n");
                break;
            case 2:
                printf("\n--- Delete Product by Name ---\n");
                printf("Enter Product Name to delete: ");
                scanf("%s", name);
                root = deleteProductByName(root, name);
                break;
            case 3:
                printf("\n--- Delete First Product ---\n");
                root = deleteFirstProduct(root);
                printf("First product deleted.\n");
                break;
            case 4:
                printf("\n--- Delete Last Product ---\n");
                root = deleteLastProduct(root);
                printf("Last product deleted.\n");
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please select a number between 1 and 5.\n");
            }
            break;
        }
        case 3:
        {
            int searchChoice;
            printf("\n--- Search Operations ---\n");
            printf("1. Search Product by Name\n");
            printf("2. Search Products by Price\n");
            printf("3. Search Products by Entry Date\n");
            printf("4. Back to Main Menu\n");
            printf("Enter your choice: ");
            if (scanf("%d", &searchChoice) != 1)
            {
                printf("Invalid input. Please enter a number between 1 and 4.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            switch (searchChoice)
            {
            case 1:
                printf("\n--- Search Product by Name ---\n");
                printf("Enter Product Name to search: ");
                scanf("%s", name);
                {
                    Product *found = searchProductByName(root, name);
                    if (found != NULL)
                        printf("Found: ID: %d, Name: %s, Quantity: %d, Cost: %.2f, Entry Date: %s, Priority: %d\n",
                               found->id, found->name, found->quantity, found->cost, found->entryDate, found->priority);
                    else
                        printf("Product not found.\n");
                }
                break;
            case 2:
                printf("\n--- Search Products by Price ---\n");
                printf("Enter Price to search: ");
                scanf("%f", &searchPrice);
                printf("Products with cost %.2f:\n", searchPrice);
                searchProductByPrice(root, searchPrice);
                break;
            case 3:
                printf("\n--- Search Products by Entry Date ---\n");
                printf("Enter Entry Date to search (YYYY-MM-DD): ");
                scanf("%s", searchDate);
                printf("Products with entry date %s:\n", searchDate);
                searchProductByEntryDate(root, searchDate);
                break;
            case 4:
                break;
            default:
                printf("Invalid choice. Please select a number between 1 and 4.\n");
            }
            break;
        }
        case 4:
            printf("\n--- Update Product ---\n");
            printf("Enter Product ID to update: ");
            scanf("%d", &id);
            printf("Enter new Name, Cost, Quantity, Entry Date (YYYY-MM-DD), Priority: ");
            scanf("%s %f %d %s %d", name, &cost, &quantity, entryDate, &priority);
            printf("Updating product with ID %d...\n", id);
            root = updateProduct(root, id, name, cost, quantity, entryDate, priority);
            printf("Product updated.\n");
            break;
        case 5:
        {
            int displayChoice;
            printf("\n--- Display Operations ---\n");
            printf("1. Display All Products (In-Order)\n");
            printf("2. Display Products Sorted by Priority\n");
            printf("3. Display Products Sorted by Price\n");
            printf("4. Display Products Sorted by Name\n");
            printf("5. Back to Main Menu\n");
            printf("Enter your choice: ");
            if (scanf("%d", &displayChoice) != 1)
            {
                printf("Invalid input. Please enter a number between 1 and 4.\n");
                while (getchar() != '\n')
                    ;
                break;
            }
            switch (displayChoice)
            {
            case 1:
                printf("\n--- Display All Products (In-Order) ---\n");
                printf("Displaying all products (In-Order):\n");
                inOrderTraversal(root);
                break;
            case 2:
                printf("\n--- Display Products Sorted by Priority ---\n");
                printf("Displaying all products sorted by priority:\n");
                displaySortedByPriority(root);
                break;
            case 3:
                printf("\n--- Display Products Sorted by Price ---\n");
                printf("Displaying all products sorted by price:\n");
                displaySortedByPrice(root);
                break;
            case 4:
                printf("\n--- Display Products Sorted by Name ---\n");
                printf("Displaying all products sorted by name:\n");
                displaySortedByName(root);
                break;
            case 5:
                break;
            default:
                printf("Invalid choice. Please select a number between 1 and 4.\n");
            }
            break;
        }
        case 6:
            printf("Exiting the program. Goodbye!\n");
            exit(0);
        default:
            printf("Invalid choice. Please select a number between 1 and 6.\n");
        }
    }

    return 0;
}