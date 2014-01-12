#include <stdio.h>
#include "../Src/btree.h"

#define NUM 20000 

int test_btree()
{
    btree_t *btree;
    btnode_t *node;
    int index, i;

    if (!(btree = btree_create()))
    {
        return -1;
    }

    for (i = 1; i < NUM; ++i)
    {
        btree = btree_insert(btree, i);
    }

    for (i = 1; i < NUM; ++i)
    {
        node = btree_search(btree, i, &index);

        if (!node || index == -1)
        {
            printf("insert error!\n");
            return -1;
        }
    }

    for (i = 1; i < NUM; ++i)
    {
        btree = btree_delete(btree, i);

        btree = btree_insert(btree, i);
    }

    return 0;
}
