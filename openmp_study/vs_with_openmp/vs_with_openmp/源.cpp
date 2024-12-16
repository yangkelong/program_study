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

    step = 1.0 / (double)num_steps;

#pragma omp parallel for reduction(+:sum) private(x)
    for (i = 1; i <= num_steps; i++) {
        x = (i - 0.5) * step;
        sum = sum + 4.0 / (1.0 + x * x);
    }
    /* #pragma omp parallel for������һ�� OpenMP ָ����ڽ������ for ѭ�����л���
     parallel for ���ʹ�ã���ζ��ѭ���ĵ������ڶ���߳�֮�����ִ�С�
     reduction(+:sum)��reduction �Ӿ�����ָ������ڶ���߳�֮��ϲ����� sum ��ֵ������������У�+ ��������ʾ��ÿ���̵߳ľֲ� sum ���������ۼӵ�ȫ�� sum �����С�����ζ���ڲ�������ʼʱ��sum �ᱻ��ʼ��Ϊ 0����ָ���ĳ�ʼ��ֵ��������ÿ���߳����������󣬽��ֲ� sum ��ֵ�ӵ�ȫ�� sum �С�
     private(x)��private �Ӿ���������ÿ���̶߳�Ӧ�����Լ��� x ��������������ζ����ÿ���߳��У�x ���������س�ʼ�����޸ģ�������Ӱ�������߳��е� x��
    */
    pi = step * sum;
    return pi;
}

int main(int argc, char* argv[]) {
    double   d;
    int n = 1 << 27;

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