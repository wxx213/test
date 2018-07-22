#ifndef SEARCHTREE_H_INCLUDED
#define SEARCHTREE_H_INCLUDED

typedef int etype;
struct treenode {
    etype element;
    struct treenode *pleft;
    struct treenode *pright;
};

struct treenode *searchtree_init(etype ele);
int searchtree_insert(struct treenode * proot, etype ele);
struct treenode *searchtree_find(struct treenode * proot, etype ele);
struct treenode *searchtree_find_parent(struct treenode * proot, etype ele);
struct treenode *searchtree_find_min(struct treenode * proot);
struct treenode *searchtree_delete(struct treenode * proot, etype ele);
void searchtree_print(struct treenode * proot);
#endif // SEARCHTREE_H_INCLUDED
