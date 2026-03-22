#if 0
#include<iostream>
using namespace std;

typedef struct pool
{
	void* head;
	void* frist;
	int totalblock;
	size_t blocksize;
}pool;

int poolinit(pool*p,int totalnum,size_t onesize)
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
			*nextp = temp+p->blocksize;
			temp= temp + p->blocksize;
		}
		nextp = (void**)temp;
		*nextp = NULL;
	}
	return 0;
}

void* poolmalloc(pool*p)
{
	if (p->frist == NULL)
	{
		cout << "ÄÚ´æ·ÖÅäÊ§°Ü" << endl;
		return NULL;
	}
	void* temp = p->frist;
	p->frist =*(void**)temp ;
	return temp;
}
int poolfree(pool*pool,void *p)
{
	if (p == NULL)return-1;
	else
	{
		*(void**)p = pool->frist;
		pool->frist = p;
		return 0;
	}
}
void destorypool(pool*p)
{
	if (p->head != NULL)
	{
		free(p->head);
		p->frist = NULL;
		p->head = NULL;
	}
}

int main()
{
	pool p;
	if (poolinit(&p, 100, 32) == -1)
	{
		cout << "ÄÚ´æ³õÊ¼»¯Ê§°Ü" << endl;
		return -1;
	}
	void* p1 = poolmalloc(&p);
	void* p2 = poolmalloc(&p);
	void* p3 = poolmalloc(&p);
	void* p4 = poolmalloc(&p);
	cout << p2 << endl << p4 << endl;
	poolfree(&p,p2);
	poolfree(&p, p4);
	void* p5 = poolmalloc(&p);
	void* p6 = poolmalloc(&p);
	cout << p5 << endl << p6 << endl;
	destorypool(&p);
}
#endif