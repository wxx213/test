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
struct avlnode *avltree_find_min(struct avlnode * proot)
{
    if(proot->pleft == NULL) {
        return proot;
    }
    else {
        return avltree_find_min(proot->pleft);
    }
}
/**
   pnode_k2: the tree node(or partial root node) that not balanced
   return: the partial new root node pnode_k1
**/
static struct avlnode *avltree_singlerotatewithleft(struct avlnode *pnode_k2)
{
    struct avlnode *pnode_k1;

    pnode_k1 = pnode_k2->pleft;
    pnode_k2->pleft = pnode_k1->pright;
    pnode_k1->pright = pnode_k2;

    /**
      The height of pnode_k2->pleft and pnode_k2->pright will not
      be changed with before, so we can directly use it.
    **/
    pnode_k2->height = avltree_max(avltree_height(pnode_k2->pleft),
                            avltree_height(pnode_k2->pright)) + 1;
    pnode_k1->height = avltree_max(avltree_height(pnode_k1->pleft),
                            avltree_height(pnode_k1->pright)) + 1;

    return pnode_k1; /* new root */
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
/**
  pnode_k3: the node that not balanced
**/
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
/**
  pnode: the root node of insert tree
  return:
    pnode->pleft when insert ele in left
    pnode->pright when insert ele in right
**/
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
    /* update height */
    pnode->height = avltree_max(avltree_height(pnode->pleft),
                                avltree_height(pnode->pright)) + 1;
    return pnode;
}

/**
  return: new root node of the tree
**/
struct avlnode *avltree_delete(struct avlnode *proot, avl_etype ele)
{
    struct avlnode *pnode;

    if(proot == NULL) {
        return NULL;
    }
    else if(ele < proot->element) {
        proot->pleft = avltree_delete(proot->pleft, ele);
        if(2 == (avltree_height(proot->pright) - avltree_height(proot->pleft))) {
            proot = avltree_singlerotatewithright(proot);
        }
    }
    else if(ele > proot->element) {
        proot->pright = avltree_delete(proot->pright, ele);
        if(2 == (avltree_height(proot->pleft) - avltree_height(proot->pright))) {
            proot = avltree_singlerotatewithleft(proot);
        }
    }
    else {
        if(proot->pleft && proot->pright) { //two child
            pnode = avltree_find_min(proot->pright);
            proot->element = pnode->element; //copy
            proot->pright = avltree_delete(proot->pright, pnode->element);
            proot->pright = avltree_delete(proot->pright, ele);
            if(2 == (avltree_height(proot->pleft) - avltree_height(proot->pright))) {
                proot = avltree_singlerotatewithleft(proot);
            }
        }
        else { //one or zero child
            pnode = proot;
            if(proot->pleft) {
                proot = proot->pleft;
            }
            else if(proot->pright) {
                proot = proot->pright;
            }
            else {
                proot = NULL;
            }
            free(pnode);
        }
    }
    /* update height */
    if(proot) {
        proot->height = avltree_max(avltree_height(proot->pleft),
                                avltree_height(proot->pright)) + 1;
    }
    return proot;
};

void avltree_print(struct avlnode *proot)
{
    if(proot == NULL) {
        return;
    }
    if(proot->pleft) {
        avltree_print(proot->pleft);
    }
    if(proot->pright) {
        avltree_print(proot->pright);
    }
    printf("%d ", proot->element);
}
