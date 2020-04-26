#include <stdio.h>
#include <stdlib.h>
#include "avl_tree.h"
#include "avl_tree.c"

int main() {
    avlTree *tree_root = create_tree(); //O conteúdo do ponteiro tree_root recebe o retorno da função
    printf("Endereço de memória de tree_root: %ld\n", (long int) &tree_root);
    printf("Valor de tree_root: %p\n", tree_root);
    printf("Conteúdo de tree_root: %p\n", *tree_root);
    printf("Endereço de memória do conteúdo de tree_root: %ld\n", (long int) &(*tree_root));
    
    if(is_empty(tree_root)) {
        printf("A árvore está vazia!\n");
    }    

    printf("Altura da ávore: %d\n", tree_height(tree_root)); // Passando o endereço do ponteiro de tipo BinaryTree
    printf("O número de elementos da árvore é: %d\n", total_number(tree_root));

    int tamanho_array;
    int inserir_numeros[6] = {7,5,3,6,14,4};
    tamanho_array = sizeof inserir_numeros / sizeof inserir_numeros[0];
    printf("\nTamanho do vetor: %d\n", tamanho_array);
    for (int i = 0; i < tamanho_array; i++) {
        int inserido = insert_value(tree_root, inserir_numeros[i]);
        if (inserido != 1) {
            printf("Algo deu errado.\n");
        }
    }

    printf("Pré-ordem:\n");
    pre_order(tree_root);
    printf("\nEm-ordem:\n");
    in_order(tree_root);
    printf("\nPós-ordem:\n");
    post_order(tree_root);
    printf("\nAltura da ávore: %d\n", tree_height(tree_root)); // Passando o endereço do ponteiro de tipo BinaryTree
    printf("O número de elementos da árvore é: %d\n", total_number(tree_root));

    int deletar_numeros[2] = {1, 5};
    tamanho_array = sizeof deletar_numeros / sizeof deletar_numeros[0];
    for(int i = 0; i < tamanho_array; i++) {
        int deletado = delete_value(tree_root, deletar_numeros[i]);
        if (deletado == 1) {
            printf("O número %d foi deletado da árvore.\n", deletar_numeros[i]);            
        } else {
            printf("O número %d não foi deletado.\n", deletar_numeros[i]);
        }
    }
    
    printf("Pré-ordem:\n");
    pre_order(tree_root);
    printf("\nEm-ordem:\n");
    in_order(tree_root);
    printf("\nPós-ordem:\n");
    post_order(tree_root);

    printf("\nAltura da ávore: %d\n", tree_height(tree_root)); // Passando o endereço do ponteiro de tipo BinaryTree
    printf("O número de elementos da árvore é: %d\n", total_number(tree_root));

    int encontrar_numeros[2] = {2, 11};
    tamanho_array = sizeof encontrar_numeros / sizeof encontrar_numeros[0];
    printf("Tamanho do vetor encontrar_numeros: %d\n", tamanho_array);
    for(int i = 0; i < tamanho_array; i++) {
        int encontrado = find_value(tree_root, encontrar_numeros[i]);        
        if (encontrado == 1) {
            printf("O numéro %d foi encontrado na árvore.\n", encontrar_numeros[i]);
        } else {
            printf("O número %d não foi encontrado na árvore.\n", encontrar_numeros[i]);
        }       
    }

    free_tree(tree_root);
    
    return 0;
}