#include <stdio.h>
#include <stdlib.h>

#include "searchtree.h"
#include "avltree.h"

int main()
{
    struct avlnode *proot;
    proot = avltree_insert(NULL, 5);
    proot = avltree_insert(proot, 3);
    proot = avltree_insert(proot, 7);
    proot = avltree_insert(proot, 1);
    proot = avltree_insert(proot, 4);
    proot = avltree_insert(proot, 6);
    proot = avltree_insert(proot, 8);

    printf("height = %d\n", proot->height);
    avltree_print2(proot);
    return 0;
}
