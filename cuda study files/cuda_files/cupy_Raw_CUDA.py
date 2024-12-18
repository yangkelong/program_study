import cupy
import cupy as cp
import numpy as np

cuda_code = r"""
extern "C" __global__ void saxpy(int n, float a, float * x, float * y, float * out)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) out[i] = a*x[i] + y[i];
}
"""

NUM_THREADS = 512  # Threads per block
NUM_BLOCKS = 32768  # Blocks per grid
N = NUM_THREADS * NUM_BLOCKS
saxpy_kernel = cp.RawKernel(cuda_code, 'saxpy', (), u'nvcc')
d_x = cp.zeros(N, dtype=cp.float32)
d_y = cp.zeros(N, dtype=cp.float32)
d_out = cp.zeros(N, dtype=cp.float32)
# d_x = cp.arange(N, dtype=cp.float32)
# d_y = cp.arange(N, dtype=cp.float32)
# d_out = cp.arange(N, dtype=cp.float32)

saxpy_kernel((NUM_BLOCKS, 1, 1), (NUM_THREADS, 1, 1),
             (cupy.int32(N), cupy.float32(2.0), d_x, d_y, d_out))  # grid, block and arguments




# complex_kernel = cp.RawKernel(r'''
# extern "C" __global__ void saxpy(int n, float a, float * x, float * y, float * out)
# {
#   int i = blockIdx.x*blockDim.x + threadIdx.x;
#   if (i < n) out[i] = a*x[i] + y[i];
# }
# ''', 'saxpy')
#
# x1 = cupy.arange(25, dtype=cupy.float32)
# x2 = cupy.arange(25, dtype=cp.float32)
# y = cupy.zeros((25, ), dtype=cp.float32)
#
# complex_kernel((5, 1, 1), (5, 1, 1), (cupy.int32(25), cupy.float32(2.0), x1, x2, y))


# complex_kernel = cp.RawKernel(r'''
# #include <cupy/complex.cuh>
# extern "C" __global__
# void my_func(int n,const complex<float>* x1, const complex<float>* x2,
#              complex<float>* y, float a) {
#     int tid = blockDim.x * blockIdx.x + threadIdx.x;
#     if (tid < n) y[tid] = x1[tid] + a * x2[tid];
# }
# ''', 'my_func')
#
# x1 = cupy.arange(25, dtype=cupy.complex64).reshape(5, 5)
# x2 = 1j*cupy.arange(25, dtype=cupy.complex64).reshape(5, 5)
# y = cupy.zeros((5, 5), dtype=cupy.complex64)
# complex_kernel((5, 1, 1), (5, 1, 1), (cupy.int32(25), x1, x2, y, cupy.float32(2.0)))





