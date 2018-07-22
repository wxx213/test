#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED

typedef enum rbtree_colortype {rbtree_red, rbtree_blank} rbtree_color;
typedef int rbtree_etype;

struct rbtree_node {
    rbtree_etype element;
    struct rbtree_node *pleft;
    struct rbtree_node *pright;
    rbtree_color color;
};


#endif // RBTREE_H_INCLUDED
