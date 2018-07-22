#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"

static int avltree_height(struct avlnode *pnode) {
    if(NULL == pnode) {
        return -1;
    }
    else {
        return pnode->height;
    }
}
static int avltree_max(int x, int y)
{
    return x > y? x:y;
}
static struct avlnode *avltree_singlerotatewithleft(struct avlnode *pnode_k2)
{
    struct avlnode *pnode_k1;

    pnode_k1 = pnode_k2->pleft;
    pnode_k2->pleft = pnode_k1->pright;
    pnode_k1->pright = pnode_k2;

    pnode_k2->height = avltree_max(avltree_height(pnode_k2->pleft),
                            avltree_height(pnode_k2->pright)) + 1;
    pnode_k1->height = avltree_max(avltree_height(pnode_k1->pleft),
                            avltree_height(pnode_k1->pright)) + 1;

    return pnode_k1;
}
static struct avlnode *avltree_singlerotatewithright(struct avlnode *pnode_k2)
{
    struct avlnode *pnode_k1;

    pnode_k1 = pnode_k2->pright;
    pnode_k2->pright = pnode_k1->pleft;
    pnode_k1->pleft = pnode_k2;

    pnode_k2->height = avltree_max(avltree_height(pnode_k2->pleft),
                            avltree_height(pnode_k2->pright)) + 1;
    pnode_k1->height = avltree_max(avltree_height(pnode_k1->pleft),
                            avltree_height(pnode_k1->pright)) + 1;

    return pnode_k1;
}
static struct avlnode *avltree_doublerotatewithleft(struct avlnode *pnode_k3)
{
    pnode_k3->pleft = avltree_singlerotatewithright(pnode_k3->pleft);

    return avltree_singlerotatewithleft(pnode_k3);
}
static struct avlnode *avltree_doublerotatewithright(struct avlnode *pnode_k3)
{
    pnode_k3->pright = avltree_singlerotatewithleft(pnode_k3->pright);

    return avltree_singlerotatewithright(pnode_k3);
}
struct avlnode *avltree_insert(struct avlnode *pnode, avl_etype ele)
{
    if(NULL == pnode) {
        pnode = malloc(sizeof(struct avlnode));
        if(NULL == pnode) {
            return NULL;
        }
        else {
            pnode->element = ele;
            pnode->height = 0;
            pnode->pleft = pnode->pright = NULL;
        }
    }
    else {
        if(ele < pnode->element) {
            pnode->pleft = avltree_insert(pnode->pleft, ele);
            if(NULL == pnode->pleft) {
                return NULL;
            }
            if(2 == (avltree_height(pnode->pleft) - avltree_height(pnode->pright))) {
                if(ele < pnode->pleft->element) {
                    pnode = avltree_singlerotatewithleft(pnode);
                }
                else {
                    pnode = avltree_doublerotatewithleft(pnode);
                }
            }
        }
        else if(ele > pnode->element) {
            pnode->pright = avltree_insert(pnode->pright, ele);
            if(NULL == pnode->pright) {
                return NULL;
            }
            if(2 == (avltree_height(pnode->pright) - avltree_height(pnode->pleft))) {
                if(ele > pnode->pright->element) {
                    pnode = avltree_singlerotatewithright(pnode);
                }
                else {
                    pnode = avltree_doublerotatewithright(pnode);
                }
            }
        }
    }
    pnode->height = avltree_max(avltree_height(pnode->pleft),
                                avltree_height(pnode->pright)) + 1;
    return pnode;
}
