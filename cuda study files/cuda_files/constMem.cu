__constant__ int array[1024];

__global__ void kernel1(int *d_dst) {
   int tId = threadIdx.x + blockIdx.x * blockDim.x;
   d_dst[tId] = array[tId];
}

__global__ void kernel2(int *d_dst, int *d_src) {
   int tId = threadIdx.x + blockIdx.x * blockDim.x;
   d_dst[tId] = d_src[tId];
}

int main(int argc, char **argv) {
   int *d_array;
   int *d_src;
   cudaMalloc((void**)&d_array, sizeof(int) * 1024);
   cudaMalloc((void**)&d_src, sizeof(int) * 1024);

   int *test = new int[1024];
   memset(test, 0, sizeof(int) * 1024);

   for (int i = 0; i < 1024; i++) {
     test[i] = 100;
   }

   cudaMemcpyToSymbol(array, test, sizeof(int) * 1024);
   kernel1<<< 1, 1024 >>>(d_array);

   cudaMemcpy(d_src, test, sizeof(int) * 1024, cudaMemcpyHostToDevice);
   kernel2<<<1, 32 >>>(d_array, d_src),

   free(test);
   cudaFree(d_array);
   cudaFree(d_src);
   
   
   }