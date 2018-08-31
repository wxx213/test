#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct single_list_head *single_list_init()
{
    struct single_list_head *phead;

    phead = malloc(sizeof(struct single_list_head));
    if(NULL == phead) {
        return NULL;
    }

    phead->pfirst = NULL;
    return phead;
}

struct single_list_node *single_list_find(struct single_list_head *phead, int value)
{
    struct single_list_node *pnode;

    if(NULL == phead) {
        return NULL;
    }

    pnode = phead->pfirst;
    while(pnode != NULL) {
        if(pnode->element == value) {
            return pnode;
        }
        pnode = pnode->pnext;
    }
    return NULL;
}

struct single_list_node *single_list_find_prev(struct single_list_head *phead, struct single_list_node *pnode)
{
    struct single_list_node *ptmp;

    ptmp = phead->pfirst;
    if(ptmp == pnode) {
        return NULL;
    }

    while(ptmp->pnext != NULL) {
        if(ptmp->pnext == pnode) {
            return ptmp;
        }
        ptmp = ptmp->pnext;
    }

    return NULL;
}
int single_list_insert(struct single_list_head *phead, int value)
{
    struct single_list_node *pnode, *ptmp;

    if(NULL == phead) {
        return -1;
    }
    if(single_list_find(phead, value) != NULL) {
        return 0;
    }

    ptmp = phead->pfirst;
    pnode = malloc(sizeof(struct single_list_node));
    pnode->element = value;
    pnode->pnext = ptmp;
    phead->pfirst = pnode;

    return 0;
}

void single_list_delete(struct single_list_head *phead, int value)
{
    struct single_list_node *pnode, *pprev;

    if(NULL == (pnode = single_list_find(phead, value))) {
        printf("the node to delete is not found\n");
        return;
    }

    pprev = single_list_find_prev(phead, pnode);
    if(NULL == pprev) { //pnode is the firt node
        phead->pfirst = pnode->pnext;
    }
    else {
        pprev->pnext = pnode->pnext;
    }
    free(pnode);
}

void single_list_print(struct single_list_head *phead)
{
    struct single_list_node *pnode;

    if(NULL == phead) {
        return;
    }

    pnode = phead->pfirst;
    while(pnode != NULL) {
        printf("%d ", pnode->element);
        pnode = pnode->pnext;
    }
    printf("\n");
}

struct single_list_node *single_list_recur_reverse(struct single_list_node *pprev, struct single_list_node *pcurr)
{
    struct single_list_node *ptmp;

    if(NULL == pcurr) {
        return pprev;
    }

    ptmp = pcurr->pnext;
    pcurr->pnext = pprev;
    ptmp = single_list_recur_reverse(pcurr, ptmp);
    return ptmp;
}
void single_list_reverse(struct single_list_head *phead)
{
    phead->pfirst = single_list_recur_reverse(NULL, phead->pfirst);
}
void single_list_reverse2(struct single_list_head *phead)
{
    struct single_list_node *pprev, *pcurr, *pnext;

    pprev = NULL;
    pcurr = phead->pfirst;

    while(pcurr != NULL) {
        pnext = pcurr->pnext;
        pcurr->pnext = pprev;
        pprev = pcurr;
        pcurr = pnext;
    }
    phead->pfirst = pprev;
}
