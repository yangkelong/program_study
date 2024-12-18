
#include <iostream>

__global__ void test_shuf_broadcast( int *__restrict__ dOutput, const int *__restrict__ dInput, const int srcLane){
    int val = dInput[threadIdx.x];
    // test1
    val = __shfl_sync(0xfff0fAfA, val, srcLane);
    // 特别地，各种函数返回的结果对被掩码排除的线程是没有定义的，不要尝试在这些被排除的线程中使用函数的返回值。
    unsigned int laneID = threadIdx.x & 0x1f;
    if(((1<<laneID) & 0xfff0fAfA)!=0)   // 取出该mask上 laneID处掩码值，1表示该线程参与运算; 1<<laneID 将1左移laneID位 置laneID位为1
        {dOutput[threadIdx.x] = val;
        printf("laneID:%d", laneID);
        }
    // mask:11111111,11110000,11111010,11111010
    //  如果不作判断，2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
    // 0 2 0 2 2 2 2 2 ,0 2 0 2 2 2 2 2 ,0 0 0 0 2 2 2 2 ,2 2 2 2 2 2 2 2
    // test2
    //val = __shfl_sync(0xffffffff, val, srcLane, 16);
    // dOutput[threadIdx.x] = val;
    // mask:11111111,11111111,11111111,111111111
    // 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 18 18 18 18 18 18 18 18 18 18 18 18 18 18 18 18
    // test3
    //val = __shfl_sync(0xffffffff, val, srcLane, 32);
    // dOutput[threadIdx.x] = val;
    // mask:11111111,11111111,11111111,111111111
    // 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2 2
}


int main(){

    
    const int n = 32;
    int in[n];
    int out[n];
    int size = n * sizeof(int);

    std::cout <<"---------------input-------------" << std::endl;
    for (int i = 0; i < n; i++)
   {   
      in[i] = i;
      std::cout << in[i]<<" ";
   }
    std::cout <<"----------------------------" << std::endl;
   
    // GPU端分配内存
    int *in_d, *out_d;
    cudaMalloc((void**)&in_d, size);
    cudaMalloc((void**)&out_d, size);
    cudaMemcpy(in_d, in, size, cudaMemcpyHostToDevice); 
	// 核函数启动
	test_shuf_broadcast<<< 1, 32>>>(out_d, in_d, 2);
    
    cudaMemcpy(out, out_d, size, cudaMemcpyDeviceToHost);
    std::cout <<"---------------output-------------" << std::endl;
    for (int i = 0; i <     32; i++)
        std::cout << out[i]<<" ";
    std::cout <<"----------------------------" << std::endl;

        // 释放CPU端、GPU端的内存
    cudaFree(in_d);
    cudaFree(out_d);

}