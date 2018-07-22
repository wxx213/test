#include <stdio.h>
#include <stdlib.h>

#include "searchtree.h"
#include "avltree.h"

int main()
{
    struct avlnode *proot = avltree_insert(NULL, 5);
    proot = avltree_insert(proot, 7);
    proot = avltree_insert(proot, 6);
    printf("%d %d %d\n", proot->element, proot->pleft->element,
           proot->pright->element);
    return 0;
}
