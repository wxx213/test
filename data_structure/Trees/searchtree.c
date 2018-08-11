#include <stdio.h>
#include <stdlib.h>

#include "searchtree.h"

struct treenode *searchtree_init(etype ele)
{
    struct treenode * pnode;
    pnode = malloc(sizeof(struct treenode));
    if(pnode) {
        pnode->element = ele;
        pnode->pleft = NULL;
        pnode->pright = NULL;
    }
    else {
        return NULL;
    }
    return pnode;
}
int searchtree_insert(struct treenode * proot, etype ele)
{
    if(ele < proot->element) {
        if(proot->pleft == NULL) {
            proot->pleft = searchtree_init(ele);
            if(proot->pleft) {
                return 0;
            }
            else {
                return -1;
            }
        }
        else {
            return searchtree_insert(proot->pleft, ele);
        }
    }
    else if(ele > proot->element ) {
        if(proot->pright == NULL) {
            proot->pright = searchtree_init(ele);
            if(proot->pright) {
                return 0;
            }
            else {
                return -1;
            }
        }
        else {
            return searchtree_insert(proot->pright, ele);
        }
    }
    else {
        return -1;
    }
}

struct treenode *searchtree_find(struct treenode * proot, etype ele)
{
    if(NULL == proot) {
        return NULL;
    }
    else {
        if(ele == proot->element) {
            return proot;
        }
        else if(ele < proot->element) {
            return searchtree_find(proot->pleft, ele);
        }
        else {
            return searchtree_find(proot->pright, ele);
        }
    }
}
struct treenode *searchtree_find_parent(struct treenode * proot, etype ele)
{
    if(proot == NULL) {
        return NULL;
    }

    if(proot->element == ele) {
        return NULL;
    }
    else if((proot->pleft && proot->pleft->element == ele) ||
            (proot->pright && proot->pright->element == ele)) {
        return proot;
    }
    else if(ele < proot->element) {
        return searchtree_find_parent(proot->pleft, ele);
    }
    else {
        return searchtree_find_parent(proot->pright, ele);
    }
}
struct treenode *searchtree_find_min(struct treenode * proot)
{
    if(proot->pleft == NULL) {
        return proot;
    }
    else {
        return searchtree_find_min(proot->pleft);
    }
}
/**
  proot: the root node of delete tree
  return:
    proot->pleft when delete in left
    proot->pright when delete in right
**/
struct treenode *searchtree_delete(struct treenode * proot, etype ele)
{
    struct treenode *pnode;

    if(proot == NULL) {
        return NULL;
    }
    else if(ele < proot->element) {
        proot->pleft = searchtree_delete(proot->pleft, ele);
    }
    else if(ele > proot->element) {
        proot->pright = searchtree_delete(proot->pright, ele);
    }
    else {
        if(proot->pleft && proot->pright) { //two child
            pnode = searchtree_find_min(proot->pright);
            proot->element = pnode->element; //copy
            proot->pright = searchtree_delete(proot->pright, pnode->element);
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
    return proot;
}
void searchtree_print(struct treenode * proot)
{
    if(proot == NULL) {
        return;
    }
    else {
        if(proot->pleft) {
            searchtree_print(proot->pleft);
        }
        if(proot->pright) {
            searchtree_print(proot->pright);
        }
        printf("%d ", proot->element);
    }
}
