#pragma once
#include <cstddef>

typedef struct pool
{
    void* head;
    void* frist;
    int totalblock;
    size_t blocksize;
}pool;

int poolinit(pool* p, int totalnum, size_t onesize);
void* poolmalloc(pool* p);
int poolfree(pool* pool, void* p);
void destorypool(pool* p);
