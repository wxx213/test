#include <stdio.h>
#include <stdlib.h>

#include "searchtree.h"
#include "avltree.h"

int main()
{
    struct avlnode *proot = avltree_insert(NULL, 8);
    proot = avltree_insert(proot, 6);
    proot = avltree_insert(proot, 10);
    proot = avltree_insert(proot, 4);
    proot = avltree_insert(proot, 7);
    proot = avltree_insert(proot, 12);
    proot = avltree_insert(proot, 2);
    avltree_print(proot);
    proot = avltree_delete(proot, 6);
    printf("\n");
    avltree_print(proot);
    return 0;
}
