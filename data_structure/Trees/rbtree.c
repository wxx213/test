#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"

struct rbtree_node *null_rbtree_node = NULL;

static int rbtree_height(struct rbtree_node *pnode) {
    if(NULL == pnode) {
        return -1;
    }
    else {
        return pnode->height;
    }
}

static int rbtree_max(int x, int y)
{
    return x > y? x:y;
}

/**
   pnode_k2: the tree node(or partial root node) that not balanced
   return: the partial new root node pnode_k1
**/
static struct rbtree_node *rbtree_singlerotatewithleft(struct rbtree_node *pnode_k2)
{
    struct rbtree_node *pnode_k1;

    pnode_k1 = pnode_k2->pleft;
    pnode_k2->pleft = pnode_k1->pright;
    pnode_k1->pright = pnode_k2;

    /**
      The height of pnode_k2->pleft and pnode_k2->pright will not
      be changed with before, so we can directly use it.
    **/
    pnode_k2->height = rbtree_max(rbtree_height(pnode_k2->pleft),
                            rbtree_height(pnode_k2->pright)) + 1;
    pnode_k1->height = rbtree_max(rbtree_height(pnode_k1->pleft),
                            rbtree_height(pnode_k1->pright)) + 1;

    return pnode_k1; /* new root */
}

static struct rbtree_node *rbtree_singlerotatewithright(struct rbtree_node *pnode_k2)
{
    struct rbtree_node *pnode_k1;

    pnode_k1 = pnode_k2->pright;
    pnode_k2->pright = pnode_k1->pleft;
    pnode_k1->pleft = pnode_k2;

    pnode_k2->height = rbtree_max(rbtree_height(pnode_k2->pleft),
                            rbtree_height(pnode_k2->pright)) + 1;
    pnode_k1->height = rbtree_max(rbtree_height(pnode_k1->pleft),
                            rbtree_height(pnode_k1->pright)) + 1;

    return pnode_k1;
}

struct rbtree_node *rbtree_initialize(void)
{
    struct rbtree_node *pnode;

    if(NULL == null_rbtree_node) {
        null_rbtree_node = malloc(sizeof(struct rbtree_node));
        if(NULL == null_rbtree_node) {
            return NULL;
        }
        null_rbtree_node->pleft = null_rbtree_node->pright = null_rbtree_node;
        null_rbtree_node->color = rbtree_blank;
        null_rbtree_node->element = rbtree_infinity;
    }

    pnode = malloc(sizeof(struct rbtree_node));
    if(NULL == pnode) {
        return NULL;
    }
    pnode->element = rbtree_neginfinity;
    pnode->pleft = pnode->pright = null_rbtree_node;
    pnode->color = rbtree_blank;

    return pnode;
}

struct rbtree_node *rbtree_rotate(rbtree_etype item, struct rbtree_node *parent)
{
    if(item < parent->element) {
        return parent->pleft = item < parent->pleft->element ?
            rbtree_singlerotatewithleft(parent->pleft):
            rbtree_singlerotatewithright(parent->pleft);
    }
    else {
        return parent->pright = item < parent->pright->element ?
        rbtree_singlerotatewithleft(parent->pright):
        rbtree_singlerotatewithright(parent->pright);
    }
}

static struct rbtree_node * x, *p, *gp, *ggp;
void rbtree_handle_reorient(rbtree_etype item, struct rbtree_node *t)
{
    x->color = rbtree_red;
    x->pleft->color = rbtree_blank;
    x->pright->color = rbtree_blank;

    if(p->color == rbtree_red) {
        gp->color = rbtree_red;
        if((item < gp->element) != (item < gp->element)) {
            p = rbtree_rotate(item, gp);
        }
        x = rbtree_rotate(item, ggp);
        x->color = rbtree_blank;
    }
    t->pright->color = rbtree_blank;
}

struct rbtree_node *rbtree_insert(rbtree_etype item, struct rbtree_node *t)
{
    x = p = gp = t;
    null_rbtree_node->element = item;
    while(x->element != item) {
        ggp = gp;
        gp = p;
        p = x;
        if(item < x->element) {
            x = x->pleft;
        }
        else {
            x = x->pright;
        }
        if(x->pleft->color == rbtree_red && x->pright->color == rbtree_red) {
            rbtree_handle_reorient(item, t);
        }
    }

    if(x != null_rbtree_node) {
        return null_rbtree_node;
    }

    x = malloc(sizeof(struct rbtree_node));
    if(x == NULL) {
        printf("out of space!!!\n");
        return NULL;
    }
    x->element = item;
    x->pleft = x->pright = null_rbtree_node;

    if(item < p->element) {
        p->pleft = x;
    }
    else {
        p->pright = x;
    }

    rbtree_handle_reorient(item, t);
    return t;
}

void rbtree_print(struct rbtree_node *proot)
{
    if(proot == NULL) {
        return;
    }
    if(proot->pleft) {
        rbtree_print(proot->pleft);
    }
    if(proot->pright) {
        rbtree_print(proot->pright);
    }
    printf("%d ", proot->element);
}
