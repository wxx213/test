#ifndef AVLTREE_H_INCLUDED
#define AVLTREE_H_INCLUDED

typedef int avl_etype;

struct avlnode {
    avl_etype element;
    struct avlnode *pleft;
    struct avlnode *pright;
    int height;
};

struct avlnode *avltree_insert(struct avlnode *pnode, avl_etype ele);

#endif // AVLTREE_H_INCLUDED
