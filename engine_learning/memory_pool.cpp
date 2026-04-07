#include "memory_pool.h"
#include <iostream>
#include <cstdlib>

int poolinit(pool* p, int totalnum, size_t onesize)
{
    if (onesize < sizeof(void*))p->blocksize = sizeof(void*);
    else p->blocksize = (onesize + 7) & ~7;

    p->totalblock = totalnum;
    p->head = (void*)malloc(totalnum * p->blocksize);

    if (p->head == NULL)return -1;
    else
    {
        char* temp = (char*)p->head;
        void** nextp;
        p->frist = p->head;
        for (int i = 1;i <= p->totalblock - 1;i++)
        {
            nextp = (void**)temp;
            *nextp = temp + p->blocksize;
            temp = temp + p->blocksize;
        }
        nextp = (void**)temp;
        *nextp = NULL;
    }
    return 0;
}

void* poolmalloc(pool* p)
{
    if (p->frist == NULL)
    {
        std::cout << "ÄÚ´æ·ÖÅäÊ§°Ü" << std::endl;
        return NULL;
    }
    void* temp = p->frist;
    p->frist = *(void**)temp;
    return temp;
}

int poolfree(pool* pool, void* p)
{
    if (p == NULL)return-1;
    else
    {
        *(void**)p = pool->frist;
        pool->frist = p;
        return 0;
    }
}

void destorypool(pool* p)
{
    if (p->head != NULL)
    {
        free(p->head);
        p->frist = NULL;
        p->head = NULL;
    }
}