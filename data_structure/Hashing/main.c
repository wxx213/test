#include <stdio.h>
#include <stdlib.h>

typedef unsigned int hash_index;

hash_index hash_func(const char *key, int table_size)
{
    unsigned int hash_val = 0;

    while(*key != '\0') {
        hash_val += *key++;
    }
    return hash_val % table_size;
}

hash_index hash_func2(const char *key, int table_size) {
    unsigned int hash_val = 0;

    while(*key != '\0') {
        hash_val = (hash_val << 5) + *key++;
    }
    return hash_val % table_size;
}

int main()
{
    printf("Hello world!\n");
    return 0;
}
