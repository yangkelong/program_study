#include <iostream>
#include <cassert>
using namespace std;


__device__ int device_int;


__global__ void kernel()
{
    device_int = 1000;
}

int main()
{
    kernel<<<1, 1>>>();
    assert(cudaGetLastError() == cudaSuccess);

    int *host_pointer_to_device_int;
    /* Get a pointer to device_int. After this, I won't be able to access it,
     * but I'm going to copy its value with cudaMemcpy */
    cudaGetSymbolAddress((void **)&host_pointer_to_device_int, device_int);
    assert(cudaGetLastError() == cudaSuccess); // The above operation executed successfully

    int host_int;
    // Copy the device_int's value
    cudaMemcpy(&host_int, host_pointer_to_device_int,
            sizeof(int), cudaMemcpyDeviceToHost);

    // style2
    int value;
    cudaMemcpyFromSymbol(&value, device_int, cudaMemcpyDeviceToHost);
    assert(cudaGetLastError() == cudaSuccess); // The above operation executed successfully
    cout << value << endl; // Everything's fine!
    cout << host_int << endl; // Everything's fine!
}

