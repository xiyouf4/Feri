#include <stddef.h>

typedef struct Threadpool Threadpool;

Threadpool *Threadpoolinit(size_t thread_count);
void Threadpoolcreate(Threadpool *pool);
void Threadpoolpushtask(Threadpool *pool, int ready_fd);
void Threadpoolstop(Threadpool *pool);
void Threadpooldestory(Threadpool *pool);
size_t Threadpooltaskcount(Threadpool *pool);
