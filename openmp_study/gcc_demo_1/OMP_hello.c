#include <omp.h>
#include <stdio.h>
int main()
{
int nthreads, tid;
#pragma omp parallel private(nthreads,tid)
{
tid=omp_get_thread_num(); // 获取线程号
printf("Hello world from OpenMP thread %d\n", tid);
if (tid==0)
{
nthreads=omp_get_num_threads(); // 获取线程个数
printf("Number of threads %d\n", nthreads);
}
}
return 0;
}