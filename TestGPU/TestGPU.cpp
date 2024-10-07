#include <iostream>
#include <cmath>
#include <cuda_runtime.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <chrono>

__device__ double rtopr(double x, double y) {
    return sqrt(x * x + y * y); // Converts to radial distance
}

__device__ double rtopa(double x, double y) {
    return atan2(y, x); // Converts to angle in polar coordinates
}

__device__ glm::vec2 PtoRxy(double r, double theta) {
    return glm::vec2(r * cos(theta), r * sin(theta)); // Polar to Cartesian conversion
}

// CUDA kernel for the Sxy function
__global__ void SxyKernel(double* XResults, double* YResults, double XS, double YS, double Asta, double R, double LS, double angle, double w, double PstaStart, double PstaStep, int count) {
    int i = blockIdx.x * blockDim.x + threadIdx.x;

    if (i < count) {
        double Psta = PstaStart + i * PstaStep;
        double SITA = 0.0;
        double L = Psta - Asta;

        double a = sqrt(fabs(R) * LS) * (R >= 0 ? 1 : -1); // glm::sign equivalent in CUDA
        SITA = pow(L / a, 2) / 2 * (a >= 0 ? 1 : -1);

        double X = L * (1 - pow(SITA, 2) / 10 + pow(SITA, 4) / 216 - pow(SITA, 6) / 9360);
        double Y = L * SITA * (1.0 / 3 - pow(SITA, 2) / 42 + pow(SITA, 4) / 1320);

        double X1 = X - w * sin(SITA);
        double Y1 = Y + w * cos(SITA);

        double R1 = rtopr(X1, Y1);
        double S1 = rtopa(X1, Y1);

        glm::vec2 XY2 = PtoRxy(R1, S1 + angle);

        XResults[i] = XS + XY2[0];
        YResults[i] = YS + XY2[1];
    }
}


int main() {
    // Parameters
    double XS = 0.0, YS = 0.0, Asta = 0.0, R = 5.0, LS = 1.0, angle = 0.5, w = 0.2;
    double PstaStart = 0.0;
    double PstaStep = 1.0;
    int count = 51;  // From Psta = 0 to Psta = 50 inclusive

    // Allocate memory on host (CPU)
    double* XResults = new double[count];
    double* YResults = new double[count];

    // Allocate memory on device (GPU)
    double* d_XResults;
    double* d_YResults;
    cudaMalloc(&d_XResults, count * sizeof(double));
    cudaMalloc(&d_YResults, count * sizeof(double));

    // Define the grid and block sizes
    int threadsPerBlock = 256;  // Choose a reasonable number of threads per block
    int blocksPerGrid = (count + threadsPerBlock - 1) / threadsPerBlock;

    // Start timing
    auto start = std::chrono::high_resolution_clock::now();

    // Launch the CUDA kernel
    SxyKernel << <blocksPerGrid, threadsPerBlock >> > (d_XResults, d_YResults, XS, YS, Asta, R, LS, angle, w, PstaStart, PstaStep, count);

    // Wait for the GPU to finish
    cudaDeviceSynchronize();

    // Copy the results from device (GPU) to host (CPU)
    cudaMemcpy(XResults, d_XResults, count * sizeof(double), cudaMemcpyDeviceToHost);
    cudaMemcpy(YResults, d_YResults, count * sizeof(double), cudaMemcpyDeviceToHost);

    // End timing
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    // Output the results
    for (int i = 0; i < count; ++i) {
        std::cout << "Psta: " << PstaStart + i * PstaStep << " -> X: " << XResults[i] << " Y: " << YResults[i] << std::endl;
    }

    std::cout << "Execution time: " << duration.count() << " ms" << std::endl;

    // Free memory on device
    cudaFree(d_XResults);
    cudaFree(d_YResults);

    // Free memory on host
    delete[] XResults;
    delete[] YResults;

    return 0;
}
