#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "phonebook_hash.h"

pool *initPool(size_t size)
{
    pool *p = (pool *) malloc(size + sizeof(pool));
    p->next = (char *) &p[1];
    p->end = p->next + size;
    return p;
}

void *allocPool(pool *p, size_t size)
{
    void *tmp = (void *) p->next;
    p->next += size;
    return tmp;
}

unsigned long djb2(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str)) {
        hash = ((hash << 5) + hash) + c;
        str++;
    }

    return hash;
}

entry *findName(char lastName[], entry *pHead)
{
    while (pHead != NULL) {
        if (strcasecmp(lastName, pHead->lastName) == 0)
            return pHead;
        pHead = pHead->pNext;
    }
    return NULL;
}

entry *append(char lastName[], entry *e, pool *p)
{
    e->pNext = allocPool(p, sizeof(entry));
    e = e->pNext;
    strcpy(e->lastName, lastName);
    e->pNext = NULL;
    return e;
}

void freeList(entry *e)
{
    if (e) {
        freeList(e->pNext);
        free(e);
    }
    return;
}
