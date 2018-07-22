#include <stdio.h>
#include <stdlib.h>

#include "rbtree.h"

struct rbtree_node *null_rbtree_node = NULL;

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
        null_rbtree_node->element = -1;
    }

    pnode = malloc(sizeof(struct rbtree_node));
    if(NULL == pnode) {
        return NULL;
    }
    pnode->element = 1;
    pnode->pleft = pnode->pright = null_rbtree_node;
    pnode->color = rbtree_blank;

    return pnode;
}
