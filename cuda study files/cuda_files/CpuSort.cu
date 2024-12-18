#include<iostream>
#include <ctime>
#include <random>
#include<algorithm>

using namespace std;


typedef int dataType;

#if defined(_WIN32)

#include <chrono>
#define TIMER_DECLARATION()						\
		auto startTime = std::chrono::high_resolution_clock::now();		\
		auto endTime = std::chrono::high_resolution_clock::now();
#define TIMER_START()							\
		startTime = std::chrono::high_resolution_clock::now(); // high_resolution_clock::is_steady
#define TIMER_STOP(__TIMED)						\
		endTime = std::chrono::high_resolution_clock::now();			\
		__TIMED = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - startTime).count()
#endif
// duration_cast()提供在不同的时间单位之间进行转换的功能,microseconds表示输出为微秒,count( )成员函数,用来返回时间
// nanoseconds: ns; std::chrono::milliseconds ms;


void cpuSortTest(int n, int* rounds, dataType* arr){
	std::cout<<"start CPU sort test."<<std::endl;
	TIMER_DECLARATION();
	int N=0;
	dataType* sortArr = new dataType[rounds[n-1]];
	for(int i=0; i<n; i++){
		if(i==n-1){
			
			int times = 1;
			N = rounds[i];
			TIMER_START();
			for (int m = 0; m < times; m++)
				sort(arr, arr+N);
			TIMER_STOP(double aTime);
			// 输出时间信息
			std::cout << N<<" numbers, CPU sort spend time(ms):" << aTime/times << std::endl;
		}
		else{
			// 复制前rounds[i]个数据到要执行排序的数组
			N = rounds[i];
			for(int j=0; j<N; j++){
				sortArr[j] = arr[j];
			}
			// 排序
			int times = 10;
			TIMER_START();
			for (int m = 0; m < times; m++)
				// 
				sort(sortArr, sortArr+N);
			TIMER_STOP(double aTime);
			// 输出时间信息
			std::cout << N<<" numbers, CPU sort spend time(ms):" << aTime/times << std::endl;
		}
		
		

	}
	delete[] sortArr;
}



int main() {
	std::default_random_engine e;
    std::uniform_real_distribution<double> u(-100,100); // 左闭右闭区间
    //e.seed(time(0));
	e.seed(0);
	//time(0)函数返回自格林尼治标准时间1970年1月1日00:00:00至当前时刻所流逝的秒数。
	// 
	const int n = 3;
	int rounds[]= {1000000, 10000000, 100000000};
	int maxNum = rounds[2];
	dataType* testArr= new dataType[maxNum];
	// 填充随机数据
	for(int i=0;i<maxNum;i++){
		testArr[i] = (dataType)e();
		//testArr[i] = (dataType)u(e);
	}
	
	cpuSortTest(n, rounds, testArr);
	delete[] testArr;
	return 0;





}



