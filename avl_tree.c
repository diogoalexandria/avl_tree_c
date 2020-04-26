#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"

typedef struct NODE {
    int value;
    int height;
    struct NODE *left_child;
    struct NODE *right_child;    
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
    
    free_node(node->left_child);
    free_node(node->right_child);
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

    int left_height = tree_height(&((*root)->left_child)); // Endereço do nó da esquerda do nó root
    int right_height = tree_height(&((*root)->right_child)); // tree_height(&((*root)->right));
    if (left_height > right_height)
        return (left_height + 1);
    else
        return(right_height + 1);
}

int node_height(Node* node) {
    if(node == NULL)
        return  -1;
    else
        return node->height;
}

int balancing_factor(Node* node) {
    return labs(node_height(node->left_child) - node_height(node->right_child));
}

int biggest_height(int left, int right) {
    if (left > right)
        return left;
    else
        return right; 
}

void ll_rotation(avlTree* root) {    
    Node* unbalanced_node = *root;
    Node* auxiliar_node;

    auxiliar_node = unbalanced_node->left_child; // Pega o filho à esquerda do ancestral mais próximo desbalanceado (Fator de balanceamento = +2) ao nó que foi inserido a árvore.
    unbalanced_node->left_child = auxiliar_node->right_child; // O filho à esquerda do nó desbalanceado recebe o valor do filho à direita do nó desbalanceado.
    auxiliar_node->right_child = unbalanced_node; //O nó que era filho a esquerda do nó desbalanceado, seu filho a direita recebe o nó desbalanceado.

    int new_height;
    new_height = biggest_height(node_height(unbalanced_node->left_child),node_height(unbalanced_node->right_child)) +1;
    unbalanced_node->height = new_height; //Atualiza a altura que está o nó inicialmente desbalanceado.
    new_height = biggest_height(node_height(auxiliar_node->left_child), unbalanced_node->height) + 1;
    auxiliar_node->height = new_height; //Atualiza a altura do nó que assume a posição do nó desbalanceado.

    unbalanced_node = auxiliar_node; // O filho que estava a esquerda do nó desbalanceado assume a posição desse nó
}

void rr_rotation(avlTree* root){
    Node* unbalanced_node = *root;
    Node* auxiliar_node;

    auxiliar_node = unbalanced_node->right_child;
    unbalanced_node->right_child = auxiliar_node->left_child;
    auxiliar_node->left_child = unbalanced_node;

    int new_height;
    new_height = biggest_height(node_height(unbalanced_node->left_child),node_height(unbalanced_node->right_child)) + 1;
    unbalanced_node->height = new_height;
    new_height = biggest_height(node_height(unbalanced_node->right_child),unbalanced_node->height) + 1;
    auxiliar_node->height = new_height;

    unbalanced_node = auxiliar_node;
}

void lr_rotation(avlTree* root) {
    rr_rotation(&(*root)->left_child);
    ll_rotation(root);
}

void rl_rotation(avlTree* root) {
    ll_rotation(&(*root)->right_child);
    rr_rotation(root);
}

int total_number(avlTree* root) { // Retorna o total de elementos na árvore;
    if (is_empty(root))
        return 0;
    
    int number_left = total_number(&((*root)->left_child));
    int number_right = total_number(&(*root)->right_child);
    int total = number_left + number_right + 1;
    return total;
}

void pre_order(avlTree* root) {
    if (is_empty(root)) {        
        return;
    }    
    printf("%d\n",(*root)->value);
    pre_order(&((*root)->left_child));    
    pre_order(&((*root)->right_child));
}

void in_order(avlTree* root) {
    if (is_empty(root)){        
        return;
    }
    in_order(&((*root)->left_child));
    printf("%d\n",(*root)->value);
    in_order(&((*root)->right_child));
}

void post_order(avlTree* root) {
    if (is_empty(root)) {        
        return;
    }
    post_order(&((*root)->left_child));
    post_order(&((*root)->right_child));
    printf("%d\n",(*root)->value);
}

Node* create_node(int value) {
    Node *new = (Node*) malloc (sizeof(Node));
    if (new != NULL){
        new->value = value;
        new->height = 0;
        new->right_child = NULL;
        new-> left_child = NULL;                
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
        Node* current = *root;
        if(current == NULL) {
            current = create_node(value);
            return 1;
        }
        int answer;
        if (value < current->value) {
            if ((answer = insert_value(&(current->left_child),value)) == 1) {
                if (balancing_factor(current) >= 2) {
                    if (value < current->left_child->value) {
                        ll_rotation(current);
                    } else {
                        lr_rotation(current);
                    }                    
                }
            }
        } else if (value > current->value) {
            if ((answer = insert_value(&(current->left_child), value)) == 1) {
                if (balancing_factor(current) >= 2) {
                    if(value > current->right_child->value) {
                        rr_rotation(current);
                    } else {
                        rl_rotation(current);
                    }                    
                }
            }
        } else {
            printf("Esse número já existe na árvore.");
            return 0;
        }
        int new_height = biggest_height(node_height(current->left_child),node_height(current->right_child)) + 1;
        current->height = new_height;
        return 1;
}

Node* remove_node(Node* this) {
    Node *auxiliar_node, *return_node;
    if(this->left_child == NULL) {
        return_node = this->right_child;
        free(this);
        return return_node;
    }
    auxiliar_node = this;
    return_node = this->left_child;
    while (return_node->right_child != NULL) {
        auxiliar_node = return_node;
        return_node = return_node->right_child;
    }
    if(auxiliar_node != this) {
        auxiliar_node->right_child = return_node->left_child;
        return_node->left_child = this->left_child;
    }
    return_node->right_child = this->right_child;
    printf("Nó deletado: %d\n", this->value);
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
        if (value == this_node->value) {
            if (this_node == *root) // Testa se está removendo a raiz da árvore
                *root = remove_node(this_node); // O retorno da função remove_node seŕa nova raiz da ŕavore
            else {
                if (previous->right_child == this_node) // Testa se o nó que será exluído está a direita do nó anterior
                    previous->right_child = remove_node(this_node); 
                else                              // Senão está a esquerda
                    previous->left_child = remove_node(this_node);                    
            }
            return 1;
        }
        previous = this_node;
        if ( value > this_node->value)
            this_node = this_node->right_child;
        else
            this_node = this_node->left_child;
    }
    printf("Elemento não encontrado para exclusão.\n");
    return 0;    
}

int find_value(avlTree* root, int value) {
    if (is_empty(root)) {
        return 0;
    }
    int answer;
    if((*root)->value == value) {
        return 1;
    } else if ((*root)->value > value) {
        answer = find_value(&((*root)->left_child), value);
    } else {
        answer = find_value(&((*root)->right_child), value);
    }
    return answer;
}
