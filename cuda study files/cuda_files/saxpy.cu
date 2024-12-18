extern "C" __global__
void saxpy(int n, float a, float * x, float * y, float * out)
{
  int i = blockIdx.x*blockDim.x + threadIdx.x;
  if (i < n) out[i] = a*x[i] + y[i];
}
