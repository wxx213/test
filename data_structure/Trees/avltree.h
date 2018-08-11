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
struct avlnode *avltree_delete(struct avlnode *pnode, avl_etype ele);
void avltree_print(struct avlnode *proot);
#endif // AVLTREE_H_INCLUDED
