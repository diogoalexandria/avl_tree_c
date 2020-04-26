#ifndef BINARY_TREE
#define BYNARY_TREE

typedef struct NODE *avlTree;

avlTree* create_tree();
void free_tree(avlTree* root);
int is_empty(avlTree* root);
int tree_height(avlTree* root);
int total_number(avlTree* root);
void pre_order(avlTree* root);
int insert_value(avlTree* root, int value);
int delete_value(avlTree* root, int value);
void pre_order(avlTree* root);
void in_order(avlTree* root);
void post_order(avlTree* root);
int find_value(avlTree* root, int values);

#endif