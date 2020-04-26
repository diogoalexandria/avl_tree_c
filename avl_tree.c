#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

typedef struct NODE {
    int info;
    int alt;
    struct NODE *left;
    struct NODE *right;    
} Node;

avlTree* create_tree() {
    avlTree *root = (avlTree*) malloc(sizeof(avlTree));
    if (root != NULL)  
        *root = NULL;
    
    return root;
}

int tree_exist(avlTree* root) {
    if(root == NULL)
        return 0;
    
    return 1;
}

int is_empty(avlTree* root) {
    if (!tree_exist(root)) {
        printf("A árvore pode não ter sido inicializada.\n");
        return 1;
    }    
    if (*root == NULL) // Se o conteúdo do ponteiro root que é NULL
        return 1;

    return 0;
}

void free_node(Node* node) { // Espera um ponteiro para Node, inicialmente o valor do avlTree que é um ponteiro para Node
    if (node == NULL)
        return;
    
    free_node(node->left);
    free_node(node->right);
    free(node);
    node = NULL;
}

void free_tree(avlTree* root) {
    if (root == NULL)
        return;
    
    free_node(*root); // Valor do ponteiro root, que é um ponteiro para um Node, é passado como parâmetro
}

int tree_height(avlTree* root) { //Recebe o conteúdo do ponteiro, no caso o endereço de avlTree
    if (is_empty(root))
        return 0;

    int left_height = tree_height(&((*root)->left)); // Endereço do nó da esquerda do nó root
    int right_height = tree_height(&((*root)->right)); // tree_height(&((*root)->right));
    if (left_height > right_height)
        return (left_height + 1);
    else
        return(right_height + 1);
}

int total_number(avlTree* root) { // Retorna o total de elementos na árvore;
    if (is_empty(root))
        return 0;
    
    int number_left = total_number(&((*root)->left));
    int number_right = total_number(&(*root)->right);
    int total = number_left + number_right + 1;
    return total;
}

void pre_order(avlTree* root) {
    if (is_empty(root)) {        
        return;
    }    
    printf("%d\n",(*root)->info);
    pre_order(&((*root)->left));    
    pre_order(&((*root)->right));
}

void in_order(avlTree* root) {
    if (is_empty(root)){        
        return;
    }
    in_order(&((*root)->left));
    printf("%d\n",(*root)->info);
    in_order(&((*root)->right));
}

void post_order(avlTree* root) {
    if (is_empty(root)) {        
        return;
    }
    post_order(&((*root)->left));
    post_order(&((*root)->right));
    printf("%d\n",(*root)->info);
}

Node* create_node(int value) {
    Node *new = (Node*) malloc (sizeof(Node));
    if (new != NULL){
        new->info = value;
        new->right = NULL;
        new-> left = NULL;                
    } else {
        printf("Houve um erro na criação do nó.\n");        
    }
    return new;
}

int insert_value(avlTree* root, int value) {
    if(!tree_exist(root)) {
        printf("A árvore pode não ter sido inicializada.\n");
        return 0;
    }    
    if (*root == NULL) {
        *root = create_node(value);
        printf("Novo nó inserido: %d\n", value);
        return 1;        
    }
    int answer;
    if ((*root)->info > value) {                
        answer = insert_value(&((*root)->left), value);
    } else if ((*root)->info < value) {              
        answer = insert_value(&((*root)->right), value);
    } else {
        printf("Esse número já existe na árvore.");
        return 0;
    }    
    return answer;    
}

Node* remove_node(Node* this) {
    Node *auxiliar_node, *return_node;
    if(this->left == NULL) {
        return_node = this->right;
        free(this);
        return return_node;
    }
    auxiliar_node = this;
    return_node = this->left;
    while (return_node->right != NULL) {
        auxiliar_node = return_node;
        return_node = return_node->right;
    }
    if(auxiliar_node != this) {
        auxiliar_node->right = return_node->left;
        return_node->left = this->left;
    }
    return_node->right = this->right;
    printf("Nó deletado: %d\n", this->info);
    free(this);
    return return_node;    
}

int delete_value(avlTree* root, int value) {
    if (is_empty(root)) {
        return 0;
    }
    Node *previous = NULL;
    Node *this_node = *root;
    while (this_node != NULL) {
        if (value == this_node->info) {
            if (this_node == *root) // Testa se está removendo a raiz da árvore
                *root = remove_node(this_node); // O retorno da função remove_node seŕa nova raiz da ŕavore
            else {
                if (previous->right == this_node) // Testa se o nó que será exluído está a direita do nó anterior
                    previous->right = remove_node(this_node); 
                else                              // Senão está a esquerda
                    previous->left = remove_node(this_node);                    
            }
            return 1;
        }
        previous = this_node;
        if ( value > this_node->info)
            this_node = this_node->right;
        else
            this_node = this_node->left;
    }
    printf("Elemento não encontrado para exclusão.\n");
    return 0;    
}

int find_value(avlTree* root, int value) {
    if (is_empty(root)) {
        return 0;
    }
    int answer;
    if((*root)->info == value) {
        return 1;
    } else if ((*root)->info > value) {
        answer = find_value(&((*root)->left), value);
    } else {
        answer = find_value(&((*root)->right), value);
    }
    return answer;
}