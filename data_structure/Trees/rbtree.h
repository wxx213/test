#ifndef RBTREE_H_INCLUDED
#define RBTREE_H_INCLUDED

#define rbtree_infinity     65535
#define rbtree_neginfinity -65535

typedef enum rbtree_colortype {rbtree_red, rbtree_blank} rbtree_color;
typedef int rbtree_etype;

struct rbtree_node {
    rbtree_etype element;
    struct rbtree_node *pleft;
    struct rbtree_node *pright;
    rbtree_color color;
    int height;
};

struct rbtree_node *rbtree_initialize(void);
struct rbtree_node *rbtree_insert(rbtree_etype item, struct rbtree_node *t);

#endif // RBTREE_H_INCLUDED
