// cpp_compiler_options_openmp.cpp
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

volatile DWORD dwStart;
volatile int global = 0;

double test2(int num_steps) {
   int i;
   global++;
   double x, pi, sum = 0.0, step;

   step = 1.0 / (double) num_steps;

   #pragma omp parallel for reduction(+:sum) private(x)
   for (i = 1; i <= num_steps; i++) {
      x = (i - 0.5) * step;
      sum = sum + 4.0 / (1.0 + x*x);
   }
/* #pragma omp parallel for：这是一个 OpenMP 指令，用于将后面的 for 循环并行化。
 parallel for 结合使用，意味着循环的迭代将在多个线程之间分配执行。
 reduction(+:sum)：reduction 子句用于指定如何在多个线程之间合并变量 sum 的值。在这个例子中，+ 操作符表示在每个线程的局部 sum 变量将被累加到全局 sum 变量中。这意味着在并行区域开始时，sum 会被初始化为 0（或指定的初始化值），并在每个线程完成其迭代后，将局部 sum 的值加到全局 sum 中。
 private(x)：private 子句用于声明每个线程都应该有自己的 x 变量副本。这意味着在每个线程中，x 将被独立地初始化和修改，而不会影响其他线程中的 x。
*/
   pi = step * sum;
   return pi;
}

int main(int argc, char* argv[]) {
   double   d;
   int n = 1<<27;
   
   if (argc > 1)
      n = atoi(argv[1]);
	printf_s("n: %d\n", n);
   dwStart = GetTickCount();
   d = test2(n);
   printf_s("For %d steps, pi = %.15f, %d milliseconds\n", n, d, GetTickCount() - dwStart);

   dwStart = GetTickCount();
   d = test2(n);
   printf_s("For %d steps, pi = %.15f, %d milliseconds\n", n, d, GetTickCount() - dwStart);
}