#ifndef KERNEL_LIST_H_INCLUDED
#define KERNEL_LIST_H_INCLUDED

#define offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

struct list_head {
	struct list_head *next, *prev;
};

#define list_entry(ptr, type, member) \
	container_of(ptr, type, member)

static inline void INIT_LIST_HEAD(struct list_head *list)
{
	list->next = list;
	list->prev = list;
}

#endif // KERNEL_LIST_H_INCLUDED
