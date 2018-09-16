#include <stdio.h>
#include <stdlib.h>

#include "avltree.h"

int stack_empty(struct stack_user *pstack)
{
    return pstack->curr_p == -1;
}

void stack_init(struct stack_user *pstack)
{
    pstack->curr_p = -1;
}

int stack_push(struct stack_user *pstack, union context_user ele)
{
    if(pstack->curr_p >= (stack_depth-1)) {
        pstack->curr_p = (stack_depth-1);
        return -1;
    }

    pstack->ele_array[++pstack->curr_p] = ele;
    return 0;
}

union context_user stack_pop(struct stack_user *pstack)
{
    return pstack->ele_array[pstack->curr_p--];
}

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

/**
  Simulate the function call to traversal avl tree non-recursively
**/
void avltree_print2(struct avlnode *proot)
{
    struct stack_user stack;
    struct stack_user *pstack = &stack;
    union context_user stack_ele;
    struct avlnode *pnode;
    enum context_end_child paddr;

    if(NULL == proot) {
        return;
    }
    stack_init(pstack);
    pnode = proot;


    stack_ele.pnode = pnode;
    stack_push(pstack, stack_ele);
    stack_ele.end_child = left_end;
    stack_push(pstack, stack_ele);
    pnode = pnode->pleft;

    while(!stack_empty(pstack)) {
        // enter function
        if(NULL == pnode) { //return
            if(stack_empty(pstack)) {
                break;
            }
            stack_ele = stack_pop(pstack);
            paddr = stack_ele.end_child;
            if(left_end == paddr) {
                if(stack_empty(pstack)) {
                    break;
                }
                stack_ele = stack_pop(pstack);
                pnode = stack_ele.pnode;
                printf("%d ", pnode->element);
                stack_ele.pnode = pnode;
                stack_push(pstack, stack_ele);
                stack_ele.end_child = right_end;
                stack_push(pstack, stack_ele);
                pnode = pnode->pright;
                continue;
            }
            else { //return
                continue;
            }
        }
        else {
            stack_ele.pnode = pnode;
            stack_push(pstack, stack_ele);
            stack_ele.end_child = left_end;
            stack_push(pstack, stack_ele);
            pnode = pnode->pleft;
            continue;
        }
    }
}

/**
  Traversal avl tree non-recursively with preorder and inorder method
**/
void avltree_print3(struct avlnode *proot)
{
    struct stack_user stack;
    struct stack_user *pstack = &stack;
    union context_user stack_ele;
    struct avlnode *pnode;

    if(NULL == proot) {
        return;
    }
    stack_init(pstack);
    pnode = proot;

    while(!stack_empty(pstack) || pnode != NULL) {
        if(pnode != NULL) {
            //printf("%d ", pnode->element); //preorder
            stack_ele.pnode = pnode;
            stack_push(pstack, stack_ele);
            pnode = pnode->pleft;
        }
        else {
            stack_ele = stack_pop(pstack);
            pnode = stack_ele.pnode;
            printf("%d ", pnode->element);  //inorder
            pnode = pnode->pright;
        }
    }

}

/**
  Traversal avl tree non-recursively with postorder method
**/
void avltree_print4(struct avlnode *proot)
{
    struct stack_user stack;
    struct stack_user *pstack = &stack;
    union context_user stack_ele;
    struct avlnode *pnode, *pright;
    int curr;

    if(NULL == proot) {
        return;
    }

    stack_init(pstack);
    pnode = proot;
    pright = NULL;
    while(!stack_empty(pstack) || pnode != NULL) {
        while(pnode != NULL) {
            stack_ele.pnode = pnode;
            stack_push(pstack, stack_ele);
            pnode = pnode->pleft;
        }

        while(1) {
            curr = pstack->curr_p;
            if(-1 == curr) {
                pnode = NULL;
                break;
            }
            stack_ele = pstack->ele_array[curr];
            pnode = stack_ele.pnode;

            if(NULL == pnode->pright || pnode->pright == pright) {
                printf("%d ", pnode->element);
                stack_ele = stack_pop(pstack);
                pright = stack_ele.pnode;
            }
            else {
                pnode = pnode->pright;
                break;
            }
        }
    }
}
